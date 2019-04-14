#!/usr/bin/env node
const path = require('path');
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const klawSync = require('klaw-sync');
const Sav = require('./Sav');
const diffEvent = require('./diffEvent');

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
    // action: 'append', // allow diff of multiple ranges
    nargs: 2,
    metavar: ['start', 'end'],
    help: 'Specific range to limit diff to, from start (inclusive) to end (exclusive)',
});
/* length-based range diffing
parser.addArgument('-l', {
    action: 'append',
    nargs: 2,
    metavar: ['start', 'length'],
    help: 'Specific range to limit diff to, length number of bytes beginning at start',
});
/* limit diff to current save (of split-able save file types)
parser.addArgument('-f', {
    action: 'storeTrue',
    help: 'Use full save file (of saves that can be split) in diff rather than just current save data',
});
/**/
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
let diffs = 0;

/**
 * @param {Number} value
 * @param {Number} padTo
 * @returns {String}
 */
function toHexStr(value, padTo) {
    let paddedHex = value.toString(16);
    while (paddedHex.length < padTo) {
        paddedHex = `0${paddedHex}`;
    }
    return `0x${paddedHex.slice(-padTo)}`;
}

/**
 * @param {Sav[]} saves
 * @param {Object} config
 * @param {Boolean} config.event
 * @param {Number[]} config.range
 * @param {Boolean} config.isSplit
 * @returns {String}
 */
function generateDiff(saves, config) {
    const diff = [];

    // construct diff header
    const tableHeader = ['\nOffset   '];
    diff.push('Diff of saves from the following file(s):\n\n');
    let ofs = {};
    if (saves[0].generation === 4) {
        ofs.general = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'general');
        ofs.storage = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'storage');
        ofs.hof = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'hof');
    } else if (saves[0].generation === 5) {
        ofs.save = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'save');
        ofs.extra = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'extra');
    }
    saves.forEach((v, i) => {
        diff.push(`Save ${i + 1}: ${v.fileName}${config.isSplit ? ' (' + v.contents + ')' : ''}\n`);

        // report block offsets of split saves
        if (config.isSplit) {
            if (v.generation === 4) { // split Gen 4 save
                diff.push(`    General: ${ofs.general.map(n => toHexStr(n + v.active.general * 0x40000, 5)).join(':')}\n`);
                diff.push(`    Storage: ${ofs.storage.map(n => toHexStr(n + v.active.storage * 0x40000, 5)).join(':')}\n`);
                diff.push(`    HoF:     ${ofs.hof.map(n => toHexStr(n + v.active.hof * 0x40000, 5)).join(':')}\n`);
            } else if (v.verGroupAbbr === 'BW') { // split BW save
                diff.push(`    Save:  ${ofs.save.map(n => toHexStr(n + v.active.save * 0x24000, 5)).join(':')}\n`);
                diff.push(`    Extra: ${ofs.extra.map(n => toHexStr(n, 5)).join(':')}\n`);
            } else if (v.verGroupAbbr === 'B2W2') { // split B2W2 save
                diff.push(`    Save:  ${ofs.save.map(n => toHexStr(n + v.active.save * 0x26000, 5)).join(':')}\n`);
                diff.push(`    Extra: ${ofs.extra.map(n => toHexStr(n, 5)).join(':')}\n`);
            } else {
                console.log('How did you split this input?');
            }
        }

        let digits = 10 + (Math.floor(Math.log10(i + 1)) !== Math.floor(Math.log10(i)));
        tableHeader.push(`    Save ${i + 1}`.slice(-digits));
    });

    if (saves[0].generation === 4 && config.isSplit) {
        diff.push('\nNote: HoF block of Save 1 may be more recent than the HoF block of Save 2\n');
    }

    // event diffing
    if (config.event) {
        let eDiff = diffEvent(saves);
        if (eDiff == '') {
            console.log('Event diff failed.');
        } else {
            diffs += eDiff.slice(0, 25) === 'Event flags and constants' ? 0 : 1;
            diff.push("\n", eDiff);
        }
    }

    // range slicing
    let slicedData = saves.map(v => v.data);
    // let slicedData = saves.map(v => config.f ? v.data : v.getCurrent());
    let sliceStart = 0;
    if (config.range) {
        sliceStart = +config.range[0];
        slicedData = slicedData.map(v => v.slice(+config.range[0], +config.range[1]));
        diff.push(`\n\nDiff range: ${config.range[0]}-${config.range[1]}`);
    }

    // construct diff body
    diff.push(`\n\n${tableHeader.join('')}\n`);
    slicedData[0].forEach((d, n) => {
        const offsetDiff = {
            offset: toHexStr(n + sliceStart, 5),
            values: [],
        };
        if (config.isSplit && saves[0].generation === 5) {
            if (n > ofs.save[1]) {
                offsetDiff.offset = toHexStr(n + sliceStart + ofs.save[1] + 1);
            }
        }
        slicedData.forEach((v, i) => {
            offsetDiff.values[i] = toHexStr(v[n], 2);
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
    const config = {
        range: params.range,
        event: params.e,
    };

    console.log('Loading saves...');
    const saves = params.saves.map(v => new Sav(v)).filter(v => v.version !== -1);

    console.log('Checking compatibility of saves...');
    let compatFailReason = Sav.checkCompat(saves);
    if (compatFailReason !== '') {
        console.log(`Save compatibility check failed.\nReason: "${compatFailReason}"\nExiting without diffing.`);
        return;
    }

    // try to split lone save
    if (saves.length === 1) {
        if (!saves[0].canSplit()) {
            console.log(`Cannot split a single ${saves[0].verGroupAbbr} save file. Exiting without diffing.`);
            return;
        }
        // split lone save
        Sav.splitSave(saves, 0, true);
        config.isSplit = true;
    }

    console.log('Generating diff...');
    const diff = generateDiff(saves, config);

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
