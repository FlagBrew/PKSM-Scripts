#!/usr/bin/env python3
import argparse
import os

import Sav
from diffEvent import generateDiff as diffEvent

# argparse setup
parser = argparse.ArgumentParser(
    description='Generate a list of differences between 2 or more Gen 4-7 Pokémon saves')
parser.add_argument('-o', metavar='outFile',
                    help='File (.txt) to write diff to -- if not given, diff is written to console')
parser.add_argument('-r', '--range', nargs=2, metavar=('start', 'end'),
                    help='Specific range to limit diff to, from start (included) to end (excluded)')
parser.add_argument('-e', action='store_true', help='Flag to include an event diff')
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument('-d', '--dir', metavar='dir', nargs='+',
                    help='Directory (folder) containing files to diff')
group.add_argument('-s', '--saves', nargs='+',
                    help='Space separated list of save files to diff')

# Global variables
split = False
diffs = 0

def _toPaddedHexString(value, padTo):
    paddedHex = hex(value)[2:]
    while len(paddedHex) < padTo:
        paddedHex = "0" + paddedHex
    return "0x" + paddedHex[-padTo:]


def generateDiff(files, data, diffRange, eventDiff):
    diff = []
    global diffs

    # construct diff header
    tableHeader = ["\nOffset   "]
    diff.append("Diff of saves from the following file(s):\n\n")
    for i in range(len(files)):
        diff.append("Save %d: %s\n" % (i + 1, files[i]))
        tableHeader.append("    Save %d" % (i + 1))

    if len(data[0]) == 0x40000:
        diff.append("\nNote: Due to the way Gen 4 saves are stored, data in Save 1 may be more recent than the corresponding data in Save 2")

    # event diffing (function call?) goes here
    if eventDiff:
        eDiff = diffEvent(files, data)
        if eDiff == '':
            print('Event diff failed.')
        else:
            diffs += 0 if eDiff[0] == 'E' else 1
            diff.append("\n%s" % eDiff)

    # range slicing
    saveData = data
    sliceStart = 0
    if diffRange != None:
        sliceStart = int(diffRange[0], 0)
        for i in range(len(data)):
            saveData[i] = data[i][sliceStart:int(diffRange[1], 0)]
        diff.append("\n\nDiff range: %s-%s" % (diffRange[0], diffRange[1]))

    # construct diff body
    diff.append("\n\n%s\n" % ''.join(tableHeader))
    for i in range(len(saveData[0])):
        offsetDiff = {
            'offset': _toPaddedHexString(i + sliceStart, 5),
            'values': []
        }
        offsetDiff['values'] = [_toPaddedHexString(data[n][i], 2) for n in range(len(data))]
        for n in range(len(offsetDiff['values'])):
            if offsetDiff['values'][n] != offsetDiff['values'][0]:
                diffs += 1
                diff.append("%s      %s\n" % (offsetDiff['offset'], '      '.join(offsetDiff['values'])))
                break

    # join diff pieces
    return ''.join(diff)


def main(params):
    saveFiles = params.saves

    print("Loading saves...")
    fileBuffs = Sav.loadSaves(saveFiles)
    failedFiles = 0
    for i in range(len(fileBuffs)):
        if fileBuffs[i] == None:
            del fileBuffs[i - failedFiles]
            del saveFiles[i - failedFiles]
            failedFiles += 1

    print("Checking compatibility of saves...")
    compatFailReason = Sav.checkCompat(fileBuffs)
    if compatFailReason != '':
        print("Save compatibility check failed.\nReason: \"%s\"\nExiting without diffing." % compatFailReason)
        return

    # split lone Gen 4 save
    if len(fileBuffs) == 1:
        split = Sav.canSplit(fileBuffs[0])
        if not split:
            print("Cannot split a single save file from this game. Exiting without diffing.")
            return
        Sav.splitSave(saveFiles, fileBuffs)

    print("Generating diff...")
    diff = generateDiff(saveFiles, fileBuffs, params.range, params.e)

    # output diff
    if diffs == 0:
        print("Saves were identical.%s" % ("" if params.o == None else " %s not written to." % params.o))
    elif params.o != None:
        outDir = ''
        try:
            outDir = os.path.dirname(params.o[0])
            os.makedirs(outDir, exist_ok=True)
        except:
            pass
        outFile = "%s%s" % (params.o, "" if params.o[-4:] == ".txt" else ".txt")
        with open(outFile, 'w') as f:
            f.write(diff)
        print("Diff written to %s successfully" % outFile)
    else:
        print("\n\n%s" % diff)


# execute if called directly from command line
if __name__ == '__main__':
    params = parser.parse_args()
    if params.dir != None:
        if params.saves == None:
            params.saves = []
        for d in range(len(params.dir)):
            for path, _, files in os.walk(params.dir[d]):
                for fullname in files:
                    params.saves.append(os.path.normpath(os.path.join(path, fullname)))
    main(params)
