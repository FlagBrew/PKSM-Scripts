#!/usr/bin/env python3


def readUInt16LE(data, offset=0):
    return (data[offset + 1] << 8) + data[offset]


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


def validSequence(data, pattern, shift=0):
    ofs = readUInt16LE(pattern, 0) - 0xc + shift
    for i in range(10):
        if data[i + ofs] != pattern[i]:
            return False
    return True


def getDSVersion(data):
    chk = readUInt16LE(data, 0x24000 - 0x100 + 0x8c + 0xe)
    actual = ccitt16(data[0x24000-0x100:], 0x8c)
    if chk == actual:
        return data[0x1941f]

    chk = readUInt16LE(data, 0x26000 - 0x100 + 0x94 + 0xe)
    actual = ccitt16(data[0x26000-0x100:], 0x94)
    if chk == actual:
        return data[0x1941f]

    if readUInt16LE(data, 0xc0fe) == ccitt16(data, 0xc0ec):
        return 10
    if readUInt16LE(data, 0xcf2a) == ccitt16(data, 0xcf18):
        return 12
    if readUInt16LE(data, 0xf626) == ccitt16(data, 0xf618):
        return 7

    dpPattern = (0x00, 0xC1, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00)
    ptPattern = (0x2C, 0xCF, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00)
    hgssPattern = (0x28, 0xF6, 0x00, 0x00, 0x23, 0x06, 0x06, 0x20, 0x00, 0x00)
    if validSequence(data, dpPattern):
        return 10
    if validSequence(data, ptPattern):
        return 12
    if validSequence(data, hgssPattern):
        return 7

    if validSequence(data, dpPattern, 0x40000):
        return 10
    if validSequence(data, ptPattern, 0x40000):
        return 12
    if validSequence(data, hgssPattern, 0x40000):
        return 7
    return -1


def getSaveVersion(saveSize, saveData=None):
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
    if saveSize == 0x80000:
        # D: 10, P: 11, Pt: 12, HG: 7, SS: 8
        # W: 20, B: 21, W2: 22, B2: 23
        if saveData: return getDSVersion(saveData)
        else: return 10
    if saveSize == 0xb8800 or saveSize == 0x100000:
        # LGP: 42, LGE: 43
        if saveData: return saveData[0x1004]
        else: return 42
    return -1


if __name__ == "__main__":
    pass
