#!/usr/bin/env python3
import math
import argparse
import os

from Sav import Sav

# argparse setup
parser = argparse.ArgumentParser(
    description='Generate a list of differences between 2 or more Gen 4-7 Pokémon saves')
parser.add_argument('-o', '--out', metavar='outFile',
                    help='File (.txt) to write diff to -- if not given, diff is written to console')
parser.add_argument('-e', action='store_true',
                    help='Flag to include an event diff')
parser.add_argument('-s', action='store_true',
                    help='Flag to include save diff')
parser.add_argument('-c', '--full', action='store_true',
                    help='Use full save file (of saves that can be split) in diff rather than just current save data')
parser.add_argument('-k', '--keep', action='store_true',
                    help='Keep the backup save from first file (if split-able)')

group_range = parser.add_argument_group(
    title='Save Diff Range(s)', description='Range(s) to limit save diff to. Optional. Can use one or both, can even use them multiple times.')
group_range.add_argument('-r', '--range', action='append', nargs=2, metavar=('start', 'end'),
                         help='Specific range to limit diff to, from start (included) to end (excluded)')
group_range.add_argument('-l', action='append', nargs=2, metavar=('start', 'length'),
                         help='Specific range to limit diff to, length number of bytes beginning at start')

group_save = parser.add_argument_group(
    title='Save File(s)', description='Path(s) to save file(s) to be used in diff.\nRequired -- can use either one, or both, but input must result in at least 1 save file being found.')
group_save.add_argument('-d', '--dir', metavar='dir', nargs='+',
                        help='Space separated list of directories (folders) containing files to diff')
group_save.add_argument('-f', '--files', nargs='+',
                        help='Space separated list of save files to diff')

# Global variables
counts = {
    'DP': {
        'constCount': 288,
        'flagCount': 2912
    },
    'PT': {
        'constCount': 288,
        'flagCount': 2912
    },
    'HGSS': {
        'constCount': 368,
        'flagCount': 2912
    },
    'BW': {
        'constCount': 318,
        'flagCount': 2912
    },
    'B2W2': {
        'constCount': 431,
        'flagCount': 3064
    },
    'XY': {
        'constCount': 382,
        'flagCount': 3072
    },
    'ORAS': {
        'constCount': 382,
        'flagCount': 3072
    },
    'SM': {
        'constCount': 1000,
        'flagCount': 3968
    },
    'USUM': {
        'constCount': 1000,
        'flagCount': 4928
    }
}


def _toHexStr(value, padTo):
    paddedHex = hex(value)[2:]
    while len(paddedHex) < padTo:
        paddedHex = "0" + paddedHex
    return "0x" + paddedHex[-padTo:]


def summarize_saves(saves, state):
    header = []

    # construct diff header
    header.append("Diff of saves from the following file(s):\n\n")

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

    for i in range(len(saves)):
        contents = '' if saves[i].contents == 'full' else " ({})".format(
            saves[i].contents)
        header.append('Save {}: "{}"{}\n'.format(i + 1, saves[i].fileName, contents))

        # report block offsets of split saves
        if state['isSplit']:
            if saves[i].generation == 4:
                compOfs = [
                    _toHexStr(n + saves[i].active['general'] * 0x40000, 5) for n in ofs['general']]
                header.append("    General: {}\n".format(':'.join(compOfs)))
                compOfs = [
                    _toHexStr(n + saves[i].active['storage'] * 0x40000, 5) for n in ofs['storage']]
                header.append("    Storage: {}\n".format(':'.join(compOfs)))
                compOfs = [
                    _toHexStr(n + saves[i].active['hof'] * 0x40000, 5) for n in ofs['hof']]
                header.append("    HoF:     {}\n".format(':'.join(compOfs)))
            elif saves[i].verGroupAbbr == 'BW':
                compOfs = [
                    _toHexStr(n + saves[i].active['save'] * 0x24000, 5) for n in ofs['save']]
                header.append("    Save:  {}\n".format(':'.join(compOfs)))
                compOfs = [_toHexStr(n, 5) for n in ofs['extra']]
                header.append("    Extra: {}\n".format(':'.join(compOfs)))
            elif saves[i].verGroupAbbr == 'B2W2':
                compOfs = [
                    _toHexStr(n + saves[i].active['save'] * 0x26000, 5) for n in ofs['save']]
                header.append("    Save:  {}\n".format(':'.join(compOfs)))
                compOfs = [_toHexStr(n, 5) for n in ofs['extra']]
                header.append("    Extra: {}\n".format(':'.join(compOfs)))
            else:
                print('How did you split this input?')

    if saves[0].generation == 4 and state['isSplit']:
        header.append(
            '\nNote: "Current" / "backup" status of HoF blocks of saves may not be accurate.\n')

    return ''.join(header)


