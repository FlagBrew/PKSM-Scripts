#!/usr/bin/env node
const path = require('path');
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const klawSync = require('klaw-sync');
const Sav = require('./Sav');

/* argparse setup */
const parser = new ArgumentParser({
    addHelp: true,
    description: 'Generate a list of differences between 2 or more Gen 4-7 Pokémon save files',
});
parser.addArgument(['-o', '--out'], {
    metavar: 'outFile',
    help: 'File (.txt) to write diff to -- if not given, diff is written to console',
});
parser.addArgument('-s', {
    action: 'storeTrue',
    help: 'Flag to perform a save diff',
});
parser.addArgument('-e', {
    action: 'storeTrue',
    help: 'Flag to perform an event diff',
});
parser.addArgument(['-k', '--keep'], {
    choices: ['first', 'all', 'full'],
    help: 'Whether save files should not be split (full) or which backup save data (first or all) should be kept',
});
const groupRange = parser.addArgumentGroup({
    title: 'Save Diff Range(s)',
    description: 'Range(s) to limit save diff to. Optional. Can use one or both, can even use them multiple times.',
});
groupRange.addArgument(['-r', '--range'], {
    action: 'append', // allow diff of multiple ranges
    nargs: 2,
    metavar: ['start', 'end'],
    help: 'Specific range to limit diff to, from start (inclusive) to end (exclusive). Can be used repeatedly to diff multiple ranges',
});
groupRange.addArgument('-l', {
    action: 'append', // allow diff of multiple ranges
    nargs: 2,
    metavar: ['start', 'length'],
    help: 'Specific range to limit diff to, length number of bytes beginning at start. Can be used repeatedly to diff multiple ranges',
});
const groupSave = parser.addArgumentGroup({
    title: 'Save File(s)',
    description: 'Path(s) to save file(s) to be used in diff.\nRequired -- can use either one, or both, but input must result in at least 1 save file being found.',
});
groupSave.addArgument(['-d', '--dir'], {
    metavar: 'dir',
    nargs: '+',
    help: 'Space separated list of directories (folders) containing files to diff',
});
groupSave.addArgument(['-f', '--files'], {
    nargs: '+',
    help: 'Space separated list of save files to diff',
});

/* Global variables */
const counts = {
    'DP': {
        'constCount': 288,
        'flagCount': 2912,
    },
    'PT': {
        'constCount': 288,
        'flagCount': 2912,
    },
    'HGSS': {
        'constCount': 368,
        'flagCount': 2912,
    },
    "BW": {
        'constCount': 318,
        'flagCount': 2912,
    },
    'B2W2': {
        'constCount': 431,
        'flagCount': 3064,
    },
    'XY': {
        'constCount': 382,
        'flagCount': 3072,
    },
    'ORAS': {
        'constCount': 382,
        'flagCount': 3072,
    },
    'SM': {
        'constCount': 1000,
        'flagCount': 3968,
    },
    'USUM': {
        'constCount': 1000,
        'flagCount': 4928,
    },
    // 'LGPE': {
    //     'constCount': 1000,
    //     'flagCount': 4160,
    // },
};


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
 * @param {Object} state
 * @param {Boolean} state.isSplit
 * @param {Number[][]} state.ranges
 * @returns {String}
 */
