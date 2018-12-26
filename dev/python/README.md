# PKSM Script Python DevTools

## Setup
1. Make sure you have [Python 3](https://www.python.org/downloads/release/python-370/) installed
    - If you already have Python 3 installed, make sure you have the argparse module as well: `sudo pip3 argparse`
2. Make sure you have the following files from the [PKSM-Scripts repo](https://github.com/FlagBrew/PKSM-Scripts):
    - saveVersion.py
    - PKSMScript.py
    - genScriptsDev.py
    - dump.py
    - diffSave.py

## Main Scripts
When using these scripts, you will need to prefix the below commands with one of the following depending on your OS:
    - Windows: `py -3`
    - Mac / Linux: `python3`

### `PKSMScript`
Compiles `.pksm` scripts

```
PKSMScript.py [-h] [-d subdirectory] [-i offset length data repeat]
```

Notes:
- `-i` and its associated values can be repeated to affect multiple, non-consecutive offsets with a single script
- `-d` puts the script in the desired subdirectory. Only PKSMv6 supports subdirectories


### `dump`
Dumps a portion of your save. Useful for creating scripts that use `.bin` files

```
dump.py saveFile output offset length
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


### `diffSave`
Generate a diff of 2+ saves
- can output to a `.txt` file if the `-o outFile` is used, otherwise diff is printed to the console

```
diffSave.py [-h] [-o outFile] saveFiles
```

Future functionality:
- can diff a particular range from the saves rather than the entire thing using the `-r` flag
- can break down Event Const and Flags (mimicking PKHeX's "FlagDiff Researcher") using the `-e` flag


### `smItem`
**NOTE**: This script does not exist *yet*, though there is a JS version that can be easily translated

Transforms an item ID and quantity into the form used to store items in Gen 7 (Su/Mo and US/UM) saves
```
smItem.py itemID quantity
```


## Support Scripts
These script files aren't meant to be called directly from the command line. Instead they provide functions to be called by other scripts

### `saveVersion`
Provides a function for determining the version of a save, or at least guess it based on a save's file size.

```js
getSaveVersion(saveSize[, saveData]);
```


## To Do
- `diffSave`
  - implement `-r` and `-e` flags
- `diffSave`: allow user to supply folder of saves to diff
- `dump`: Gen 4 active block awareness
- `smItem.py`: everything
- `smItem`: allow item name instead of ID (currently very low priority)
- `lgpeItem`: everything
  - ID + (quantity << 15) + (newBit << 30) + (reservedBit << 31)
