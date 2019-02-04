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

    if (validSequence(data, 0x4C100)) {
        return 10;
    }
    if (validSequence(data, 0x4CF2C)) {
        return 12;
    }
    if (validSequence(data, 0x4F628)) {
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
