# PKSM Script Development Scripts

## Main Scripts
Most of these are still a work-in-progress (if they even exist yet)

### `PKSMScript`
Same exact file as the one in the root of the PKSM-Scripts repo

```
PKSMScript.py [-h] [-d subdirectory] [-i offset length data repeat]
PKSMScript.js [-h] [-d subdirectory] [-i offset length data repeat]
```


### `dump`
Same exact file as previously existed in the root of PKSM-Scripts, just moved

```
dump.py saveFile output offset length
dump.js saveFile output offset length
```


### `genScriptsDev`
A version with some new development-centered features:
- **Selective game compilation**: If provided a list of game version abbreviations (the ones used by PKSM for script folder names), will only compile scripts for those games; if no list of game versions is provided, all are compiled
- **Ignores missing `.txt` files**
- **Doesn't delete existing scripts**: No scripts in `/scripts` will be deleted, only overwritten if they share a name with a script being compiled. Helpful for anyone who likes keeping all their compiled scripts, even ones that are for personal use only or are still in development, in one directory
- **ignores picoC scripts**

```
genScriptsDev.py [gameVersions]
genScriptsDev.js [gameVersions]
```


### `diffSave`
Generate a diff of 2+ saves
- can output to a `.txt` file if the `-o outFile` is used, otherwise diff is printed to the console

```
diffSave.js [-h] [-o outFile] saveFiles
```

Future functionality:
- can diff a particular range from the saves rather than the entire thing using the `-r` flag
- can break down Event Const and Flags (mimicking PKHeX's "FlagDiff Researcher") using the `-e` flag


### `smItem`
Transforms an item ID and quantity into the form used to store items in Gen 7 (Su/Mo and US/UM) saves
```
smItem.js itemID quantity
```


## Support Scripts
These script files aren't meant to be called directly from the command line. Instead they provide functions to be called by other scripts

### `saveVersion`
Provides a function for determining the version of a save, or at least guess it based on a save's file size.

```js
getSaveVersion(saveSize[, saveData]);
```

### `util.js`
Meant to fill in functionality that Node lacks compared to Python.

Might add other utility functions in the future. Or just replace this altogether with a NPM module.

```js
tryFSSync(op[, args[, errCodes]])
```


## To Do
- `*.js`: add `argparse` NPM module
- `*.js`: replace `util.js` with a NPM module?
- `diffSave`
  - implement `-r` and `-e` flags
- `diffSave`: allow user to supply folder of saves to diff
  - **js**: use `klaw` NPM package?
- `dump`: Gen 4 active block awareness
- `smItem.js`: add warning about item quantity being capped at 1023
- `smItem.py`: everything
- `smItem`: allow item name instead of ID (currently very low priority)
- `lgpeItem`: everything
  - ID + (quantity << 15) + (newBit << 30) + (reservedBit << 31)
