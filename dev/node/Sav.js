const fse = require('fs-extra');

const footerDSV = Buffer.from('|-DESMUME SAVE-|');

/**
 * @constructor
 * @param {String} fileName
 */
function Sav(fileName) {
    this.fileName = fileName;
    try {
        this.data = fse.readFileSync(fileName);

        // trim footer from DeSmuME saves
        if (footerDSV.compare(this.data, this.data.length - 16) === 0) {
            this.data = this.data.slice(0, 0x80000);
        }
    } catch (e) {
        console.log(`There was an error reading save ${fileName}.`);
        console.log(e);
        this.data = [];
    }
    this.version = getVersion(this.data.length, this.data);
    this.verGroupAbbr = getVerGroupAbbr(this.version);
    this.generation = getGeneration(this.version);

    // contents metadata
    this.contents = 'full';
    if (this.generation === 4) {
        this.active = {
            general: getActiveGeneralBlock(this),
            storage: getActiveStorageBlock(this),
            hof: 0, // TODO: get proper current HoF block
        };
    } else if (this.generation === 5) {
        this.active = {
            save: 0,
        };
    }
}

module.exports = Sav;

const offsets = {
    'DP': {
        'general': [0, 0xC0FF],
        'storage': [0xC100, 0x1FFFF],
        'hof': [0x20000, 0x3FFFF],
        'eventConst': [0xD9C, 0x40D9C],
        'eventFlag': [0xFDC, 0x40FDC],
    },
    'PT': {
        'general': [0, 0xCF2B],
        'storage': [0xCF2C, 0x1FFFF],
        'hof': [0x20000, 0x3FFFF],
        'eventConst': [0xDAC, 0x40DAC],
        'eventFlag': [0xFEC, 0x40FEC],
    },
    'HGSS': {
        'general': [0, 0xF6FF],
        'storage': [0xF700, 0x22FFF],
        'hof': [0x23000, 0x3FFFF],
        'eventConst': [0xDE4, 0x40DE4],
        'eventFlag': [0x10C4, 0x410C4],
    },
    'BW': {
        'save': [0, 0x23FFF],
        'extra': [0x48000, 0x7FFFF],
        'eventConst': [0x20100, 0x2037B],
        'eventFlag': [0x2037C, 0x204E8],
    },
    'B2W2': {
        'save': [0, 0x25FFF],
        'extra': [0x4C000, 0x7FFFF],
        'eventConst': [0x1FF00, 0x2025D],
        'eventFlag': [0x2025E, 0x203DD],
    },
    'XY': {
        'eventConst': [0x14A00, 0x14CFB],
        'eventFlag': [0x14CFC, 0x14E7C],
    },
    'ORAS': {
        'eventConst': [0x14A00, 0x14CFB],
        'eventFlag': [0x14CFC, 0x14E7C],
    },
    'SM': {
        'eventConst': [0x1C00, 0x23D0],
        'eventFlag': [0x23D0, 0x25C0],
    },
    'USUM': {
        'eventConst': [0x1E00, 0x25CF],
        'eventFlag': [0x25D0, 0x27E9],
    },
};

/*
Helper functions (private)
*/