def build_table_header(num_saves, first_column, range_list = None):
    header = []

    if range_list:
        ranges = []
        for r in range_list:
            ranges.append('-'.join([_toHexStr(v, 5) for v in r]))
        ranges.append('\n')
        header.append('\n'.join(ranges))

    header.append("{}        ".format(first_column)[:9])
    for i in range(num_saves):
        digits = 10
        if i % 10 == 9:
            digits += int(math.floor(math.log10(i + 1) != math.floor(math.log10(i))))
        header.append("    Save {}".format(i + 1)[-digits:])
    header.append('\n')

    return ''.join(header)


def diff_consts(saves, state):
    # shortcut out if LGPE
    if saves[0].verGroupAbbr == 'LGPE':
        print('Event Diff does not work on LGPE yet.')
        return ''

    version_info = {
        'ofs': Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventConst'),
        'count': counts[saves[0].verGroupAbbr]['constCount']
    }

    const_data = []
    for s in saves:
        data = s.getCurrent()[version_info['ofs'][0]:version_info['ofs'][1]]
        extracted = []
        for n in range(version_info['count']):
            extracted.append(data[n * 2] + (data[n * 2 + 1] << 8))
        const_data.append(extracted[:])

    const_diffs = []
    for n in range(len(const_data[0])):
        const_diff = {
            'num': "{}        ".format(n),
            'values': []
        }
        for i in range(len(const_data)):
            const_diff['values'].append("{}     ".format(const_data[i][n])[:6])
        for i in range(len(const_diff['values'])):
            if const_diff['values'][i] != const_diff['values'][0]:
                state['diffs'] += 1
                line = [const_diff['num'][:9]]
                line.extend(const_diff['values'])
                line = '    '.join(line).strip()
                const_diffs.append("{}\n".format(line))
                break
    if len(const_diffs) > 0:
        e_const_header = ['\nEvent Const Diff\n\n']
        e_const_header.append(build_table_header(len(saves), 'Const'))
        return ''.join(e_const_header + const_diffs)
    return '\nEvent constants are identical.\n'


def diff_flags(saves, state):
    # shortcut out if LGPE
    if saves[0].verGroupAbbr == 'LGPE':
        print('Event Diff does not work on LGPE yet.')
        return ''

    version_info = {
        'ofs': Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventFlag'),
        'count': counts[saves[0].verGroupAbbr]['flagCount']
    }

    flag_data = []
    for i in range(len(saves)):
        data = saves[i].getCurrent()[version_info['ofs'][0]
                                   :version_info['ofs'][1]]
        extracted = []
        for n in range(version_info['count']):
            extracted.append(((data[n >> 3] >> (n & 7)) & 1) == 1)
        flag_data.append(extracted[:])

    flag_diffs = {
        'set': [],
        'setToggle': [],
        'unset': [],
        'unsetToggle': [],
        'toggle': []
    }
    found = False
    for n in range(version_info['count']):
        flag_diff = {
            'num': "000{}".format(n)[-4:],
            'values': []
        }
        for i in range(len(flag_data)):
            flag_diff['values'].append(flag_data[i][n])
        changes = 0
        for i in range(1, len(flag_diff['values'])):
            if flag_diff['values'][i] != flag_diff['values'][i - 1]:
                changes += 1
        if changes > 0:
            found = True
            state['diffs'] += 1
            if flag_diff['values'][0] == flag_diff['values'][-1]:
                flag_diffs['toggle'].append(flag_diff['num'])
            elif changes == 1:
                flag_diffs['set' if flag_diff['values'][-1]
                           else 'unset'].append(flag_diff['num'])
            else:
                flag_diffs['setToggle' if flag_diff['values'][-1]
                           else 'unsetToggle'].append(flag_diff['num'])

    if found:
        flag_diff_Data = ['\nEvent Flag Diff\n']

        if len(flag_diffs['set']) > 0:
            flag_diff_Data.append("Set: {}\n".format(
                ', '.join(flag_diffs['set'])))
        if len(flag_diffs['unset']) > 0:
            flag_diff_Data.append("Unset: {}\n".format(
                ', '.join(flag_diffs['unset'])))
        if len(flag_diffs['setToggle']) > 0:
            flag_diff_Data.append("Set (toggled): {}\n".format(
                ', '.join(flag_diffs['setToggle'])))
        if len(flag_diffs['unsetToggle']) > 0:
            flag_diff_Data.append("Unset (toggled): {}\n".format(
                ', '.join(flag_diffs['unsetToggle'])))
        if len(flag_diffs['toggle']) > 0:
            flag_diff_Data.append("Toggled: {}\n".format(
                ', '.join(flag_diffs['toggle'])))

        return '\n'.join(flag_diff_Data)
    return '\nEvent flags are identical.\n'


