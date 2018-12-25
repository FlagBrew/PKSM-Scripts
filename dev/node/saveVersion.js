/* eslint no-unused-vars: "off", indent: ["warn", 4, { "SwitchCase": 1 }], no-fallthrough: "off" */

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

function validSequence(data, pattern, shift = 0) {
    const ofs = pattern.readUInt16LE(0) - 0xC + shift;
    for (let i = 0; i < 10; i++) {
        if (data[i + ofs] !== pattern[i]) {
            return false;
        }
    }
    return true;
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

    // Gen 4 detection
    if (data.readUInt16LE(0xc0fe) === ccitt16(data, 0xc0ec)) {
        return 10;
    }
    if (data.readUInt16LE(0xcf2a) === ccitt16(data, 0xcf18)) {
        return 12;
    }
    if (data.readUInt16LE(0xf626) === ccitt16(data, 0xf618)) {
        return 7;
    }

    const dpPattern = Buffer.from([0x00, 0xC1, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00]);
    const ptPattern = Buffer.from([0x2C, 0xCF, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00]);
    const hgssPattern = Buffer.from([0x28, 0xF6, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00]);
    if (validSequence(data, dpPattern)) {
        return 10;
    }
    if (validSequence(data, ptPattern)) {
        return 12;
    }
    if (validSequence(data, hgssPattern)) {
        return 7;
    }

    if (validSequence(data, dpPattern, 0x40000)) {
        return 10;
    }
    if (validSequence(data, ptPattern, 0x40000)) {
        return 12;
    }
    if (validSequence(data, hgssPattern, 0x40000)) {
        return 7;
    }

    console.log('Unrecognized save');
    return -1;
}

/**
 *
 *
 * @param {Number} saveSize
 * @param {Buffer} saveData [Optional] Buffer containing save data to determine specific save version
 * @returns {number}
 */
function getSaveVersion(saveSize, saveData) {
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
            // D: 10, P: 11, Pt: 12, HG: 7, SS: 8
            // W: 20, B: 21, W2: 22, B2: 23
            if (saveData) {
                return getDSVersion(saveData);
            } else {
                return 10;
            }
        case 0xb8800:
        case 0x100000:
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

module.exports = getSaveVersion;
