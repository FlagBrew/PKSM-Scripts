# PKSM Script Python DevTools

## Setup
1. Make sure you have [Python 3](https://www.python.org/downloads/release/python-370/) installed
    - If you already have Python 3 installed, make sure you have the argparse module as well: `sudo pip3 install argparse`
2. Make sure you have the following files from the [PKSM-Scripts repo](https://github.com/FlagBrew/PKSM-Scripts):
    - Sav.py
    - PKSMScript.py
    - genScriptsDev.py
    - dump.py
    - diff.py

## Main Scripts
When using these scripts, you will need to prefix the below commands with one of the following depending on your OS:
    - Windows: `py -3`
    - Mac / Linux: `python3`

> Pardon the lack of code documentation, which may or may not come in the future. If you want help understanding any of the methods, you're welcome to check the [Node.js](https://github.com/PKSM-Scripts/tree/dev/node) version which are documented using [JSDoc conventions](https://jsdoc.app/)

### `PKSMScript`
Compiles `.pksm` scripts

```
PKSMScript.py [-h] [-d subdirectory] [-i offset length data repeat]

Creates .pksm script files

Positional arguments:
  output              Output file name

Optional arguments:
  -h, --help          Show this help message and exit.
  -d subdir           Subdirectory in which to create the script
  -i ofs len pld rpt  ofs: offset to write the payload to. len: payload
                      length. pld: payload (can be an integer or a file path),
                       rpt: repeat n times.
```

**Notes**:

- `-i` and its associated values can be repeated to change multiple, non-consecutive offsets with a single script
- `-d` puts the script in the desired subdirectory. Only PKSMv6 supports subdirectories


### `dump`
Dumps a portion of your save. Useful for creating scripts that use `.bin` files

```
dump.py saveFile output offset length

Dump portion of file

Positional arguments:
  input       Input file name
  output      Output file name
  off         Start offset
  len         Length to dump

Optional arguments:
  -h, --help  Show this help message and exit.
```


### `genScriptsDev`
A version with some new development-centered features:

- **Selective game compilation**: If provided a list of game version abbreviations (the ones used by PKSM for script folder names), will only compile scripts for those games; if no list of game versions is provided, all are compiled
- **Ignores missing `.txt` files**
- **Doesn't delete existing scripts**: No scripts in `/scripts` will be deleted, only overwritten if they share a name with a script being compiled. Helpful for anyone who likes keeping all their compiled scripts, even ones that are for personal use only or are still in development, in one directory
- **ignores picoC scripts**

```
genScriptsDev.py [gameVersions]
```


### `diff`
Generates a listing of differences between 2 or more Gen IV-VII saves

- can output to a `.txt` file if the `-o outFile` is used, otherwise diff is printed to the console
- can output save diff with `-s`, event diff with `-e`, and both with `-se`
- can diff a particular range from the saves rather than the entire thing using the `-r` flag
  - can define a range based on a starting offset and a length with `-l`
  - can define multiple ranges by providing multiple `-r` or `-l` argument sets
  - can mix usage of `-r` and `-l`
- can break down Event Const and Flags (mimicking PKHeX's "FlagDiff Researcher") using the `-e` flag
  - includes a diff of the raw data from the save's event region
- supports passing folders containing saves with the `-d` flag or save files with the `-f` flag
  - can use both `-f` and `-d` at the same time to provide individual saves along with 1 or more folder(s) of saves
- automatically splits all saves that can be split and uses only the most recent save data
  - you can prevent this and diff full saves with `-k 'full'`
  - you can keep backup data of the first save with `-k 'first'`
  - you can keep backup data from all saves with `-k 'all'`

```
usage: diff.py [-h] [-o outFile] [-e] [-s] [-k {first,all,full}]
               [-r start end] [-l start length] [-d dir [dir ...]]
               [-f FILES [FILES ...]]

Generate a list of differences between 2 or more Gen 4-7 Pokémon saves

optional arguments:
  -h, --help            show this help message and exit
  -o outFile, --out outFile
                        File (.txt) to write diff to -- if not given, diff is
                        written to console
  -e                    Flag to perform an event diff
  -s                    Flag to perform a save diff
  -k {first,all,full}, --keep {first,all,full}
                        Whether save files should not be split (full) or which
                        backup save data (first or all) should be kept

Save Diff Range(s):
  Range(s) to limit save diff to. Optional. Can use one or both, can even
  use them multiple times.

  -r start end, --range start end
                        Specific range to limit diff to, from start (included)
                        to end (excluded)
  -l start length       Specific range to limit diff to, length number of
                        bytes beginning at start

Save File(s):
  Path(s) to save file(s) to be used in diff. Required -- can use either
  one, or both, but input must result in at least 1 save file being found.

  -d dir [dir ...], --dir dir [dir ...]
                        Space separated list of directories (folders)
                        containing files to diff
  -f FILES [FILES ...], --files FILES [FILES ...]
                        Space separated list of save files to diff
```


## Support Scripts
These script files aren't meant to be called directly from the command line. Instead they provide functions to be called by other scripts

### `Sav`
Constructor for Sav objects, containing details about saves useful in parsing

```py
Sav(fileName)
```

#### Instance Properties
- `data` - the contents of the file
  - if the save is from a type that can be split, this may only be a portion of the original file -- either the current save data or the backup
  - if the file could not be read, this will be an empty list
- `version` - Save's version number
  - DP: 10, PT: 12, HGSS: 7
    - Diamond and Pearl share a version number because saves cannot be told apart by their contents alone
    - HeartGold and SoulSilver share a version number because saves cannot be told apart by their contents alone
  - W: 20, B: 21, W2: 22, B2: 23
  - X: 24, Y: 25, AS: 26, OR: 27
  - S: 30, M: 31, US: 32, UM: 33
  - LGP: 42, LGE: 43
- `verGroupAbbr` - string abbreviation of save type
  - one of `DP`, `PT`, `HGSS`, `BW`, `B2W2`, `XY`, `ORAS`, `SM`, `USUM`, `LGPE`
- `generation` - generation of save
  - DP, PT, HGSS: 4
  - BW, B2W2: 5
  - XY, ORAS: 6
  - SM, USUM: 7
  - LGPE: 7.5
- `contents` - how much of the save file's original data is within `data`
  - `'full'` - The entire contents of the file's save data
  - `'current'` - Only the data representing the most recent save data from the file. Will only be this value if the save file is from a type that can be split
  - `'backup'` - Only the data representing the older save data from the file. Will only be this value if the save file is from a type that can be split
- `active` - dict tracking which blocks of save data within a split-able file are the most recent
  - `active.general` - Gen 4 General (small) block
  - `active.storage` - Gen 4 Storage (big) block
  - `active.hof` - Gen 4 Hall of Fame Block
    - logic for determining active HoF block does not exist yet so results may be inaccurate
  - `active.save` - Gen 5 save data
  - `active.extra` - Gen 5 extra data (Hall of Fame, custom C-Gear and Pokedex skins, PWT, etc.)


#### Instance Methods
```py
sav.canSplit()
sav.getCurrent()
sav.getBackup()
```

#### Class Methods
```py
Sav.splitSave(arr, ind, keepOld)
Sav.checkCompat(saves)
Sav.getBlockOffsets(verGroupAbbr, block)
```


## To Do
Ideas that may or may not get implemented in the future

- `smItem.py`: everything (probably won't get made since PKSM v6+ has a bag editor; [a Node.js version already exists](https://github.com/FlagBrew/PKSM-Scripts/blob/dev/node/smItem.js))
- `smItem`: allow item name instead of ID (currently very low priority)
- `lgpeItem`: everything
  - ID + (quantity << 15) + (newBit << 30) + (reservedBit << 31)