def diffSave(saves, state, label = ''):
    diff = []

    ofs_update = state['isSplit'] and saves[0].verGroupAbbr == 5
    if ofs_update:
        save_end = Sav.getBlockOffsets(saves[0].verGroupAbbr, 'save')[1]

    for r in state['ranges']:
        for n in range(r[0], r[1]):
            ofs_diff = {
                'offset': _toHexStr(n, 5),
                'values': []
            }
            if ofs_update and n > save_end:
                ofs_diff['offset'] = _toHexStr(n + save_end + 1, 5)
            ofs_diff['values'] = [
                _toHexStr(saves[i].data[n], 2) for i in range(len(saves))]
            for i in range(len(ofs_diff['values'])):
                if ofs_diff['values'][i] != ofs_diff['values'][0]:
                    state['diffs'] += 1
                    diff.append("{}      {}\n".format(
                        ofs_diff['offset'], '      '.join(ofs_diff['values'])))
                    break

    if len(diff) > 0:
        if state['ranges'][0] == [0, len(saves[0].data)]:
            header = build_table_header(len(saves), 'Offset')
        else:
            header = build_table_header(len(saves), 'Offset', state['ranges'])
        diff = [label, header] + diff

    return ''.join(diff)


def main(params):
    # get list of files from provided directories
    if params.dir:
        if not params.files:
            params.files = []
        for d in params.dir:
            dir_files = []
            for path, _, files in os.walk(d):
                for fullname in files:
                    dir_files.append(os.path.normpath(
                        os.path.join(path, fullname)))
            dir_files.sort(key=str.lower)
            params.files += dir_files
    # need at least 1 save
    if (not params.files) or len(params.files) == 0:
        parser.error('At least 1 save file is required')

    print("Loading saves...")
    saves = []
    for f in params.files:
        s = Sav(f)
        if s.version == -1:
            print('  Unable to determine version of save "{}". Excluding it from diff.'.format(
                s.fileName))
        else:
            saves.append(s)

    print("Checking compatibility of saves...")
    reason = Sav.checkCompat(saves)
    if reason != '':
        print('Save compatibility check failed.\nReason: "{}"\nExiting without diffing.'.format(reason))
        return

    state = {
        'e': params.e,
        's': params.s or not params.e,
        'ranges': [],
        'isSplit': False,
        'diffs': 0
    }

    # save splitting
    if saves[0].canSplit():
        if len(saves) == 1 or (params.keep and not params.full):
            state['isSplit'] = True
            Sav.splitSave(saves, 0, True)
        if not params.full:
            state['isSplit'] = True
            for i in range(len(saves)):
                Sav.splitSave(saves, i, False)
    elif len(saves) == 1:
        print("\nCannot split a single {} save file. Exiting without diffing.".format(
            saves[0].verGroupAbbr))

    # consolidate supplied ranges
    range_label = ''
    if params.l:
        for r in params.l:
            state['ranges'].append([int(r[0], 0), int(r[0], 0) + int(r[1], 0)])
    if params.range:
        state['s'] = True # force save diff
        for r in params.range:
            # TODO: check that range doesn't exceed length of save's data
            state['ranges'].append([int(i, 0) for i in r])
        # CONSIDER: should I handle (prevent/merge) overlapping ranges?
        state['ranges'] = sorted(state['ranges'])
        range_label = 'Save Diff range(s):\n'
    elif state['s']:
        state['ranges'].append([0, len(saves[0].data)])

    print("Generating diff...")
    diff = []
    diff.append(summarize_saves(saves, state))
    if state['e']:
        const_diff = diff_consts(saves, state)
        flag_diff = diff_flags(saves, state)
        raw_event_diff = ''
        if state['diffs'] > 0:
            raw_event_state = {
                'isSplit': state['isSplit'],
                'ranges': [[
                    Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventConst')[0],
                    Sav.getBlockOffsets(saves[0].verGroupAbbr, 'eventFlag')[1]
                ]],
                'diffs': 0
            }
            raw_event_diff = diffSave(saves, raw_event_state, 'Raw Event Data Diff\n  ')
            state['diffs'] += raw_event_state['diffs']
        diff.append('\n'.join(['', const_diff, flag_diff, '', raw_event_diff]))
    if state['s']:
        diff.append('\n\n\nSave Diff\n\n')
        diff.append(diffSave(saves, state, range_label))

    # output results
    if params.out:
        params.out += "" if params.out[-4:] == ".txt" else ".txt"
    if state['diffs'] == 0:
        print("Saves were identical.{}".format("" if params.out ==
                                               None else ' "%s" not written to.' % params.out))

    if params.out:
        outDir = ''
        try:
            outDir = os.path.dirname(params.out)
            os.makedirs(outDir, exist_ok=True)
        except:
            pass
        with open(params.out, 'w') as f:
            f.write(''.join(diff))
        print('Diff written to "{}" successfully.'.format(params.out))
    else:
        print("\n\n{}".format(''.join(diff)))


# execute if called directly from command line
if __name__ == '__main__':
    main(parser.parse_args())
