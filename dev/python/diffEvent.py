#!/usr/bin/env python3
import argparse
import math
import os

from Sav import Sav

# argparse setup
parser = argparse.ArgumentParser(
    description='Generate a list of differences in the event flags and event constants of 2 or more Gen 4-7 Pokémon save files')
parser.add_argument('-o', metavar='outFile',
                    help='File (.txt) to write diff to -- if not given, diff is written to console')
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument('-d', '--dir', metavar='dir', nargs='+',
                   help='Directory (folder) containing files to diff')
group.add_argument('-s', '--saves', nargs='+',
                   help='Space separated list of save files to diff')

# Global variables
diffs = 0
cli = __name__ == '__main__'


def _getVersionEventInfo(version):
    if version == 'DP':
        return {
            'constStart': 0xd9c,
            'constCount': 288,
            'flagStart': 0xfdc,
            'flagCount': 2912
        }
    elif version == 'PT':
        return {
            'constStart': 0xdac,
            'constCount': 288,
            'flagStart': 0xfec,
            'flagCount': 2912
        }
    elif version == 'HGSS':
        return {
            'constStart': 0xde4,
            'constCount': 368,
            'flagStart': 0x10c4,
            'flagCount': 2912
        }
    elif version == 'BW':
        return {
            'constStart': 0x20100,
            'constCount': 318,
            'flagStart': 0x2037c,
            'flagCount': 2912
        }
    elif version == 'B2W2':
        return {
            'constStart': 0x1ff00,
            'constCount': 431,
            'flagStart': 0x2025e,
            'flagCount': 3064
        }
    elif version in ('XY', 'ORAS'):
        return {
            'constStart': 0x14a00,
            'constCount': 382,
            'flagStart': 0x14cfc,
            'flagCount': 3072
        }
    elif version == 'SM':
        return {
            'constStart': 0x1c00,
            'constCount': 1000,
            'flagStart': 0x23d0,
            'flagCount': 3968
        }
    elif version == 'USUM':
        return {
            'constStart': 0x1e00,
            'constCount': 1000,
            'flagStart': 0x25d0,
            'flagCount': 4928
        }
    else:
        # TODO: come up with error handling for other versions
        pass


def _diffEventFlags(eFlagData):
    flagDiffs = {
        'set': [],
        'setToggle': [],
        'unset': [],
        'unsetToggle': [],
        'toggle': []
    }
    flagDiffCount = 0
    for n in range(len(eFlagData[0])):
        flagDiff = {
            'num': ("000%s" % n)[-4:],
            'values': []
        }
        for i in range(len(eFlagData)):
            flagDiff['values'].append(eFlagData[i][n])
        changes = 0
        for i in range(len(flagDiff['values'])):
            if i > 0 and flagDiff['values'][i] != flagDiff['values'][i - 1]:
                changes += 1
        if changes > 0:
            flagDiffCount += 1
            if flagDiff['values'][0] == flagDiff['values'][-1]:
                flagDiffs['toggle'].append(flagDiff['num'])
            elif changes == 1:
                flagDiffs['set' if flagDiff['values'][-1]
                          else 'unset'].append(flagDiff['num'])
            else:
                flagDiffs['setToggle' if flagDiff['values'][-1]
                          else 'unsetToggle'].append(flagDiff['num'])

    if flagDiffCount > 0:
        flagDiffData = ['\nEvent Flag Diff\n']

        if len(flagDiffs['set']) > 0:
            flagDiffData.append("Set: %s\n" % ', '.join(flagDiffs['set']))
        if len(flagDiffs['unset']) > 0:
            flagDiffData.append("Unset: %s\n" % ', '.join(flagDiffs['unset']))
        if len(flagDiffs['setToggle']) > 0:
            flagDiffData.append("Set (toggled): %s\n" %
                                ', '.join(flagDiffs['setToggle']))
        if len(flagDiffs['unsetToggle']) > 0:
            flagDiffData.append("Unset (toggled): %s\n" %
                                ', '.join(flagDiffs['unsetToggle']))
        if len(flagDiffs['toggle']) > 0:
            flagDiffData.append("Toggled: %s\n" % ', '.join(flagDiffs['toggle']))

        return '\n'.join(flagDiffData)
    return '\nEvent flags are identical.\n'


