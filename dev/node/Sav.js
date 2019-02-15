const fse = require('fs-extra');

const Sav = {};

function ccitt16(save, len) { // u16 Sav::ccitt16(const u8* buf, u32 len)
    let crc = 0xffff;
    for (let i = 0; i < len; i++) {
        crc ^= (save[i] << 8); // (u16)(buf[i] << 8)
        for (let j = 0; j < 0x8; j++) {
            if ((crc & 0x8000) > 0) {
                crc = ((crc << 1) ^ 0x1021) & 0xffff; // (u16)((crc << 1) ^ 0x1021)
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

function validSequence(data, offset) {
    const size = data.readUInt32LE(offset - 0xC);
    if (size !== (offset & 0xFFFF)) {
        return false;
    }
    const sdk = data.readUInt32LE(offset - 0x8);

    const dateInt = 0x20060623;
    const dateKor = 0x20070903;

    return sdk === dateInt || sdk === dateKor;
}

function getDSVersion(data) {
    let chk = data.readUInt16LE(0x24000 - 0x100 + 0x8c + 0xe); // u16
    let actual = ccitt16(data.slice(0x24000 - 0x100), 0x8c);
    if (chk === actual) { // BW save
        return data[0x1941f];
    }

    chk = data.readUInt16LE(0x26000 - 0x100 + 0x94 + 0xe); // u16
    actual = ccitt16(data.slice(0x26000 - 0x100), 0x94);
    if (chk === actual) { // B2W2 save
        return data[0x1941f];
    }

    let offset = data.length === 0x40000 ? 0 : 0x40000;
    if (validSequence(data, offset + 0xC100)) {
        return 10;
    }
    if (validSequence(data, offset + 0xCF2C)) {
        return 12;
    }
    if (validSequence(data, offset + 0xF628)) {
        return 7;
    }

    console.log('Unrecognized save');
    return -1;
}

/**
 * @param {Number} saveSize
 * @param {Buffer} saveData [Optional] Buffer containing save data to determine specific save version
 * @returns {number}
 */
Sav.getVersion = function(saveSize, saveData) {
    switch (saveSize) {
        case 0x6cc00:
            // US: 32, UM: 33
            if (saveData) {
                return saveData[0x1404];
            } else {
                return 32;
            }
        case 0x6be00:
            // Su: 30, Mo: 31
            if (saveData) {
                return saveData[0x1204];
            } else {
                return 30;
            }
        case 0x76000:
            // AS: 26, OR: 27
            if (saveData) {
                return saveData[0x14004];
            } else {
                return 26;
            }
        case 0x65600:
            // X: 24, Y: 25
            if (saveData) {
                return saveData[0x14004];
            } else {
                return 24;
            }
        case 0x80000: // DS games
        case 0x40000: // split DPPt
            // D: 10, P: 11, Pt: 12, HG: 7, SS: 8
            // W: 20, B: 21, W2: 22, B2: 23
            if (saveData) {
                return getDSVersion(saveData);
            } else {
                return 10;
            }
        case 0xb8800:   // LGPE actual
        case 0x100000:  // LGPE raw
            // LGP: 42, LGE: 43
            if (saveData) {
                return saveData[0x1004];
            } else {
                return 42;
            }
        default:
            return -1;
    }
}

/**
 * @param {Number} saveSize
 * @param {Buffer} saveData
 * @returns {number}
 */
Sav.getGeneration = function(saveSize, saveData) {
    let version;
    switch (saveSize) {
        case 0xb8800:           // LGPE actual
        case 0x100000:          // LGPE raw
            return 7.5;
        case 0x6cc00:           // US/UM
        case 0x6be00:           // Su/Mo
            return 7;
        case 0x76000:           // AS/OR
        case 0x65600:           // X/Y
            return 6;
        case 0x80000:           // DS games
            version = Sav.getVersion(0x80000, saveData);
            if (version > 12) {
                return 5;       // W/B/W2/B2
            } else if (saveData && version > -1) {
                return 4;       // D/P/Pt/HG/SS
            }
            // intentional fallthrough
        default:
            return -1;          // unrecognized save
    }
}

/**
 * @param {Buffer[]} data
 * @returns {String} Empty string if saves are compatible, otherwise compatibility failure reason
 */
Sav.checkCompat = function(data) {
    if (data.length < 1) {
        return 'Not enough saves were provided and successfully read.';
    }

    let testResult;

    // compare version
    const versions = data.map((v) => Sav.getVersion(v.length, v));
    if (versions.includes(-1)) {
        return 'One or more save\'s version couldn\'t be determined.';
    }
    testResult = versions.some((v, i, a) => (v >> 1) !== (a[0] >> 1));
    if (testResult) {
        return 'Two or more saves come from different version pairings.';
    }

    // all saves are compatible
    return '';
}

/**
 * @param {String[]} fileNames
 * @returns {Buffer[]}
 */
Sav.loadSaves = function(fileNames) {
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
 * Check if a single save file can be split into two saves
 * Currently only returns true for Gen 4 (DPPtHGSS)
 *
 * @param {Buffer} data Contents of a single save file
 * @returns {Boolean}
 */
Sav.canSplit = function(data) {
    const canBeSplit = [10, 11, 12, 7, 8];

    const version = Sav.getVersion(data.length, data);
    if (canBeSplit.includes(version)) {
        return true;
    }
    return false;
}

/**
 * @param {String[]} saveFiles
 * @param {Buffer[]} fileBuffs
 */
Sav.splitSave = function(saveFiles, fileBuffs) {
    const saveName = saveFiles[0];
    const saveData = fileBuffs[0];

    const version = Sav.getVersion(saveData.length, saveData);
    switch (version) {
        case 10: case 11:
        case 12:
        case 7: case 8:
            saveFiles[0] = `${saveName} (0x00000:0x3ffff)`;
            saveFiles[1] = `${saveName} (0x40000:0x7ffff)`;
            fileBuffs[0] = saveData.slice(0, 0x40000);
            fileBuffs[1] = saveData.slice(0x40000);
            break;
        default:
            console.log('Cannot split this type of save.');
            break;
    }
}

module.exports = Sav;
