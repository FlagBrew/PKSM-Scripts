#!/usr/bin/env python3
import struct

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


def getDSVersion(data):
    def validSequence(data, offset):
        # '<I': uint32
        size = struct.unpack('<I', data[offset - 0xC:][:4])[0]
        if size != (offset & 0xffff):
            return False
        sdk = struct.unpack('<I', data[offset - 0x8:][:4])[0]
        dateInt = 0x20060623
        dateKor = 0x20070903
        return sdk == dateInt or sdk == dateKor


    # '<I': uint16
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


def getVersion(saveSize, saveData=None):
    if saveSize == 0xb8800 or saveSize == 0x100000:
        # LGP: 42, LGE: 43
        if saveData: return saveData[0x1004]
        else: return 42
    if saveSize == 0x6cc00:
        # US: 32, UM: 33
        if saveData: return saveData[0x1404]
        else: return 32
    if saveSize == 0x6be00:
        # Su: 30, Mo: 31
        if saveData: return saveData[0x1204]
        else: return 30
    if saveSize == 0x76000:
        # AS: 26, OR: 27
        if saveData: return saveData[0x14004]
        else: return 26
    if saveSize == 0x65600:
        # X: 24, Y: 25
        if saveData: return saveData[0x14004]
        else: return 24
    if saveSize == 0x80000 or saveSize == 0x40000:
        # D: 10, P: 11, Pt: 12, HG: 7, SS: 8
        # W: 20, B: 21, W2: 22, B2: 23
        # raw: 0x80000, Gen 4 split: 0x40000
        if saveData: return getDSVersion(saveData)
        else: return 10
    return -1


def checkCompat(data):
    if len(data) < 1:
        return "Not enough saves were provided and successfully read."

    # compare version
    versions = [getVersion(len(data[d]), data[d]) for d in range(len(data))]
    if -1 in versions:
        return "One or more save's version couldn't be determined."
    for i in range(len(versions)):
        if (versions[i] >> 1) != (versions[0] >> 1):
            return "Two or more saves come from different version pairings."

    # all saves compatible
    return ""


def loadSaves(fileNames):
    saveData = []
    for i in range(len(fileNames)):
        try:
            with open(fileNames[i], 'rb') as f:
                saveData.append(f.read())
        except OSError:
            print(
                "There was an error reading save %s. Excluding it from diff" % fileNames[i])
            saveData.append(None)
    return saveData


def canSplit(data):
    canBeSplit = (10, 11, 12, 7, 8)

    version = getVersion(len(data), data)
    if version in canBeSplit:
        return True
    return False


def splitSave(saveFiles, fileBuffs):
    saveName = saveFiles[0]
    saveData = fileBuffs[0]

    version = getVersion(len(saveData), saveData)
    if version in (10, 11, 12, 7, 8):
        fileBuffs.append(saveData[0x40000:])
        fileBuffs[0] = saveData[0:0x40000]
        saveFiles.append("%s (0x40000:0x7ffff)" % saveName)
        saveFiles[0] = "%s (0x00000:0x3ffff)" % saveName
    else:
        print("Cannot split this type of save.")


if __name__ == "__main__":
    pass
