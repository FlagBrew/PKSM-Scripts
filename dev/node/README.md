# PKSM Script Node DevTools

## Setup
1. Make sure you have [Node](https://nodejs.org) installed
2. Copy of the [PKSM-Scripts repo](https://github.com/FlagBrew/PKSM-Scripts). At the very least you will need these files:
    - package.json
    - Sav.js
    - PKSMScript.js
    - genScriptsDev.js
    - dump.js
    - diff.js
3. Run the following command: `npm install`
    - This will install the NPM modules [`argparse`](https://www.npmjs.com/package/argparse), [`fs-extra`](https://www.npmjs.com/package/fs-extra), and [`klaw-sync`](https://www.npmjs.com/package/klaw-sync) which are needed by many of the JS scripts


## Main Scripts
### `PKSMScript`
Compiles `.pksm` scripts

```
usage: PKSMScript.js [-h] output [-d subdir] [-i ofs len pld rpt]

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
usage: dump.js [-h] input output off len

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
genScriptsDev.js [gameVersions]
```


### `diff`
Generate a diff of 2+ saves

- can output to a `.txt` file if the `-o outFile` is used, otherwise diff is printed to the console
- can output save diff with `-s`, event diff with `-e`, and both with `-se`
- can diff a particular range from the saves rather than the entire thing using the `-r` flag
  - can define a range based on a starting offset and a length with `-l`
  - can define multiple ranges by providing multiple `-r` or `-l` argument sets
  - can mix usage of `-r` and `-l`
- can break down Event Const and Flags (mimicking PKHeX's "FlagDiff Researcher") using the `-e` flag
  - includes a diff of the raw data from the save's event region
- supports passing folders containing saves (via `-d` flag), save files (via `-f` flag), or even both at once
  - can use both `-f` and `-d` at the same time
- automatically splits all saves that can be split and uses only the most recent save data
  - you can alter this behavior with one of the `-k` options:
    - `'full'` - don't split saves at all
    - `'all'` - split saves and keep all backups
    - `'first'` - split saves and keep only the first save's backup

```
usage: diff.js [-h] [-o outFile] [-e] [-s] [-k {first,all,full}]
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


### `smItem`
Transforms an item ID and quantity into the form used to store items in Gen 7 (Su/Mo and US/UM) saves
```
smItem.js itemID quantity
```


## Support Scripts
These script files aren't meant to be called directly from the command line. Instead they provide functions to be called by other scripts

### `Sav`
Constructor for Sav objects, containing details about saves useful in parsing

```js
/**
 * @constructor
 * @param {String} fileName Path to save file to read
 */
new Sav(fileName);
```

#### Instance Properties
- `data` - the contents of the file
  - if the save is from a type that can be split, this may only be a portion of the original file -- either the current save data or the backup
  - if the file could not be read, this will be an empty Array
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
- `active` - object tracking which blocks of save data within a split-able file are the most recent
  - `active.general` - Gen 4 General (small) block
  - `active.storage` - Gen 4 Storage (big) block
  - `active.hof` - Gen 4 Hall of Fame Block
    - logic for determining active HoF block does not exist yet so results may be inaccurate
  - `active.save` - Gen 5 save data


#### Instance Methods
```js
/**
 * Returns a Boolean indicating if save can be split
 *
 * @returns {Boolean} true if save can be split, false if not
 */
Sav.prototype.canSplit()


/**
 * Extract the current save data as a new Buffer
 *
 * @returns {Buffer} Data representing current save state
 */
Sav.prototype.getCurrent();


/**
 * Extract the backup save data as a new Buffer
 *
 * @returns {Buffer} Data representing backup save state
 */
Sav.prototype.getBackup();
```

#### Class Methods
```js
/**
 * Split the save at `arr[ind]`, keeping the current save data and
 * optionally keeping the backup save data
 *
 * @param {Sav[]} arr Array of Sav objects
 * @param {Number} ind Index in arr of save to be split
 * @param {Boolean} keepOld Whether the backup should be kept
 */
Sav.splitSave(arr, ind, keepOld);


/**
 * Makes sure all saves come from the same version group
 *
 * @param {Sav[]} saves Array of Sav objects to check for compatibility
 * @returns {String} String detailing reason for save incompatibility (if any)
 */
Sav.checkCompat(saves);


/**
 * Grabs list (Array) of offsets representing certain blocks of save files
 *
 * Gen 4: general, storage, hof
 * Gen 5: save, extra
 * all games (except LGPE): eventConst, eventFlag
 *
 * @param {String} verGroupAbbr Save version group abbreviation
 * @param {String} block Which block's offsets are being requested
 * @returns {Number[]} Array of start and end (inclusive) offsets of block
 */
Sav.getBlockOffsets(verGroupAbbr, block);
```


## To Do
Ideas that may or may not get implemented in the future

- `smItem.js`: add warning about item quantity being capped at 1023
- `smItem`: allow item name instead of ID (currently very low priority)
- `lgpeItem`: everything
  - ID + (quantity << 15) + (newBit << 30) + (reservedBit << 31)
