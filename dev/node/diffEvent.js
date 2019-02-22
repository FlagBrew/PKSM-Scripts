#!/usr/bin/env node
const path = require('path');
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const klawSync = require('klaw-sync');
const Sav = require('./Sav');

/* argparse setup */
const parser = new ArgumentParser({
    addHelp: true,
    description: 'Generate a list of differences in the event flags and event constants of 2 or more Gen 4-7 Pokémon save files',
});
parser.addArgument('-o', {
    metavar: 'outFile',
    help: 'File (.txt) to write diff to -- if not given, diff is written to console',
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
let split = false;
let diffs = 0;
const cli = module === require.main;

/**
 * @param {Number} version
 * @returns {Object}
 */
function getVersionEventInfo(version) {
    let data;
    switch (version) {
        case 10:
        case 11:
            data = {
                'constStart': 0xd9c,
                'constCount': 288,
                'flagStart': 0xfdc,
                'flagCount': 2912,
            };
            break;
        case 12:
            data = {
                'constStart': 0xdac,
                'constCount': 288,
                'flagStart': 0xfec,
                'flagCount': 2912,
            };
            break;
        case 7:
        case 8:
            data = {
                'constStart': 0xde4,
                'constCount': 368,
                'flagStart': 0x10c4,
                'flagCount': 2912,
            };
            break;
        case 20:
        case 21:
            data = {
                'constStart': 0x20100,
                'constCount': 318,
                'flagStart': 0x2037c,
                'flagCount': 2912,
            };
            break;
        case 22:
        case 23:
            data = {
                'constStart': 0x1ff00,
                'constCount': 431,
                'flagStart': 0x2025e,
                'flagCount': 3064,
            };
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            data = {
                'constStart': 0x14a00,
                'constCount': 382,
                'flagStart': 0x14cfc,
                'flagCount': 3072,
            };
            break;
        case 30:
        case 31:
            data = {
                'constStart': 0x1c00,
                'constCount': 1000,
                'flagStart': 0x23d0,
                'flagCount': 3968,
            };
            break;
        case 32:
        case 33:
            data = {
                'constStart': 0x1e00,
                'constCount': 1000,
                'flagStart': 0x25d0,
                'flagCount': 4928,
            };
            break;
        default:
            // TODO: come up with error handling for other versions
            break;
    }
    return data;
}

/**
 * @param {Array[]} eFlagData
 * @returns {String}
 */
function diffEventFlags(eFlagData) {
    const flagDiffs = {
        set: [],
        setToggle: [],
        unset: [],
        unsetToggle: [],
        toggle: [],
    };
    let flagDiffCount = 0;
    eFlagData[0].forEach((d, n) => {
        const flagDiff = {
            num: `000${n}`.slice(-4),
            values: [],
            last: true,
        };
        eFlagData.forEach((v, i) => {
            flagDiff.values[i] = v[n];
            flagDiff.last = v[n];
        });
        const changes = flagDiff.values.reduce((t, v, i, a) => {
            if (i > 0) {
                return t + (v !== a[i - 1]);
            }
            return t;
        }, 0);
        if (changes > 0) {
            flagDiffCount += 1;
            if (flagDiff.values[0] === flagDiff.last) {
                flagDiffs.toggle.push(flagDiff.num);
            } else if (changes === 1) {
                flagDiffs[`${flagDiff.last ? '' : 'un'}set`].push(flagDiff.num);
            } else {
                flagDiffs[`${flagDiff.last ? '' : 'un'}setToggle`].push(flagDiff.num);
            }
        }
    });

    if (flagDiffCount) {
        let flagDiffData = ['\nEvent Flag Diff\n'];

        if (flagDiffs.set.length > 0) {
            flagDiffData.push(`Set: ${flagDiffs.set.join(', ')}\n`);
        }
        if (flagDiffs.unset.length > 0) {
            flagDiffData.push(`Unset: ${flagDiffs.unset.join(', ')}\n`);
        }
        if (flagDiffs.setToggle.length > 0) {
            flagDiffData.push(`Set (toggled): ${flagDiffs.setToggle.join(', ')}\n`);
        }
        if (flagDiffs.unsetToggle.length > 0) {
            flagDiffData.push(`Unset (toggled): ${flagDiffs.unsetToggle.join(', ')}\n`);
        }
        if (flagDiffs.toggle.length > 0) {
            flagDiffData.push(`Toggled: ${flagDiffs.toggle.join(', ')}\n`);
        }

        return flagDiffData.join('\n');
    }
    return '\nEvent flags are identical.\n';
}

/**
 * @param {Array[]} eConstData
 * @returns {String}
 */
function diffEventConst(eConstData) {
    const constDiffs = [];
    eConstData[0].forEach((d, n) => {
        const constDiff = {
            num: `${n}    `.slice(0, 5),
            values: [],
        };
        eConstData.forEach((v, i) => {
            constDiff.values[i] = `${v[n]}     `.slice(0, 6);
        });
        const match = constDiff.values.every((v, i, a) => v === a[0]);
        if (!match) {
            diffs += 1;
            const line = [constDiff.num];
            Array.prototype.push.apply(line, constDiff.values);
            constDiffs.push(`${line.join('    ').trim()}\n`);
        }
    });
    if (constDiffs.length) {
        const eConstHeader = ['\nEvent Const Diff\n\nConst'];
        eConstData.forEach((v, i) => {
            eConstHeader.push(`    Save ${i + 1}`);
        });
        eConstHeader.push('\n');
        constDiffs.unshift(eConstHeader.join(''));
        return constDiffs.join('');
    }
    return '\nEvent constants are identical.\n';
}

/**
 * @param {String[]} files
 * @param {Buffer[]} data
 * @returns {String}
 */
function generateDiff(files, data) {
    const diff = [];

    // detect version of save(s)
    const version = Sav.getVersion(data[0].length, data[0]);
    if ([-1, 42, 43].includes(version)) {
        if (version != -1) {
            console.log('Event Diff does not work on LGPE yet.');
        }
        return '';
    }
    const versionInfo = getVersionEventInfo(version);

    const flagData = [];
    const constData = [];
    data.forEach((v, i) => {
        // extract Event Flags
        let raw = v.slice(versionInfo.flagStart, versionInfo.flagStart + (versionInfo.flagCount >> 3));
        let data = [];
        for (let n = 0; n < versionInfo.flagCount; n++) {
            data[n] = (raw[n>>3] >> (n & 7) & 1) === 1;
        }
        flagData[i] = data;

        // extract Event Constants
        raw = v.slice(versionInfo.constStart, versionInfo.flagStart);
        data = [];
        for (let n = 0; n < versionInfo.constCount; n++) {
            data[n] = raw.readUInt16LE(n * 2);
        }
        constData[i] = data;
    });

    // diff event data
    const flagDiffs = diffEventFlags(flagData);
    if (flagDiffs.length > 0) {
        diff.push('\n', flagDiffs);
    }
    const constDiffs = diffEventConst(constData);
    if (constDiffs.length > 0) {
        diff.push('\n', constDiffs);
    }

    if (diff.length > 0) {
        // if not called from another script, construct diff header
        if (cli) {
            const header = ['Diff of saves from the following file(s):\n\n'];
            files.forEach((v, i) => {
                header.push(`Save ${i + 1}: ${v}\n`);
            });
            if (data[0].length === 0x40000) {
                header.push('\nNote: Due to the way Gen 4 saves are stored, data in Save 1 may be more recent than the corresponding data in Save 2');
            }
            header.push('\n');
            diff.unshift(header.join(''));
        }

        return diff.join('');
    }
    return 'Event flags and constants of provided saves are identical.';
}

/**
 * @param {Object} params
 * @param {String[]} params.saves
 * @param {String} params.o (Optional)
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
    const diff = generateDiff(saveFiles, fileBuffs);

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

module.exports = generateDiff;

// execute if called directly from command line
if (cli) {
    const params = parser.parseArgs();
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
