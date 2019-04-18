#!/usr/bin/env python3
import math
import argparse
import os

from Sav import Sav
from diffEvent import generateDiff as diffEvent

# argparse setup
parser = argparse.ArgumentParser(
    description='Generate a list of differences between 2 or more Gen 4-7 Pokémon saves')
parser.add_argument('-o', metavar='outFile',
                    help='File (.txt) to write diff to -- if not given, diff is written to console')
parser.add_argument('-r', '--range', nargs=2, metavar=('start', 'end'),
                    help='Specific range to limit diff to, from start (included) to end (excluded)')
# Length-based range diffing
# parser.add_argument('-l', action='append', nargs=2, metavar=('start', 'length'),
#                     help='Specific range to limit diff to, length number of bytes beginning at start')
# Diff full file rather than just current save data (of split-able save file types)
# parser.add_argument('-f', action='store_true',
#                     help='Use full save file (of saves that can be split) in diff rather than just current save data')
parser.add_argument('-e', action='store_true',
                    help='Flag to include an event diff')
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument('-d', '--dir', metavar='dir', nargs='+',
                   help='Directory (folder) containing files to diff')
group.add_argument('-s', '--saves', nargs='+',
                   help='Space separated list of save files to diff')

# Global variables
diffs = 0


def _toPaddedHexString(value, padTo):
    paddedHex = hex(value)[2:]
    while len(paddedHex) < padTo:
        paddedHex = "0" + paddedHex
    return "0x" + paddedHex[-padTo:]


def generateDiff(saves, config):
    diff = []
    global diffs

    ofs = {
        'general': [0],
        'storage': [0],
        'hof': [0],
        'save': [0],
        'extra': [0]
    }
    if saves[0].generation == 4:
        ofs['general'] = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'general')
        ofs['storage'] = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'storage')
        ofs['hof'] = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'hof')
    elif saves[0].generation == 5:
        ofs['save'] = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'save')
        ofs['extra'] = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'extra')

    # construct diff header
    tableHeader = ["\nOffset   "]
    diff.append("Diff of saves from the following file(s):\n\n")
    for i in range(len(saves)):
        contents = '' if saves[i].contents == 'full' else ' (%s)' % saves[i].contents
        diff.append("Save %d: %s%s\n" % (i + 1, saves[i].fileName, contents))

        if config['isSplit']:
            if saves[i].generation == 4:
                compOfs = [_toPaddedHexString(n + saves[i].active['general'] * 0x40000, 5) for n in ofs['general']]
                diff.append("    General: %s\n" % ':'.join(compOfs))
                compOfs = [_toPaddedHexString(n + saves[i].active['storage'] * 0x40000, 5) for n in ofs['storage']]
                diff.append("    Storage: %s\n" % ':'.join(compOfs))
                compOfs = [_toPaddedHexString(n + saves[i].active['hof'] * 0x40000, 5) for n in ofs['hof']]
                diff.append("    HoF:     %s\n" % ':'.join(compOfs))
            elif saves[i].verGroupAbbr == 'BW':
                compOfs = [_toPaddedHexString(n + saves[i].active['save'] * 0x24000, 5) for n in ofs['save']]
                diff.append("    Save:  %s\n" % ':'.join(compOfs))
                compOfs = [_toPaddedHexString(n + saves[i].active['extra'] * 0x24000, 5) for n in ofs['extra']]
                diff.append("    Extra: %s\n" % ':'.join(compOfs))
            elif saves[i].verGroupAbbr == 'B2W2':
                compOfs = [_toPaddedHexString(n + saves[i].active['save'] * 0x26000, 5) for n in ofs['save']]
                diff.append("    Save:  %s\n" % ':'.join(compOfs))
                compOfs = [_toPaddedHexString(n + saves[i].active['extra'] * 0x26000, 5) for n in ofs['extra']]
                diff.append("    Extra: %s\n" % ':'.join(compOfs))
            else:
                print('How did you split this input?')

        digStr = "    Save %d" % (i + 1)
        digits = 10
        if i % 10 == 9:
            digits += (math.floor(math.log10(i + 1)) != math.floor(math.log10(i)))
        tableHeader.append(digStr[-digits:])

    if saves[0].generation == 4 and config['isSplit']:
        diff.append(
            "\nNote: HoF block of Save 1 may be more recent than the HoF block of Save 2\n")

    # event diffing (function call?) goes here
    if config['event']:
        eDiff = diffEvent(saves)
        if eDiff == '':
            print('Event diff failed.')
        else:
            diffs += 0 if eDiff[:25] == 'Event flags and constants' else 1
            diff.append("\n%s" % eDiff)

    # range slicing
    slicedData = [saves[i].data for i in range(len(saves))]
    sliceStart = 0
    if config['range'] != None:
        sliceStart = int(config['range'][0], 0)
        for i in range(len(slicedData)):
            slicedData[i] = slicedData[i][sliceStart:int(config['range'][1], 0)]
        diff.append("\n\nDiff range: %s-%s" % (config['range'][0], config['range'][1]))

    # construct diff body
    diff.append("\n\n%s\n" % ''.join(tableHeader))
    for n in range(len(slicedData[0])):
        offsetDiff = {
            'offset': _toPaddedHexString(n + sliceStart, 5),
            'values': []
        }
        if config['isSplit'] and saves[0].generation == 5:
            if n > ofs['save'][1]:
                offsetDiff['offset'] = _toPaddedHexString(n + sliceStart + ofs['save'][1] + 1, 2)
            pass
        offsetDiff['values'] = [_toPaddedHexString(
            slicedData[i][n], 2) for i in range(len(slicedData))]
        for i in range(len(offsetDiff['values'])):
            if offsetDiff['values'][i] != offsetDiff['values'][0]:
                diffs += 1
                diff.append("%s      %s\n" % (
                    offsetDiff['offset'], '      '.join(offsetDiff['values'])))
                break

    # join diff pieces
    return ''.join(diff)


def main(params):
    config = {
        'range': params.range,
        'event': params.e,
        'isSplit': False
    }

    print("Loading saves...")
    saves = [Sav(f) for f in params.saves]
    saves = [s for s in saves if s.version != -1]

    print("Checking compatibility of saves...")
    compatFailReason = Sav.checkCompat(saves)
    if compatFailReason != '':
        print("Save compatibility check failed.\nReason: \"%s\"\nExiting without diffing." %
              compatFailReason)
        return

    # split lone Gen 4 save
    if len(saves) == 1:
        if not saves[0].canSplit():
            print(
                "Cannot split a single %s save file. Exiting without diffing." % saves[0].verGroupAbbr)
            return
        # split lone save
        Sav.splitSave(saves, 0, True)
        config['isSplit'] = True

    print("Generating diff...")
    diff = generateDiff(saves, config)

    # output diff
    if diffs == 0:
        print("Saves were identical.%s" %
              ("" if params.o == None else " %s not written to." % params.o))
    elif params.o != None:
        outDir = ''
        try:
            outDir = os.path.dirname(params.o[0])
            os.makedirs(outDir, exist_ok=True)
        except:
            pass
        outFile = "%s%s" % (
            params.o, "" if params.o[-4:] == ".txt" else ".txt")
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
            dirFiles = []
            for path, _, files in os.walk(params.dir[d]):
                for fullname in files:
                    dirFiles.append(os.path.normpath(
                        os.path.join(path, fullname)))
            dirFiles.sort(key=str.lower)
            params.saves.extend(dirFiles)
    main(params)