function summarizeSaves(saves, state) {
    const header = [];

    // construct diff header
    header.push('Diff of saves from the following file(s):\n\n');
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
        header.push(`Save ${i + 1}: "${v.fileName}"${state.isSplit ? ' (' + v.contents + ')' : ''}\n`);

        // report block offsets of split saves
        if (state.isSplit) {
            if (v.generation === 4) { // split Gen 4 save
                header.push(`    General: ${ofs.general.map(n => toHexStr(n + v.active.general * 0x40000, 5)).join(':')}\n`);
                header.push(`    Storage: ${ofs.storage.map(n => toHexStr(n + v.active.storage * 0x40000, 5)).join(':')}\n`);
                header.push(`    HoF:     ${ofs.hof.map(n => toHexStr(n + v.active.hof * 0x40000, 5)).join(':')}\n`);
            } else if (v.verGroupAbbr === 'BW') { // split BW save
                header.push(`    Save:  ${ofs.save.map(n => toHexStr(n + v.active.save * 0x24000, 5)).join(':')}\n`);
                header.push(`    Extra: ${ofs.extra.map(n => toHexStr(n, 5)).join(':')}\n`);
            } else if (v.verGroupAbbr === 'B2W2') { // split B2W2 save
                header.push(`    Save:  ${ofs.save.map(n => toHexStr(n + v.active.save * 0x26000, 5)).join(':')}\n`);
                header.push(`    Extra: ${ofs.extra.map(n => toHexStr(n, 5)).join(':')}\n`);
            } else {
                console.log('How did you split this input?');
            }
        }
    });

    if (saves[0].generation === 4 && state.isSplit) {
        header.push('\nNote: "Current" / "backup" status of HoF blocks of saves may not be accurate.\n');
    }

    return header.join('');
}

/**
 * Builds header for table of diffs
 *
 * @param {Number} numSaves Number of saves that table will list data of
 * @param {String} firstColumn Label for the first column of the table
 * @param {Number[][]} [rangeList] (optional) List of ranges to be included in table
 * @returns {String}
 */
function buildTableHeader(numSaves, firstColumn, rangeList) {
    const header = [];

    if (rangeList) {
        let ranges = [];
        rangeList.forEach(v => ranges.push(v.map(v => toHexStr(v, 5)).join('-')));
        ranges.push('\n');
        header.push(ranges.join('\n'));
    }

    header.push(`${firstColumn}        `.slice(0, 9));
    for (let i = 0; i < numSaves; i++) {
        let digits = 10;
        if (i % 10 === 9) {
            digits += (Math.floor(Math.log10(i + 1)) !== Math.floor(Math.log10(i)));
        }
        header.push(`    Save ${i + 1}`.slice(-digits));
    }
    header.push('\n');

    return header.join('');
}

/**
 * @param {Sav[]} saves
 * @param {Object} state
 * @param {Number} state.diffs
 */
function diffConsts(saves, state) {
    // shortcut out if LGPE
    if (saves[0].verGroupAbbr === 'LGPE') {
        console.log('Event Diff does not work on LGPE yet.');
        return '';
    }

    const versionInfo = {
        ofs: Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventConst'),
        count: counts[saves[0].verGroupAbbr]['constCount'],
    };

    const eConstData = saves.map(v => {
        const data = v.getCurrent().slice(versionInfo.ofs[0], versionInfo.ofs[1]);
        let extracted = [];
        for (let n = 0; n < versionInfo.count; n++) {
            extracted[n] = data.readUInt16LE(n * 2);
        }
        return extracted;
    });

    const constDiffs = [];
    eConstData[0].forEach((d, n) => {
        const constDiff = {
            num: `${n}        `.slice(0, 9),
            values: [],
        };
        eConstData.forEach((v, i) => {
            constDiff.values[i] = `${v[n]}     `.slice(0, 6);
        });
        const match = constDiff.values.every((v, i, a) => v === a[0]);
        if (!match) {
            state.diffs += 1;
            const line = [constDiff.num];
            Array.prototype.push.apply(line, constDiff.values);
            constDiffs.push(`${line.join('    ').trim()}\n`);
        }
    });
    if (constDiffs.length) {
        constDiffs.unshift('\nEvent Const Diff\n\n', buildTableHeader(saves.length, 'Const'));
        return constDiffs.join('');
    }
    return '\nEvent constants are identical.\n';
}

/**
 * @param {Sav[]} saves
 * @param {Object} state
 * @param {Number} state.diffs
 */
