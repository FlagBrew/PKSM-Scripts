#!/usr/bin/env node
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const getSaveVersion = require('./saveVersion');

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
parser.addArgument('saves', {
    nargs: '+',
    help: 'Space separated list of save files to diff',
});

/* Global variables */
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
 * @param {String[]} fileNames
 * @returns {Buffer[]}
 */
function loadSaves(fileNames) {
    const saveData = [];
    fileNames.map((v, i) => {
        try {
            saveData[i] = fse.readFileSync(v);
        } catch (err) {
            console.log(`There was an error reading save ${v}. Excluding it from diff`);
        }
    });
    return saveData;
}

/**
 * @param {Buffer[]} data
 * @returns {String}
 */
function checkSaveCompat(data) {
    let testResult;

    // check compatibility based on save size
    const saveSizes = data.map(v => v.length);
    testResult = saveSizes.some((v, i, a) => v !== a[0]);
    if (testResult) {
        return 'Saves aren\'t all the same size.';
    }

    // compare version
    const versions = data.map((v, i) => getSaveVersion(saveSizes[i], v));
    if (versions.includes(-1)) {
        return 'One or more save\'s version couldn\'t be determined.';
    }
    testResult = versions.some((v, i, a) => (v >> 1) !== (a[0] >> 1));
    if (testResult) {
        return 'Two or more saves come from different version pairings.';
    }
    const version = versions[0];

    // check number of saves
    if (data.length < 2) {
        // allow only 1 save file if it's Gen 4 (DPPtHGSS)
        testResult = data.length === 1 && [10, 11, 12, 7, 8].includes(version);

        // NOTE: testing for Gen 5+ save splitting goes here if made

        if (testResult) {
            split = true;
        } else {
            return 'Not enough saves were provided and successfully read.';
        }
    }

    // all saves are compatible
    return '';
}

/**
 * @param {String[]} files
 * @param {Buffer[]} data
 * @param {Number []} diffRange
 * @returns {String}
 */
function generateDiff(files, data, diffRange) {
    const diff = [];

    // construct diff header
    const tableHeader = ['\nOffset   '];
    diff.push('Diff of saves from the following file(s):\n');
    files.forEach((v, i) => {
        diff.push(`\nSave ${i + 1}: ${v}`);
        tableHeader.push(`    Save ${i + 1}`);
    });
    if (split) {
        diff.push('\n\nNote: Due to the way Gen 4 saves are stored, data in Save 1 may be more recent than the corresponding data in Save 2');
    }

    // event diffing (function call?) goes here

    // range slicing
    if (diffRange) {
        // blah
    }

    // construct diff body
    diff.push(`\n\n${tableHeader.join('')}\n`);
    data[0].forEach((d, n) => {
        const offsetDiff = {
            offset: toPaddedHexString(n, 5),
            values: [],
        };
        data.forEach((v, i) => {
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
 * @param {String} params.o
 */
function main(params) {
    let saveFiles = params.saves;
    let outFile = '';
    if (params.o) {
        outFile = params.o;
        outFile = `${outFile}${outFile.slice(-4) === '.txt' ? '' : '.txt'}`;
    }

    console.log('Loading saves...');
    const fileBuffs = loadSaves(saveFiles);
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
    const compatFailReason = checkSaveCompat(fileBuffs);
    if (compatFailReason !== '') {
        console.log(`Save compatibility check failed.\nReason: "${compatFailReason}"\nExiting without diffing.`);
        return;
    }

    // split lone Gen 4 save
    if (split) {
        // NOTE: save splitting for Gen 5+ would go here if it ever gets made
        // Multi-gen save splitting logic would probably be abstracted to its own function

        const saveData = fileBuffs[0];
        const saveName = saveFiles[0];
        fileBuffs[1] = saveData.slice(0x40000);
        fileBuffs[0] = saveData.slice(0, 0x40000);
        saveFiles[0] = `${saveName} (0x00000:0x3ffff)`;
        saveFiles[1] = `${saveName} (0x40000:0x7ffff)`;
    }

    console.log('Generating diff...');
    const diff = generateDiff(saveFiles, fileBuffs, params.range);

    // output diff
    if (diffs === 0) {
        console.log(`Saves were identical.${outFile !== '' ? outFile : ''}`);
    } else if (outFile !== '') {
        fse.outputFileSync(outFile, diff);
        console.log(`Diff written to ${outFile} successfully.`);
    } else {
        console.log(`\n\n${diff}`);
    }
}

// execute if called directly from command line
if (module === require.main) {
    main(parser.parseArgs());
}
