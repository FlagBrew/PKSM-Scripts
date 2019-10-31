# PKSMScript

## Table of Contents
- [Installing Scripts](#Installing-Scripts)
- [Legality Warning](#Legality-Warning)
    - [Replaced Scripts](#Replaced-Scripts)
    - [Past Gen](#Past-Gen)
- [Script Notes](#Script-Notes)
- [Making Scripts](#Making-Scripts)
- [Credits](#Credits)
- [Script file format](#Script-file-format)

## Installing Scripts
If you're using PKSM v6.0.0 or later then you already have most (if not all) scripts already installed

If you're still using PKSM v5.1.x (which is no longer receiving support), do the following:

1. Download the `scripts.7z` from [this release](https://github.com/FlagBrew/PKSM-Scripts/releases/tag/v1.1)
2. Extract the contents and copy the `scripts` folder to your SD card so that its path is `/3ds/PKSM/scripts`

## Legality Warning
>There is risk to using some of these scripts, *particularly on the most recent games* (US/UM and Su/Mo).

The following is a list of unlabeled scripts (with no legal counterpart) known to edit parts of your save to illegal values:

- `all versions` **Set Vivillon Fancy Form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal
- `all versions` **Set Vivillon Pokeball form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal

### Replaced Scripts
Old versions of these scripts included the following elements that could be flagged as illegal if a save is put through strict hack checks

- `USUM, SM` **All items 99x** -- Black Flute, Blue Scarf, Bug Gem, Cherish Ball, Dark Gem, Discount Coupon, Dragon Gem, Dream Ball, Electric Gem, Fairy Gem, Fighting Gem, Fire Gem, Fluffy Tail, Flying Gem, Ghost Gem, Grass Gem, Green Scarf, Greet Mail, Ground Gem, Ice Gem, Macho Brace, Odd Keystone, Old Amber, Pink Scarf, Poison Gem, Psychic Gem, Red Scarf, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Shoal Salt, Shoal Shell, Sport Ball, Steel Gem, Water Gem, White Flute, Yellow Scarf
- `USUM, SM` **All Medicine 99x** -- Blue Flute, Red Flute, Yellow Flute
- `USUM, SM` **All berries 99x** -- Razz Berry, Nanab Berry, Wepear Berry, Cornn Berry, Magost Berry, Rabuta Berry, Nomel Berry, Spelon Berry, Pamtre Berry, Watmel Berry, Durin Berry, Belue Berry
- `ORAS` **Unlock & max all O-Powers** -- unreleased S levels
- `ORAS, XY` **Give all items 99x** -- Bug Gem, Cherish Ball, Dark Gem, Dragon Gem, Electric Gem, Fairy Gem, Fast Ball, Fighting Gem, Fire Gem, Flying Gem, Friend Ball, Ghost Gem, Grass Gem, Ground Gem, Heavy Ball, Ice Gem, Level Ball, Love Ball, Lure Ball, Moon Ball, Odd Keystone, Park Ball, Poison Gem, Psychic Gem, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Sport Ball, Steel Gem, Water Gem
- `B2W2, BW` **Give all items 99x** -- Blue Scarf, Cherish Ball, Dream Ball, Fast Ball, Friend Ball, Green Scarf, Heavy Ball, Level Ball, Love Ball, Lure Ball, Moon Ball, Park Ball, Pink Scarf, Red Scarf, Safari Ball, Sport Ball, Yellow Scarf
- `B2W2, BW` **Give all berries 99x** -- Rabuta Berry, Pamtre Berry
- `HGSS` **Give all pokeballs 99x** -- Cherish Ball, Park Ball, Sport Ball
- `PT, DP` **Give all pokeballs 99x** -- Cherish Ball
- `DP` **Give all items 99x** -- Shoal Salt, Shoal Shell

### Past Gen
These scripts may cause problems in the unlikely event you should ever have to go through thorough hack checks

- `HGSS` **Unlock all Pokewalker Courses** -- Rally, Sightseeing, and Amity Meadow were not released for all regions
- `HGSS, PT` **Give all items 99x** -- Griseous Orb (untradeable and only one can be obtained per file)
- `PT, DP` **Get all Pokewatch apps** -- Alarm Clock and Stopwatch were never released

## Script Notes
Some scripts deal with complicated mechanics or have effects that cannot be summarized to fit in their names. Helpful details about these scripts can be found on [this wiki page](https://github.com/FlagBrew/PKSM-Scripts/wiki/Script-Notes).

---

## Making Scripts
For simple scripts and a basic guide to figuring out the edits you want the script to make, see the [docs README](https://github.com/FlagBrew/PKSM-Scripts/blob/master/dev/README.md).

If you're looking to make a picoC script for PKSM, check out the PKSM scripting API documentation in [the wiki](https://github.com/FlagBrew/PKSM-Scripts/wiki/PicoC-Basics)

---

## Credits
- bernardogiordano - PKSM, PKSMScript.py, dump.py, scripts
- Lavorther - scripts
- piepie62 - PKSM's picoC API, genScripts.py, scripts
- PKMWM1 - scripts
- PlasticJustice - scripts
- SpiredMoth - scripts, documentation, dev scripts (all Node and some Python)
- trainboy2019 - scripts
- wrathsoffire - scripts

---

## Script file format

```
# "Legacy" PKSM script structure
# u8 magic[10]        // PKSMSCRIPT
# u32 offset          // save offset to write the data to
# u32 length          // payload length
# u8 payload[len]     // payload data
# u32 repeat_times    // repeat payload n times
# ...
```