function diffFlags(saves, state) {
    // shortcut out if LGPE
    if (saves[0].verGroupAbbr === 'LGPE') {
        console.log('Event Diff does not work on LGPE yet.');
        return '';
    }

    const versionInfo = {
        ofs: Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventFlag'),
        count: counts[saves[0].verGroupAbbr]['flagCount'],
    };

    const eFlagData = saves.map(v => {
        const data = v.getCurrent().slice(versionInfo.ofs[0], versionInfo.ofs[1]);
        let extracted = [];
        for (let n = 0; n < versionInfo.count; n++) {
            extracted[n] = (data[n >> 3] >> (n & 7) & 1) === 1;
        }
        return extracted;
    });

    const flagDiffs = {
        set: [],
        setToggle: [],
        unset: [],
        unsetToggle: [],
        toggle: [],
    };
    let found = false;
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
            found = true;
            state.diffs += 1;
            if (flagDiff.values[0] === flagDiff.last) {
                flagDiffs.toggle.push(flagDiff.num);
            } else if (changes === 1) {
                flagDiffs[`${flagDiff.last ? '' : 'un'}set`].push(flagDiff.num);
            } else {
                flagDiffs[`${flagDiff.last ? '' : 'un'}setToggle`].push(flagDiff.num);
            }
        }
    });

    if (found) {
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
 * @param {Sav[]} saves
 * @param {Object} state
 * @param {Number[][]} state.ranges
 * @param {Boolean} state.isSplit
 * @param {Number} state.diffs
 * @param {String} [label]
 * @returns {String}
 */
function diffSave(saves, state, label = '') {
    const diff = [];

    const ofsUpdate = state.isSplit && saves[0].generation === 5;
    let saveEnd;
    if (ofsUpdate) {
        saveEnd = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'save')[1];
    }

    state.ranges.forEach(v => {
        const end = v[1];
        for (let i = v[0]; i < end; i++) {
            const offsetDiff = {
                offset: toHexStr(i, 5),
                values: [],
            };
            if (ofsUpdate && i > saveEnd) {
                offsetDiff.offset = toHexStr(i + saveEnd + 1, 5);
            }
            saves.forEach((s, n) => {
                offsetDiff.values[n] = toHexStr(s.data[i], 2);
            });
            const match = offsetDiff.values.every((v, n, a) => v === a[0]);
            if (!match) {
                state.diffs += 1;
                diff.push(`${offsetDiff.offset}      ${offsetDiff.values.join('      ')}\n`);
            }
        }
    });

    if (diff.length) {
        let header;
        if (state.ranges[0].join(' ') === `0 ${saves[0].data.length}`) {
            header = buildTableHeader(saves.length, 'Offset');
        } else {
            header = buildTableHeader(saves.length, 'Offset', state.ranges);
        }
        diff.unshift(label, header);
    }
    return diff.join('');
}

/**
 * @param {Object} params
 * @param {String} [params.out] - (Optional) Output .txt file to write diff to. If none, diff written to console
 * @param {Boolean} [params.s] - (Optional) Include save diff
 * @param {Boolean} [params.e] - (Optional) Include event diff
 * @param {String} [params.keep] - (Optional) Keep entire save for diff if split-able
 * @param {String[]} [params.range] - (Optional) List of range start and end offsets to limit save diff to
 * @param {String[]} [params.l] - (Optional) List of range start offsets and lengths to limit save diff to
 * @param {String[]} params.files - List of save files (at least one required of this or params.dir)
 * @param {String[]} params.dir - List of directories containing save files (at least one required of this or params.files)
 */