function ccitt16(save, len) {
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
 * @param {Buffer} saveData
 * @returns {Number}
 */
function getVersion(saveSize, saveData) {
    switch (saveSize) {
        case 0x100000:  // LGPE raw
        case 0xb8800:   // LGPE actual
            // LGP: 42, LGE: 43
            return saveData[0x1004];
        case 0x6cc00:
            // US: 32, UM: 33
            return saveData[0x1404];
        case 0x6be00:
            // Su: 30, Mo: 31
            return saveData[0x1204];
        case 0x76000:
            // AS: 26, OR: 27
            return saveData[0x14004];
        case 0x65600:
            // X: 24, Y: 25
            return saveData[0x14004];
        case 0x80000: // raw DS saves
        case 0x8007A: // DeSmuME saves
        case 0x40000: // split DPPt saves
            // D: 10, P: 11, Pt: 12, HG: 7, SS: 8
            // W: 20, B: 21, W2: 22, B2: 23
            return getDSVersion(saveData);
        default:
            return -1;
    }
}

/**
 * @param {Number} version
 * @returns {Number}
 */
function getGeneration(version) {
    switch (version) {
        case 10: // D
        case 11: // P
        case 12: // PT
        case 7: // HG
        case 8: // SS
            return 4
        case 20: // W
        case 21: // B
        case 22: // W2
        case 23: // B2
            return 5;
        case 24: // X
        case 25: // Y
        case 26: // AS
        case 27: // OR
            return 6;
        case 30: // S
        case 31: // M
        case 32: // US
        case 33: // UM
            return 7;
        case 42: // LGP
        case 43: // LGE
            return 7.5;
        default: // unrecognized save
            return -1;
    }
}

/**
 * @param {Number} version
 * @returns {String}
 */
function getVerGroupAbbr(version) {
    switch (version) {
        case 10: // D
        case 11: // P
            return 'DP';
        case 12: // PT
            return 'PT';
        case 7: // HG
        case 8: // SS
            return 'HGSS';
        case 20: // W
        case 21: // B
            return 'BW';
        case 22: // W2
        case 23: // B2
            return 'B2W2';
        case 24: // X
        case 25: // Y
            return 'XY';
        case 26: // AS
        case 27: // OR
            return 'ORAS';
        case 30: // S
        case 31: // M
            return 'SM';
        case 32: // US
        case 33: // UM
            return 'USUM';
        case 42: // LGP
        case 43: // LGE
            return 'LGPE';
        default:
            return '(unknown version)';
    }
}

/**
 * @param {Sav} save
 * @returns {Number}
 */
function getActiveGeneralBlock(save) {
    const uninit = Buffer.alloc(20, 0).fill(0xff, 10, 20);
    if (uninit.compare(save.data, 0, 10, 0, 10) === 0 || uninit.compare(save.data, 0, 10, 10) === 0) {
        return 1;
    }
    if (uninit.compare(save.data, 0x40000, 10, 0, 10) === 0 || uninit.compare(save.data, 0x40000, 10, 10) === 0) {
        return 0;
    }

    const ofs = getActiveBlockSaveCounterOffset(save);
    const first = save.data.readUInt16LE(ofs) >= save.data.readUInt16LE(ofs + 0x40000);
    return first ? 0 : 1;
}

/**
 * @param {Sav} save
 * @returns {Number}
 */
function getActiveStorageBlock(save) {
    const uninit = Buffer.alloc(20, 0).fill(0xff, 10, 20);
    if (uninit.compare(save.data, 0, 10, 0, 10) === 0 || uninit.compare(save.data, 0, 10, 10) === 0) {
        return 1;
    }
    if (uninit.compare(save.data, 0x40000, 10, 0, 10) === 0 || uninit.compare(save.data, 0x40000, 10, 10) === 0) {
        return 0;
    }

    const ofs = getStorageBlockSaveCounterOffset(save);
    const first = save.data.readUInt16LE(ofs) >= save.data.readUInt16LE(ofs + 0x40000);
    return first ? 0 : 1;
}

/**
 * @param {Sav} save
 * @returns {Number}
 */
function getActiveBlockSaveCounterOffset(save) {
    switch (save.verGroupAbbr) {
        case 'DP': return 0xC0F0;
        case 'PT': return 0xCF1C;
        case 'HGSS': return 0xF618;
        default: return 0;
    }
}

/**
 * @param {Sav} save
 * @returns {Number}
 */
function getStorageBlockSaveCounterOffset(save) {
    switch (save.verGroupAbbr) {
        case 'DP': return 0x1E2D0;
        case 'PT': return 0x1F100;
        case 'HGSS': return 0x21A00;
        default: return 0;
    }
}

/*
Instance methods
*/

/**
 * Returns a Boolean indicating if save can be split
 *
 * @returns {Boolean} true if save can be split, false if not
 */
Sav.prototype.canSplit = function () {
    switch (this.verGroupAbbr) {
        case 'DP':
        case 'PT':
        case 'HGSS':
        case 'BW':
        case 'B2W2':
            return this.data.length >= 0x80000;
        default:
            return false;
    }
};

/**
 * Extract the current save data as a new Buffer
 *
 * @returns {Buffer} Data representing current save state
 */
Sav.prototype.getCurrent = function () {
    let data, general, storage, hof, ofsGen, ofsStor, ofsHOF;
    if (!this.canSplit()) {
        return this.data;
    }
    switch (this.verGroupAbbr) {
        case 'DP':
        case 'PT':
        case 'HGSS':
            ofsGen = Sav.getBlockOffsets(this.verGroupAbbr, 'general').map(v => v + this.active.general * 0x40000);
            ofsStor = Sav.getBlockOffsets(this.verGroupAbbr, 'storage').map(v => v + this.active.storage * 0x40000);
            ofsHOF = Sav.getBlockOffsets(this.verGroupAbbr, 'hof').map(v => v + this.active.hof * 0x40000);
            general = this.data.slice(ofsGen[0], ofsGen[1] + 1);
            storage = this.data.slice(ofsStor[0], ofsStor[1] + 1);
            hof = this.data.slice(ofsHOF[0], ofsHOF[1] + 1); // length: 0x2AB0?
            data = Buffer.concat([general, storage, hof], 0x40000);
            return data;
        case 'BW':
        case 'B2W2':
            data = this.data.slice(0, Sav.getBlockOffsets(this.verGroupAbbr, 'save')[1] + 1);
            general = this.data.slice(Sav.getBlockOffsets(this.verGroupAbbr, 'extra')[0]);
            return Buffer.concat([data, general], this.verGroupAbbr === 'BW' ? 0x38000 : 0x34000);
        default:
            // this case should never happen
            return this.data;
    }
};

/**
 * Extract the backup save data as a new Buffer
 *
 * @returns {Buffer} Data representing backup save state
 */
Sav.prototype.getBackup = function () {
    let data, general, storage, hof, ofsGen, ofsStor, ofsHOF;
    if (!this.canSplit()) {
        return this.data;
    }
    switch (this.verGroupAbbr) {
        case 'DP':
        case 'PT':
        case 'HGSS':
            ofsGen = Sav.getBlockOffsets(this.verGroupAbbr, 'general').map(v => v + (1 - this.active.general) * 0x40000);
            ofsStor = Sav.getBlockOffsets(this.verGroupAbbr, 'storage').map(v => v + (1 - this.active.storage) * 0x40000);
            ofsHOF = Sav.getBlockOffsets(this.verGroupAbbr, 'hof').map(v => v + (1 - this.active.hof) * 0x40000);
            general = this.data.slice(ofsGen[0], ofsGen[1] + 1);
            storage = this.data.slice(ofsStor[0], ofsStor[1] + 1);
            hof = this.data.slice(ofsHOF[0], ofsHOF[1] + 1); // length: 0x2AB0?
            data = Buffer.concat([general, storage, hof], 0x40000);
            return data;
        case 'BW':
        case 'B2W2':
            return this.data.slice(Sav.getBlockOffsets(this.verGroupAbbr, 'save')[1] + 1);
        default:
            // this case should never happen
            return this.data;
    }
};

/*
Class methods
*/

/**
 * Split the save at `arr[ind]`, keeping the current save data and
 * optionally keeping the backup save data
 *
 * @param {Sav[]} arr Array of Sav objects
 * @param {Number} ind Index in arr of save to be split
 * @param {Boolean} keepOld Whether the backup should be kept
 */
Sav.splitSave = function (arr, ind, keepOld) {
    const save = arr[ind];
    if (!save.canSplit()) {
        // "unable to split save" response
        return;
    }
    save.data = save.getCurrent();
    save.contents = 'current';
    if (keepOld) {
        const secondSav = new Sav(save.fileName);
        secondSav.data = secondSav.getBackup();
        secondSav.contents = 'backup';
        if (secondSav.generation === 4) {
            secondSav.active = {
                general: (1 - save.active.general),
                storage: (1 - save.active.storage),
                hof: (1 - save.active.hof),
            };
        } else if (secondSav.generation === 5) {
            secondSav.active = {
                save: 1,
            };
        }
        arr.splice(ind, 0, secondSav);
    }
};

/**
 * Makes sure all saves come from the same version group
 *
 * @param {Sav[]} saves Array of Sav objects to check for compatibility
 * @returns {String} String detailing reason for save incompatibility (if any)
 */
Sav.checkCompat = function (saves) {
    if (saves.length < 1) {
        return 'Not enough saves were provided and successfully read.';
    }
    // compare version
    if (saves.some((v, i, a) => v.verGroupAbbr !== a[0].verGroupAbbr)) {
        return 'Two or more saves come from different version groups.';
    }
    return '';
};

/**
 * @param {String} verGroupAbbr Save version group abbreviation
 * @param {String} block Which block's offsets are being requested
 * @returns {Number[]} Array of start and end (inclusive) offsets of block
 */
Sav.getBlockOffsets = function (verGroupAbbr, block) {
    return offsets[verGroupAbbr][block];
};
