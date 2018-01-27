# PKSMScript

## Installing Scripts
1. Download `PKSMScript.zip` from the [latest release](https://github.com/BernardoGiordano/PKSM-Tools/releases/latest)
1. Extract the contents and copy the `scripts` folder to your SD card so that its path is `sd:/3ds/PKSM/scripts`

## Legality Warning
>There is risk to using some of these scripts, *particularly on the most recent games* (US/UM and Su/Mo).

The following is a list of unlabeled scripts (with no legal counterpart) known to edit parts of your save to illegal values:
- `all versions` **Set Vivillon Fancy Form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal
- `all versions` **Set Vivillon Pokeball form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal

#### Item Scripts
Discarding or selling the listed items **BEFORE** going online *should* let you avoid trouble
- `SM` **Give all items 99x** -- Black Flute, Blue Flute, Blue Scarf, Bug Gem, Cherish Ball, Dark Gem, Discount Coupon, Dragon Gem, Dream Ball, Electric Gem, Fairy Gem, Fighting Gem, Fire Gem, Fluffy Tail, Flying Gem, Ghost Gem, Grass Gem, Green Scarf, Greet Mail, Ground Gem, Ice Gem, Macho Brace, Odd Keystone, Old Amber, Pink Scarf, Poison Gem, Psychic Gem, Red Flute, Red Scarf, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Shoal Salt, Shoal Shell, Sport Ball, Steel Gem, Water Gem, White Flute, Yellow Flute, Yellow Scarf
- `SM` **Give all berries 99x** -- Razz Berry, Nanab Berry, Wepear Berry, Cornn Berry, Magost Berry, Rabuta Berry, Nomel Berry, Spelon Berry, Pamtre Berry, Watmel Berry, Durin Berry, Belue Berry, Enigma Berry, Micle Berry, Custap Berry, Jaboca Berry, Rowap Berry
- `XY, ORAS` **Give all items 99x** -- Bug Gem, Cherish Ball, Dark Gem, Dragon Gem, Electric Gem, Fairy Gem, Fast Ball, Fighting Gem, Fire Gem, Flying Gem, Friend Ball, Ghost Gem, Grass Gem, Ground Gem, Heavy Ball, Ice Gem, Level Ball, Love Ball, Lure Ball, Moon Ball, Odd Keystone, Park Ball, Poison Gem, Psychic Gem, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Sport Ball, Steel Gem, Water Gem

#### Confirmation Required
- `USUM` **Give all items 99x** -- are any of the illegal items from the SM version (see above) available in SUMO?
- `USUM` **Give all berries 99x** -- are any of the illegal berries from the SM version (see above) available in SUMO?
- `SM, USUM` **All Z-Crystals Owned** -- unreleased Z-Crystals?
- `ORAS` **Unlock & max all O-Powers** -- includes unreleased Max and S levels?

#### Past Gen
These scripts may cause problems in the unlikely event you should ever have to go through thorough hack checks
- `HGSS` **Unlock all Pokewalker Courses** -- contains unreleased courses?
- `HGSS` **Give all pokeballs 99x** -- Cherish Ball, Park Ball, Sport Ball
- `PT, HGSS` **Give all items 99x** -- Griseous Orb (untradeable and only one can be obtained per file), Shoal Salt, Shoal Shell
- `DP, PT` **Give all pokeballs 99x** -- Cherish Ball
- `DP, PT` **Get all Pokewatch apps** -- Alarm Clock and Stopwatch were never released
- `DP` **Give all items 99x** -- Shoal Salt, Shoal Shell

---

## Building Scripts
1. Make sure you have [Python 3](https://www.python.org/downloads/release/python-364/) installed
    - If already have Python 3 installed, make sure you have the argparse module as well: `sudo pip3 install argparse`
1. Download or clone the [PKSM-Tools source code](https://github.com/BernardoGiordano/PKSM-Tools)
1. Use one of the following commands in the Command Line to compile your scripts
    - Windows
        - All scripts (in the `.txt` files): `py -3 genScripts.py`
        - Single script: `py -3 PKSMScript.py "USUM - Set max money" -i 0x4404 4 9999999 1`
    - Mac / Linux
        - All scripts (in the `.txt` files): `python3 genScripts.py`
        - Single script: `python3 PKSMScript.py "USUM - Set max money" -i 0x4404 4 9999999 1`

## Creating Scripts
PKSMScript syntax: `PKSMScript.py [-h] output [-i ofs len pld rpt]`
> You can use `PKSMScript.py -h` to view PKSMScript's own documentation

To create completely new scripts, you will need to find the following values:
- `output` -- the name of your new script
- `-i` -- denotes the beginning of input values (can be repeated, along with extra sets of `ofs`, `len`, `pld`, and `rpt` values, to change more than one offset with a single script)
- `ofs` -- the offset (location) in the game's save of the value you want to edit
- `len` -- how many bytes (offsets) need to be written over
- `pld` -- the new value you want to write to the save (or a `.bin` file containing a list of values to write)
- `rpt` -- how many times you want `pld` to be written to the save in succession


### Examples
Examples can be found [here](https://github.com/BernardoGiordano/PKSM-Tools/blob/master/PKSMScript/src/scriptsUSUM.txt).


## .pksm file format

```
# PKSM script structure
# u8 magic[10]        // PKSMSCRIPT
# u32 offset          // save offset to write the data to
# u32 length          // payload length
# u8 payload[len]     // payload data
# u32 repeat_times    // repeat payload n times
# ...
```
