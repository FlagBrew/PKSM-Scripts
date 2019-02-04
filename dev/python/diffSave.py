#!/usr/bin/env python3
import os
import argparse
from saveVersion import getSaveVersion

# argparse setup
parser = argparse.ArgumentParser(
    description='Generate a list of differences between 2 or more Gen 4-7 Pokémon saves')
parser.add_argument('-o', metavar='outFile',
                    help='File (.txt) to write diff to -- if not given, diff is written to console')
parser.add_argument('-r', '--range', nargs=2, metavar=('start', 'end'),
                    help='Specific range to limit diff to, from start (included) to end (excluded)')
parser.add_argument('-e', action='store_true', help='Flag to include an event diff')
parser.add_argument('saves', nargs='+',
                    help='Space separated list of save files to diff')

# Global variables
split = False
diffs = 0

def toPaddedHexString(value, padTo):
    paddedHex = hex(value)[2:]
    while len(paddedHex) < padTo:
        paddedHex = "0" + paddedHex
    return "0x" + paddedHex[-padTo:]


def loadSaves(fileNames):
    saveData = []
    for i in range(len(fileNames)):
        try:
            with open(fileNames[i], 'rb') as f:
                saveData.append(f.read())
        except OSError:
            print("There was an error reading save %s. Excluding it from diff" % fileNames[i])
            saveData.append(None)
    return saveData


def checkSaveCompat(data):
    # check compatibility based on save size
    saveSizes = [len(data[d]) for d in range(len(data))]
    for i in range(len(saveSizes)):
        if saveSizes[i] != saveSizes[0]:
            return "Saves aren't all the same size."

    # compare version
    versions = [getSaveVersion(len(data[d]), data[d]) for d in range(len(data))]
    if -1 in versions:
        return "One or more save's version couldn't be determined."
    for i in range(len(versions)):
        if (versions[i] >> 1) != (versions[0] >> 1):
            return "Two or more saves come from different version pairings."
    version = versions[0]

    # check number of saves
    if len(data) < 2:
        # allow only 1 save file if it's Gen 4 (DPPtHGSS)
        gen4 = (10, 11, 12, 7, 8)

        # NOTE: testing for Gen 5+ save splitting goes here if made

        if version in gen4 and len(data) == 1:
            global split
            split = True
        else:
            return "Not enough saves were provided and successfully read"

    # all saves compatible
    return ""


def generateDiff(files, data, diffRange):
    diff = []

    # construct diff header
    tableHeader = ["\nOffset   "]
    diff.append("Diff of saves from the following file(s):\n")
    for i in range(len(files)):
        diff.append("\nSave %d: %s" % (i + 1, files[i]))
        tableHeader.append("    Save %d" % (i + 1))
    if split:
        diff.append("\n\nNote: Due to the way Gen 4 saves are stored, data in Save 1 may be more recent than the corresponding data in Save 2")

    # event diffing (function call?) goes here

    # range slicing
    saveData = data
    sliceStart = 0
    if diffRange != None:
        sliceStart = int(diffRange[0], 0)
        for i in range(len(data)):
            saveData[i] = data[i][int(diffRange[0], 0):int(diffRange[1], 0)]
        diff.append("\n\nDiff range: %s-%s" % (diffRange[0], diffRange[1]))

    # construct diff body
    diff.append("\n\n%s\n" % ''.join(tableHeader))
    for i in range(len(saveData[0])):
        offsetDiff = {
            'offset': toPaddedHexString(i + sliceStart, 5),
            'values': []
        }
        offsetDiff['values'] = [toPaddedHexString(data[n][i], 2) for n in range(len(data))]
        for n in range(len(offsetDiff['values'])):
            if offsetDiff['values'][n] != offsetDiff['values'][0]:
                global diffs
                diffs += 1
                diff.append("%s      %s\n" % (offsetDiff['offset'], '      '.join(offsetDiff['values'])))
                break

    # join diff pieces
    return ''.join(diff)


def main(params):
    saveFiles = params.saves

    print("Loading saves...")
    fileBuffs = loadSaves(saveFiles)
    failedFiles = 0
    for i in range(len(fileBuffs)):
        if fileBuffs[i] == None:
            del fileBuffs[i - failedFiles]
            del saveFiles[i - failedFiles]
            failedFiles += 1

    print("Checking compatibility of saves...")
    compatFailReason = checkSaveCompat(fileBuffs)
    if compatFailReason != '':
        print("Save compatibility check failed.\nReason: \"%s\"\nExiting without diffing." % compatFailReason)
        return

    # split lone Gen 4 save
    if split:
        # NOTE: save splitting for Gen 5+ would go here if it ever gets made
        # Multi-gen save splitting logic would probably be abstracted to its own function

        saveData = fileBuffs[0]
        saveName = saveFiles[0]
        fileBuffs.append(saveData[0x40000:])
        fileBuffs[0] = saveData[0:0x40000]
        saveFiles.append("%s (0x40000:0x7ffff)" % saveName)
        saveFiles[0] = "%s (0x00000:0x3ffff)" % saveName

    print("Generating diff...")
    diff = generateDiff(saveFiles, fileBuffs, params.range)

    # output diff
    if diffs == 0:
        print("Saves were identical.%s" % ("" if params.o == None else "%s not written to." % params.o))
    elif params.o != None:
        outDir = ''
        try:
            outDir = os.path.dirname(params.o[0])
            os.makedirs(outDir, exist_ok=True)
        except:
            pass
        outFile = "%s%s" % (params.o[0], "" if params.o[0][-4:] == ".txt" else ".txt")
        with open(outFile, 'w') as f:
            f.write(diff)
        print("Diff written to %s successfully" % outFile)
    else:
        print("\n\n%s" % diff)


# execute if called directly from command line
if __name__ == '__main__':
    main(parser.parse_args())
