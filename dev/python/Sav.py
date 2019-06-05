#!/usr/bin/env python3
import struct

class Sav:
    _footerDSV = b'|-DESMUME SAVE-|'
    _offsets = {
        'DP': {
            'general': [0, 0xC0FF],
            'storage': [0xC100, 0x1FFFF],
            'hof': [0x20000, 0x3FFFF],
            'eventConst': [0xD9C, 0xFDC],
            'eventFlag': [0xFDC, 0x1148],
        },
        'PT': {
            'general': [0, 0xCF2B],
            'storage': [0xCF2C, 0x1FFFF],
            'hof': [0x20000, 0x3FFFF],
            'eventConst': [0xDAC, 0xFEC],
            'eventFlag': [0xFEC, 0x1158],
        },
        'HGSS': {
            'general': [0, 0xF6FF],
            'storage': [0xF700, 0x22FFF],
            'hof': [0x23000, 0x3FFFF],
            'eventConst': [0xDE4, 0x10C4],
            'eventFlag': [0x10C4, 0x1230],
        },
        'BW': {
            'save': [0, 0x23FFF],
            'extra': [0x48000, 0x7FFFF],
            'eventConst': [0x20100, 0x2037C],
            'eventFlag': [0x2037C, 0x204E8],
        },
        'B2W2': {
            'save': [0, 0x25FFF],
            'extra': [0x4C000, 0x7FFFF],
            'eventConst': [0x1FF00, 0x2025E],
            'eventFlag': [0x2025E, 0x203DD],
        },
        'XY': {
            'eventConst': [0x14A00, 0x14CFC],
            'eventFlag': [0x14CFC, 0x14E7B],
        },
        'ORAS': {
            'eventConst': [0x14A00, 0x14CFC],
            'eventFlag': [0x14CFC, 0x14E7B],
        },
        'SM': {
            'eventConst': [0x1C00, 0x23D0],
            'eventFlag': [0x23D0, 0x25C0],
        },
        'USUM': {
            'eventConst': [0x1E00, 0x25D0],
            'eventFlag': [0x25D0, 0x2838], # end == 0x27e9?
        }
    }

    def __init__(self, fileName):
        self.fileName = fileName
        try:
            with open(fileName, 'rb') as f:
                self.data = f.read()
            if self.data[-16:] == Sav._footerDSV:
                self.data = self.data[:0x80000]
        except OSError:
            print('There was an error reading save "{}"'.format(fileName))
            self.data = []
        self.version = self._getVersion()
        self.verGroupAbbr = self._getVerGroupAbbr()
        self.generation = self._getGeneration()
        self.contents = "full"

        self.active = {
            'general': 0,
            'storage': 0,
            'hof': 0,
            'save': 0
        }
        if self.generation == 4:
            self.active['general'] = self._getActiveGeneralBlock()
            self.active['storage'] = self._getActiveStorageBlock()

    def canSplit(self):
        if self.verGroupAbbr in ['DP', 'PT', 'HGSS', 'BW', 'B2W2']:
            return len(self.data) >= 0x80000
        else:
            return False

    def _getActiveBlockSaveCounterOffset(self):
        if self.verGroupAbbr == 'DP':
            return 0xC0F0
        if self.verGroupAbbr == 'PT':
            return 0xCF1C
        if self.verGroupAbbr == 'HGSS':
            return 0xF618
        return 0

    def _getStorageBlockSaveCounterOffset(self):
        if self.verGroupAbbr == 'DP':
            return 0x1E2D0
        if self.verGroupAbbr == 'PT':
            return 0x1F100
        if self.verGroupAbbr == 'HGSS':
            return 0x21A00
        return 0

    def _getActiveGeneralBlock(self):
        if self.data[:10].count(0) == 10 or self.data[:10].count(0xff) == 10:
            return 1
        if self.data[0x40000:0x4000A].count(0) == 10 or self.data[0x40000:0x4000A].count(0xff) == 10:
            return 0
        ofs = self._getActiveBlockSaveCounterOffset()
        first = struct.unpack('<H', self.data[ofs:ofs + 2])[0] >= struct.unpack('<H', self.data[ofs + 0x40000:ofs + 0x40000 + 2])[0]
        return 0 if first else 1

    def _getActiveStorageBlock(self):
        if self.data[:10].count(0) == 10 or self.data[:10].count(0xff) == 10:
            return 1
        if self.data[0x40000:0x4000A].count(0) == 10 or self.data[0x40000:0x4000A].count(0xff) == 10:
            return 0
        ofs = self._getStorageBlockSaveCounterOffset()
        first = struct.unpack('<H', self.data[ofs:ofs + 2])[0] >= struct.unpack('<H', self.data[ofs + 0x40000:ofs + 0x40000 + 2])[0]
        return 0 if first else 1

    def getCurrent(self):
        if not self.canSplit():
            return self.data
        if self.generation == 4:
            ofsGen = [i + self.active['general'] * 0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'general')]
            ofsStor = [i + self.active['storage'] * 0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'storage')]
            ofsHOF = [i + self.active['hof'] * 0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'hof')]
            general = self.data[ofsGen[0]:ofsGen[1] + 1]
            storage = self.data[ofsStor[0]:ofsStor[1] + 1]
            hof = self.data[ofsHOF[0]:ofsHOF[1] + 1]
            return general + storage + hof
        if self.generation == 5:
            data = self.data[:self.getBlockOffsets(self.verGroupAbbr, 'save')[1] + 1]
            general = self.data[self.getBlockOffsets(self.verGroupAbbr, 'extra')[0]:]
            return data + general
        else:
            return self.data

    def getBackup(self):
        if not self.canSplit():
            return self.data
        if self.generation == 4:
            ofsGen = [i + (1 - self.active['general']) *
                      0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'general')]
            ofsStor = [i + (1 - self.active['storage']) *
                       0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'storage')]
            ofsHOF = [i + (1 - self.active['hof']) *
                      0x40000 for i in self.getBlockOffsets(self.verGroupAbbr, 'hof')]
            general = self.data[ofsGen[0]:ofsGen[1] + 1]
            storage = self.data[ofsStor[0]:ofsStor[1] + 1]
            hof = self.data[ofsHOF[0]:ofsHOF[1] + 1]
            return general + storage + hof
        if self.generation == 5:
            return self.data[self.getBlockOffsets(self.verGroupAbbr, 'save')[1] + 1:]
        else:
            return self.data

    def _getVersion(self):
        def getDSVersion(data):
            def ccitt16(save, length):
                crc = 0xffff
                for i in range(length):
                    crc ^= (save[i] << 8)
                    for j in range(0x8):
                        if (crc & 0x8000) > 0:
                            crc = ((crc << 1) ^ 0x1021) & 0xffff
                        else:
                            crc <<= 1
                return crc

            def validSequence(data, offset):
                # '<I': uint32
                size = struct.unpack('<I', data[offset - 0xC:][:4])[0]
                if size != (offset & 0xffff):
                    return False
                sdk = struct.unpack('<I', data[offset - 0x8:][:4])[0]
                dateInt = 0x20060623
                dateKor = 0x20070903
                return sdk == dateInt or sdk == dateKor


            # '<H': uint16
            chk = struct.unpack('<H', data[0x24000 - 0x100 + 0x8c + 0xe:][:2])[0]
            actual = ccitt16(data[0x24000-0x100:], 0x8c)
            if chk == actual:
                return data[0x1941f]

            chk = struct.unpack('<H', data[0x26000 - 0x100 + 0x94 + 0xe:][:2])[0]
            actual = ccitt16(data[0x26000-0x100:], 0x94)
            if chk == actual:
                return data[0x1941f]

            offset = 0 if len(data) == 0x40000 else 0x40000
            if validSequence(data, offset + 0xc100):
                return 10
            if validSequence(data, offset + 0xcf2c):
                return 12
            if validSequence(data, offset + 0xf628):
                return 7

            print("Unrecognized save")
            return -1

        if len(self.data) in [0xb8800, 0x100000]:
            # LGP: 42, LGE: 43
            return self.data[0x1004]
        if len(self.data) == 0x6cc00:
            # US: 32, UM: 33
            return self.data[0x1404]
        if len(self.data) == 0x6be00:
            # Su: 30, Mo: 31
            return self.data[0x1204]
        if len(self.data) in [0x76000, 0x65600]:
            # 0x76000: AS: 26, OR: 27
            # 0x65600: X: 24, Y: 25
            return self.data[0x14004]
        if len(self.data) == 0x80000:
            # raw: 0x80000, DeSmuME: 0x8007A, Gen 4 split: 0x40000
            # D: 10, P: 11, Pt: 12, HG: 7, SS: 8
            # W: 20, B: 21, W2: 22, B2: 23
            return getDSVersion(self.data)
        return -1

    def _getVerGroupAbbr(self):
        if self.version in [10, 11]:
            return 'DP'
        elif self.version == 12:
            return 'PT'
        elif self.version in [7, 8]:
            return 'HGSS'
        elif self.version in [20, 21]:
            return 'BW'
        elif self.version in [22, 23]:
            return 'B2W2'
        elif self.version in [24, 25]:
            return 'XY'
        elif self.version in [26, 27]:
            return 'ORAS'
        elif self.version in [30, 31]:
            return 'SM'
        elif self.version in [32, 33]:
            return 'USUM'
        elif self.version in [42, 43]:
            return 'LGPE'
        else:
            return '(unknown version)'

    def _getGeneration(self):
        if self.version in [10, 11, 12, 7, 8]:
            return 4
        elif self.version in [20, 21, 22, 23]:
            return 5
        elif self.version in [24, 25, 26, 27]:
            return 6
        elif self.version in [30, 31, 32, 33]:
            return 7
        elif self.version in [42, 43]:
            return 7.5
        else:
            return -1


    @staticmethod
    def splitSave(arr, ind, keepOld):
        save = arr[ind]
        if not save.canSplit():
            return
        save.data = save.getCurrent()
        save.contents = "current"
        if keepOld:
            secondSav = Sav(save.fileName)
            secondSav.data = secondSav.getBackup()
            secondSav.contents = "backup"
            if secondSav.generation == 4:
                secondSav.active['general'] = 1 - save.active['general']
                secondSav.active['storage'] = 1 - save.active['storage']
                secondSav.active['hof'] = 1 - save.active['hof']
            elif secondSav.generation == 5:
                secondSav.active['save'] = 1
            arr.insert(ind, secondSav)

    @staticmethod
    def checkCompat(saves):
        if len(saves) < 1:
            return "Not enough saves were provided and successfully read."
        # compare version groups
        for i in range(len(saves)):
            if saves[i].verGroupAbbr != saves[0].verGroupAbbr:
                return "Two or more saves come from different version groups."
        # all saves compatible
        return ""

    @staticmethod
    def getBlockOffsets(verGroupAbbr, block):
        return Sav._offsets[verGroupAbbr][block]