function main(params) {
    // get list of files from provided directories
    if (params.dir) {
        if (!params.files) {
            params.files = [];
        }
        params.dir.forEach(d => {
            try {
                const paths = klawSync(d, { nodir: true });
                if (paths.length > 0) {
                    const fileNames = paths.map(f => path.relative('', f.path));
                    Array.prototype.push.apply(params.files, fileNames);
                }
            } catch (e) {
                console.log(`Directory "${d}" could not be read.`);
            }
        });
    }
    // need at least 1 save
    if (!params.files || params.files.length == 0) {
        parser.error('At least 1 save file is required');
    }

    console.log('Loading saves...');
    const saves = params.files.map(v => new Sav(v)).filter(v => {
        const known = v.version !== -1;
        if (!known) {
            console.log(`  Unable to determine version of save "${v.fileName}". Excluding it from diff.`);
        }
        return known;
    });

    console.log('Checking compatibility of saves...');
    let reason = Sav.checkCompat(saves);
    if (reason !== '') {
        console.log(`\nSave compatibility check failed.\nReason: "${reason}"\nExiting without diffing.`);
        return;
    }

    const state = {
        e: params.e || !params.s,
        s: params.s || !params.e,
        ranges: [],
        isSplit: false,
        diffs: 0,
    };

    // save splitting
    if (saves[0].canSplit()) {
        if (saves.length === 1 || params.keep === 'first') {
            state.isSplit = true;
            Sav.splitSave(saves, 0, true);
        }
        if (params.keep !== 'full') {
            state.isSplit = true;
            const keepAll = params.keep === 'all';
            saves.forEach((v, i, a) => Sav.splitSave(a, i, keepAll));
        }
    } else if (saves.length === 1) {
        console.log(`\nCannot split a single ${saves[0].verGroupAbbr} save file. Exiting without diffing.`);
        return;
    }

    // consolidate and sort any supplied ranges
    let rangeLabel = '';
    if (params.l) {
        params.l.forEach(r => {
            state.ranges.push([+r[0], +r[0] + (+r[1])]);
        });
    }
    if (params.range) {
        state.s = true; // force save diff
        params.range.forEach(r => {
            // TODO: check that range doesn't exceed length of save's data
            state.ranges.push(r.map(v => +v));
        });
        // CONSIDER: should I handle (prevent/merge) overlapping ranges?
        state.ranges.sort((a, b) => a[0] - b[0]);
        rangeLabel = 'Save Diff range(s):\n';
    } else if (state.s) {
        state.ranges.push([0, saves[0].data.length]);
    }

    console.log('Generating diff...');
    const diff = [];
    diff.push(summarizeSaves(saves, state));
    if (state.e) {
        const constDiff = diffConsts(saves, state);
        const flagDiff = diffFlags(saves, state);
        let rawEventDiff = '';
        if (state.diffs) {
            const rawEventState = {
                isSplit: state.isSplit,
                ranges: [[
                    Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventConst')[0],
                    Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventFlag')[1],
                ]],
                diffs: 0,
            };
            rawEventDiff = diffSave(saves, rawEventState, 'Raw Event Data Diff\n  ');
            state.diffs += rawEventState.diffs;
        }
        diff.push(['', constDiff, flagDiff, '', rawEventDiff].join('\n'));
    }
    if (state.s) {
        diff.push('\n\n\nSave Diff\n\n');
        diff.push(diffSave(saves, state, rangeLabel));
    }

    // output results
    if (params.out) {
        params.out += params.out.slice(-4) === '.txt' ? '' : '.txt';
    }
    if (state.diffs === 0) {
        console.log(`\nSaves were identical.${params.out ? " " + params.out + " not written to." : ""}`);
        return;
    }

    if (params.out) {
        fse.outputFileSync(params.out, diff.join(''));
        console.log(`\nDiff written to "${params.out}" successfully.`);
        return;
    }
    console.log(`\n\n${diff.join('')}`);
}

// in case someone wants to write their own script
module.exports = {
    save: diffSave,
    eventConst: diffConsts,
    eventFlags: diffFlags,
};

// execute if called directly from command line
if (module === require.main) {
    main(parser.parseArgs());
}
