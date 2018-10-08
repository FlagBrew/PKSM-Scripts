# PKSMScript

## Table of Contents
- [Installing Scripts](#installing-scripts)
- [Legality Warning](#legality-warning)
    - [Gen 7 (US/UM and Su/Mo)](#gen-7-usum-and-sumo)
    - [Past Gen](#past-gen)
- [Script Notes](#script-notes)
    - [Mass Inject Scripts](#mass-inject-scripts)
    - [Fill Dex Scripts](#fill-dex-scripts)
    - [Item Scripts](#item-scripts)
    - [Reset Scripts](#reset-scripts)
    - [Other Scripts](#other-scripts)
- [Making Scripts](#making-scripts)
- [Script file format](#script-file-format)

## Installing Scripts
1. Download the [latest release](https://github.com/FlagBrew/PKSM-Scripts/releases/latest)
2. Extract the contents and copy the `scripts` folder to your SD card so that its path is `sd:/3ds/PKSM/scripts`

## Legality Warning
>There is risk to using some of these scripts, *particularly on the most recent games* (US/UM and Su/Mo).

The following is a list of unlabeled scripts (with no legal counterpart) known to edit parts of your save to illegal values:
- `all versions` **Set Vivillon Fancy Form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal
- `all versions` **Set Vivillon Pokeball form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal

### Gen 7 (US/UM and Su/Mo)
Discarding or selling the listed items **BEFORE** going online *should* let you avoid trouble
- `SM, USUM` **Give all items 99x** -- Black Flute, Blue Flute, Blue Scarf, Bug Gem, Cherish Ball, Dark Gem, Discount Coupon, Dragon Gem, Dream Ball, Electric Gem, Fairy Gem, Fighting Gem, Fire Gem, Fluffy Tail, Flying Gem, Ghost Gem, Grass Gem, Green Scarf, Greet Mail, Ground Gem, Ice Gem, Macho Brace, Odd Keystone, Old Amber, Pink Scarf, Poison Gem, Psychic Gem, Red Flute, Red Scarf, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Shoal Salt, Shoal Shell, Sport Ball, Steel Gem, Water Gem, White Flute, Yellow Flute, Yellow Scarf
- `SM, USUM` **Give all berries 99x** -- Razz Berry, Nanab Berry, Wepear Berry, Cornn Berry, Magost Berry, Rabuta Berry, Nomel Berry, Spelon Berry, Pamtre Berry, Watmel Berry, Durin Berry, Belue Berry, Enigma Berry, Micle Berry, Custap Berry, Jaboca Berry, Rowap Berry

### Past Gen
These scripts may cause problems in the unlikely event you should ever have to go through thorough hack checks
- `ORAS` **Unlock & max all O-Powers** -- includes unreleased S levels
    - This was replaced with a fully legal version in recent releases
- `XY, ORAS` **Give all items 99x** -- Bug Gem, Cherish Ball, Dark Gem, Dragon Gem, Electric Gem, Fairy Gem, Fast Ball, Fighting Gem, Fire Gem, Flying Gem, Friend Ball, Ghost Gem, Grass Gem, Ground Gem, Heavy Ball, Ice Gem, Level Ball, Love Ball, Lure Ball, Moon Ball, Odd Keystone, Park Ball, Poison Gem, Psychic Gem, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Sport Ball, Steel Gem, Water Gem
- `HGSS` **Unlock all Pokewalker Courses** -- contains unreleased courses?
- `HGSS` **Give all pokeballs 99x** -- Cherish Ball, Park Ball, Sport Ball
- `PT, HGSS` **Give all items 99x** -- Griseous Orb (untradeable and only one can be obtained per file), Shoal Salt, Shoal Shell
- `DP, PT` **Give all pokeballs 99x** -- Cherish Ball
- `DP, PT` **Get all Pokewatch apps** -- Alarm Clock and Stopwatch were never released
- `DP` **Give all items 99x** -- Shoal Salt, Shoal Shell

## Script Notes
These are notes and details that may be useful to know about scripts that couldn't be summarized to fit in scripts' names

### Mass Inject Scripts
- All mass injection scripts target the first slot of Box 1 to start injecting the collection. If you're worried about losing some of your Pokémon, make sure to clear out enough of your in-game boxes to make room
- Each mass injection script overwrites a number of your in-game boxes
    - **Living Dex**
        - Gen 5: 22 boxes
        - Gen 6: 25 boxes
        - Gen 7: 27 boxes
    - **Colosseum**: 2 boxes
    - **XD**: 3 boxes
    - everything else: 1 box
- Not all Pokémon in the mass injection scripts may be legal
- Only the "Living Dex" scripts update your dex. If you want the contents of a mass inject script to be registered but don't want the full Fill Dex, do one of the following:
    - deposit the unregistered Pokémon in the Day Care then withdraw them
    - take them into a wild battle (reported to work but not confirmed)
- **rBreedingDitto**: the Ditto in these scripts were obtained from [this list on /r/BreedingDittos](https://www.reddit.com/r/BreedingDittos/comments/2wqabp/giveaway_so_you_want_a_ditto/). They are subject to all the conditions and limits set by /r/BreedingDittos (so don't try passing them off as legal on /r/pokemontrades)

### Fill Dex Scripts
- Regional Pokédex scripts will overwrite anything you've seen (and owned if you use the "owned" version) which may cause you to lose registration of anything not in your game's regional Pokédex
- These scripts will fill your dex enough to unlock access to the following:
    - `DP, Pt` **Sinnoh seen**: regional dex diploma, National dex upgrade
    - `HGSS` **Johto owned**: regional dex diploma
    - `DP, Pt, HGSS` **National owned**: national dex diploma
    - `BW` **Unova owned**: regional dex diploma
    - `BW` **National owned**: national dex diploma
    - `B2W2` **Unova seen**: Permit (for visiting Nature Preserve)
    - `B2W2` **Unova owned**: regional dex diploma, Oval Charm
    - `B2W2` **National owned**: national dex diploma, Shiny Charm
    - `XY` **Kalos seen**: Oval Charm
    - `XY` **Kalos owned**: regional dex diplomas (Central, Coastal, Mountain, Kalos)
    - `ORAS` **Hoenn seen**: Oval Charm
    - `ORAS` **Hoenn owned**: regional dex diploma
    - `XY, ORAS` **National owned**: national dex diploma, Shiny Charm
    - `SM, USUM` **Alola owned**: Shiny Charm
- **National** versions will also unlock all regional rewards
- **Complete** versions will unlock all the same rewards as the National versions
- Only the **Complete** versions will fill in Mythicals (Mew, Celebi, Jirachi, etc.)
- Only the **Complete (illegal)** version will unlock *all* forms and shiny sprites, including unreleased ones

### Item Scripts
- `SM, USUM` **slot 1 x897-960**: due to the way items are stored in Gen 7 saves and the current limitations of PKSM's scripts, the quantity of the item in the pouch's first slot is set to something in the range of 897 to 960 (depends on the former quantity) rather than 999 like in past generations
- `Gen IV, V, VI` **All TMs and HMs owned**: fills your TM pouch with *all* TMs and HMs, which may cause problems with story progression

### Reset Scripts
- `all games` **Reset [pokemon]**: Allows any listed Pokémon to be re-obtained (if gift) or re-battled
- `USUM` **Reset Main Conflict**: resets everything between getting to the Altar of the Sunne/Moone and encountering Mina
- `USUM` **Reset Postgame**: resets it back to the start of the Rainbow Rocket arc, when you enter your house, you meet Sophocles and go the Festival Plaza
- `USUM` **Reset Nanu Event**: ?
- `USUM` **Reset Team Skull Pose Event**: resets the event in Po Town where you help the Team Skull Grunt who can't make the Team Skull pose
- `USUM` **Reset Janitor Event**: resets the event that happens when you talk to the janitor in Hau'oli Mall
- `USUM` **Reset Shiny Exeggcute Battle**: resets the battle against the Poni Island trainer with the shiny Exeggcute
- `USUM` **Remove Stakataka and Blacephalon**: the reset scripts for these two cause them to respawn indefinitely after capture/defeat so this script was made to allow users to end that if they want
- `ORAS` **Reset Delta Episode**: resets back to before the battle with Wallace in front of Sky Pillar
- `DP` **Set all legendaries battlable/disappeared**: same as **Reset [pokemon]** above

### Other Scripts
- `USUM` **Set 100 hatched eggs**: set the number of hatched eggs to 100 so that you can just talk to the stats judge to unlock IV checking in the PC
- `USUM` **Set Sun/Moon time**: sets the in-game time of day, to allow access to time limited events (only available during day/night)
- `DP, Pt` **Set 32 people met Underground**: meeting 32 people in the Underground is one of the requirements to encounter Spiritomb

---

## Making Scripts
See the [docs README](./docs/README.md)

---

## Script file format

```
# PKSM script structure
# u8 magic[10]        // PKSMSCRIPT
# u32 offset          // save offset to write the data to
# u32 length          // payload length
# u8 payload[len]     // payload data
# u32 repeat_times    // repeat payload n times
# ...
```