def _diffEventConst(eConstData):
    constDiffs = []
    for n in range(len(eConstData[0])):
        constDiff = {
            'num': "%s    " % n,
            'values': []
        }
        for i in range(len(eConstData)):
            constDiff['values'].append(("%s     " % eConstData[i][n])[:6])
        for i in range(len(constDiff['values'])):
            if constDiff['values'][i] != constDiff['values'][0]:
                line = [constDiff['num'][:5]]
                line.extend(constDiff['values'])
                line = '    '.join(line).strip()
                constDiffs.append("%s\n" % line)
                break
    if len(constDiffs) > 0:
        eConstHeader = ['\nEvent Const Diff\n\nConst']
        for i in range(len(eConstData)):
            digStr = "    Save %d" % (i + 1)
            digits = 10
            if i % 10 == 9:
                digits += (math.floor(math.log10(i + 1)) != math.floor(math.log10(i)))
            eConstHeader.append(digStr[-digits:])
        eConstHeader.append('\n')
        constDiffs.insert(0, ''.join(eConstHeader))
        return ''.join(constDiffs)
    return '\nEvent constants are identical.\n'


def generateDiff(saves):
    if saves[0].verGroupAbbr == 'LGPE':
        print('Event Diff does not work on LGPE yet.')
        return ''
    versionInfo = _getVersionEventInfo(saves[0].verGroupAbbr)

    flagData = []
    constData = []
    for i in range(len(saves)):
        raw = saves[i].getCurrent()

        # extract Event Flags
        data = raw[versionInfo['flagStart']:versionInfo['flagStart'] + (versionInfo['flagCount'] >> 3)]
        extracted = []
        for n in range(versionInfo['flagCount']):
            extracted.append((data[n >> 3] >> (n & 7) & 1) == 1)
        flagData.append(extracted[:])

        # extract Event Constants
        data = raw[versionInfo['constStart']:versionInfo['flagStart']]
        extracted = []
        for n in range(versionInfo['constCount']):
            extracted.append(data[n * 2] + (data[n * 2 + 1] << 8))
        constData.append(extracted[:])

    diff = []
    global diffs

    # diff event data
    flagDiffs = _diffEventFlags(flagData)
    if len(flagDiffs) > 0:
        diffs += 1
        diff.append('\n')
        diff.append(flagDiffs)
    constDiffs = _diffEventConst(constData)
    if len(constDiffs) > 0:
        diffs += 1
        diff.append('\n')
        diff.append(constDiffs)

    if len(diff) > 0:
        # if not called from another script, construct diff header
        if cli:
            header = ['Diff of saves from the following file(s):\n\n']
            for i in range(len(saves)):
                contents = '' if saves[i].contents == 'full' else ' (%s)' % saves[i].contents
                header.append("Save %i: %s%s\n" % (i + 1, saves[i].fileName, contents))
            header.append("\n")
            diff.insert(0, ''.join(header))
        return ''.join(diff)
    return 'Event flags and constants of provided saves are identical.'


def main(params):
    print("Loading saves...")
    saves = [Sav(f) for f in params.saves]
    saves = [s for s in saves if s.version != -1]

    print("Checking compatibility of saves...")
    compatFailReason = Sav.checkCompat(saves)
    if compatFailReason != '':
        print("Save compatibility check failed.\nReason: \"%s\"\nExiting without diffing." %
              compatFailReason)
        return

    # check number of saves
    if len(saves) == 1:
        if not saves[0].canSplit():
            print(
                "Cannot split a single %s save file. Exiting without diffing." % saves[0].verGroupAbbr)
            return
        # split lone save
        Sav.splitSave(saves, 0, True)

    print("Generating diff...")
    diff = generateDiff(saves)

    # output diff
    if diffs == 0:
            print("Event flags and constants of provided saves are identical.%s" % (
                "" if params.o == None else " %s not written to." % params.o))
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
if cli:
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
