#!/usr/bin/env node
const path = require('path');
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const klawSync = require('klaw-sync');
const Sav = require('./Sav');
const diffEvent = require('./diffEvent')

/* argparse setup */
const parser = new ArgumentParser({
    addHelp: true,
    description: 'Generate a list of differences between 2 or more Gen 4-7 Pokémon save files',
});
parser.addArgument('-o', {
    metavar: 'outFile',
    help: 'File (.txt) to write diff to -- if not given, diff is written to console',
});
parser.addArgument(['-r', '--range'], {
    nargs: 2,
    metavar: ['start', 'end'],
    help: 'Specific range to limit diff to, from start (inclusive) to end (exclusive)',
});
parser.addArgument('-e', {
    action: 'storeTrue',
    help: 'Flag to include an event diff',
});
const group = parser.addMutuallyExclusiveGroup({ required: true });
group.addArgument(['-d', '--dir'], {
    metavar: 'dir',
    nargs: '+',
    help: 'Space separated list of directories (folders) containing files to diff',
});
group.addArgument(['-s', '--saves'], {
    nargs: '+',
    help: 'Space separated list of save files to diff',
});

/* Global variables */
let params;
let split = false;
let diffs = 0;

/**
 * @param {Number} value
 * @param {Number} padTo
 * @returns {String}
 */
function toPaddedHexString(value, padTo) {
    let paddedHex = value.toString(16);
    while (paddedHex.length < padTo) {
        paddedHex = `0${paddedHex}`;
    }
    return `0x${paddedHex.slice(-padTo)}`;
}

/**
 * @param {String[]} files
 * @param {Buffer[]} data
 * @param {Number[]} diffRange
 * @param {Boolean} eventDiff
 * @returns {String}
 */
function generateDiff(files, data, diffRange, eventDiff) {
    const diff = [];

    // construct diff header
    const tableHeader = ['\nOffset   '];
    diff.push('Diff of saves from the following file(s):\n\n');
    files.forEach((v, i) => {
        diff.push(`Save ${i + 1}: ${v}\n`);
        tableHeader.push(`    Save ${i + 1}`.slice((i == 9) ? -11 : -10));
    });

    if (data[0].length === 0x40000) {
        diff.push('\nNote: Due to the way Gen 4 saves are stored, data in Save 1 may be more recent than the corresponding data in Save 2');
    }

    // event diffing (function call?) goes here
    if (eventDiff) {
        let eDiff = diffEvent(files, data);
        if (eDiff == '') {
            console.log('Event diff failed.');
        } else {
            diffs += eDiff[0] === 'E' ? 0 : 1;
            diff.push("\n", eDiff);
        }
    }

    // range slicing
    let slicedData = data;
    let sliceStart = 0;
    if (diffRange) {
        sliceStart = +diffRange[0];
        slicedData = data.map(v => v.slice(+diffRange[0], +diffRange[1]));
        diff.push(`\n\nDiff range: ${diffRange[0]}-${diffRange[1]}`);
    }

    // construct diff body
    diff.push(`\n\n${tableHeader.join('')}\n`);
    slicedData[0].forEach((d, n) => {
        const offsetDiff = {
            offset: toPaddedHexString(n + sliceStart, 5),
            values: [],
        };
        slicedData.forEach((v, i) => {
            offsetDiff.values[i] = toPaddedHexString(v[n], 2);
        });
        const match = offsetDiff.values.every((v, i, a) => v === a[0]);
        if (!match) {
            diffs += 1;
            diff.push(`${offsetDiff.offset}      ${offsetDiff.values.join('      ')}\n`);
        }
    });

    return diff.join('');
}

/**
 * @param {Object} params
 * @param {String[]} params.saves
 * @param {String} params.o (Optional)
 * @param {String[]} params.range (Optional)
 * @param {Boolean} params.e (Optional)
 */
function main(params) {
    let saveFiles = params.saves;

    console.log('Loading saves...');
    const fileBuffs = Sav.loadSaves(saveFiles);
    let failedSaves = 0;
    saveFiles = saveFiles.filter((v, i) => {
        if (!v) {
            fileBuffs.splice(i - failedSaves, 1);
            failedSaves += 1;
            return false;
        }
        return true;
    });

    console.log('Checking compatibility of saves...');
    let compatFailReason = Sav.checkCompat(fileBuffs);
    if (compatFailReason !== '') {
        console.log(`Save compatibility check failed.\nReason: "${compatFailReason}"\nExiting without diffing.`);
        return;
    }

    // check number of saves
    if (fileBuffs.length === 1) {
        split = Sav.canSplit(fileBuffs[0]);
        if (!split) {
            console.log('Cannot split a single save file from this game. Exiting without diffing.');
            return;
        }
        // split lone save
        Sav.splitSave(saveFiles, fileBuffs);
    }

    console.log('Generating diff...');
    const diff = generateDiff(saveFiles, fileBuffs, params.range, params.e);

    // output diff
    if (diffs === 0) {
        console.log(`Saves were identical.${params.o ? " " + params.o + " not written to." : ""}`);
    } else if (params.o) {
        let outFile = params.o;
        outFile = `${outFile}${outFile.slice(-4) === '.txt' ? '' : '.txt'}`;
        fse.outputFileSync(outFile, diff);
        console.log(`Diff written to ${outFile} successfully.`);
    } else {
        console.log(`\n\n${diff}`);
    }
}

// execute if called directly from command line
if (module === require.main) {
    params = parser.parseArgs();
    if (params.dir) {
        if (!params.saves) {
            params.saves = [];
        }
        params.dir.forEach(d => {
            const paths = klawSync(d, { nodir: true });
            const fileNames = paths.map(v => path.relative('', v.path));
            Array.prototype.push.apply(params.saves, fileNames);
        })
    }
    main(params);
}
