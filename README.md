# PKSMScript

## Table of Contents
- [Installing Scripts](#installing-scripts)
- [Legality Warning](#legality-warning)
    - [Replaced Scripts](#replaced-scripts)
    - [Past Gen](#past-gen)
- [Script Notes](#script-notes)
    - [Mass Inject Scripts](#mass-inject-scripts)
    - [Fill Dex Scripts](#fill-dex-scripts)
    - [Item Scripts](#item-scripts)
    - [Reset Scripts](#reset-scripts)
    - [Battle Facility Scripts](#battle-facility-scripts)
    - [Black City / White Forest](#black-city--white-forest)
    - [Other Scripts](#other-scripts)
- [Making Scripts](#making-scripts)
- [Credits](#credits)
- [Script file format](#script-file-format)

## Installing Scripts
1. Download the [latest release](https://github.com/FlagBrew/PKSM-Scripts/releases/latest) (*not* the ones labeled "Source code")
2. Extract the contents and copy the `scripts` folder to your SD card so that its path is `/3ds/PKSM/scripts`

## Legality Warning
>There is risk to using some of these scripts, *particularly on the most recent games* (US/UM and Su/Mo).

The following is a list of unlabeled scripts (with no legal counterpart) known to edit parts of your save to illegal values:
- `all versions` **Set Vivillon Fancy Form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal
- `all versions` **Set Vivillon Pokeball form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal

### Replaced Scripts
Old versions of these scripts included the following elements that could be flagged as illegal if a save is put through strict hack checks
- `SM, USUM` **All items 99x** -- Black Flute, Blue Scarf, Bug Gem, Cherish Ball, Dark Gem, Discount Coupon, Dragon Gem, Dream Ball, Electric Gem, Fairy Gem, Fighting Gem, Fire Gem, Fluffy Tail, Flying Gem, Ghost Gem, Grass Gem, Green Scarf, Greet Mail, Ground Gem, Ice Gem, Macho Brace, Odd Keystone, Old Amber, Pink Scarf, Poison Gem, Psychic Gem, Red Scarf, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Shoal Salt, Shoal Shell, Sport Ball, Steel Gem, Water Gem, White Flute, Yellow Scarf
- `SM, USUM` **All Medicine 99x** -- Blue Flute, Red Flute, Yellow Flute
- `SM, USUM` **All berries 99x** -- Razz Berry, Nanab Berry, Wepear Berry, Cornn Berry, Magost Berry, Rabuta Berry, Nomel Berry, Spelon Berry, Pamtre Berry, Watmel Berry, Durin Berry, Belue Berry, Enigma Berry, Micle Berry, Custap Berry, Jaboca Berry, Rowap Berry
- `ORAS` **Unlock & max all O-Powers** -- unreleased S levels
- `XY, ORAS` **Give all items 99x** -- Bug Gem, Cherish Ball, Dark Gem, Dragon Gem, Electric Gem, Fairy Gem, Fast Ball, Fighting Gem, Fire Gem, Flying Gem, Friend Ball, Ghost Gem, Grass Gem, Ground Gem, Heavy Ball, Ice Gem, Level Ball, Love Ball, Lure Ball, Moon Ball, Odd Keystone, Park Ball, Poison Gem, Psychic Gem, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Sport Ball, Steel Gem, Water Gem
- `BW, B2W2` **Give all items 99x** -- Blue Scarf, Cherish Ball, Dream Ball, Fast Ball, Friend Ball, Green Scarf, Heavy Ball, Level Ball, Love Ball, Lure Ball, Moon Ball, Park Ball, Pink Scarf, Red Scarf, Safari Ball, Sport Ball, Yellow Scarf
- `BW, B2W2` **Give all berries 99x** -- Rabuta Berry, Pamtre Berry
- `BW` **All TMs and HMs owned** -- TM95 Snarl (only available from [an unreleased Gen 4 event](https://bulbapedia.bulbagarden.net/wiki/Lock_Capsule))
- `HGSS` **Give all pokeballs 99x** -- Cherish Ball, Park Ball, Sport Ball
- `DP, PT` **Give all pokeballs 99x** -- Cherish Ball
- `DP` **Give all items 99x** -- Shoal Salt, Shoal Shell

### Past Gen
These scripts may cause problems in the unlikely event you should ever have to go through thorough hack checks
- `HGSS` **Unlock all Pokewalker Courses** -- Rally, Sightseeing, and Amity Meadow were not released for all regions
- `PT, HGSS` **Give all items 99x** -- Griseous Orb (untradeable and only one can be obtained per file)
- `DP, PT` **Get all Pokewatch apps** -- Alarm Clock and Stopwatch were never released

## Script Notes
These are notes and details that may be useful to know about scripts that couldn't be summarized to fit in scripts' names

### Mass Inject Scripts
- All mass injection scripts target the first slot of Box 1 to start injecting the collection. If you're worried about losing some of your Pokémon, make sure to clear out enough of your in-game boxes to make room
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
- These scripts will fill your dex enough to unlock access to the following rewards:
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
- **National** versions will also unlock access to all corresponding regional rewards
- **owned** versions will also unlock access to all corresponding **seen** rewards
- **Complete** versions will unlock all the same rewards as the **National owned** versions
- Only the **Complete** versions will fill in Mythicals (Mew, Celebi, Jirachi, etc.)
- Only the **Complete (illegal)** versions will unlock *all* forms and shiny sprites, including unreleased ones

### Item Scripts
- `SM, USUM` **slot 1 x897-960**: due to the way items are stored in Gen 7 saves and the current limitations of PKSM's scripts, the quantity of the item in the pouch's first slot is set to something in the range of 897 to 960 (depends on the former quantity) rather than 999 like in past generations
- `BW, B2W2` **Item slot 1 - Pass Orb x65535**: this was only added because the MAX level Pass Powers require 9999 to use, which is more than existing scripts give
- `Gen IV, V, VI` **All TMs and HMs**: fills your TM pouch with *all* TMs and HMs, which may cause problems with story progression

### Reset Scripts
- `all games` **Reset [pokemon]**: Allows any listed Pokémon to be re-obtained (if gift) or re-battled
- `USUM` **Reset Main Conflict**: resets everything between getting to the Altar of the Sunne/Moone and encountering Mina
- `USUM` **Reset Postgame**: resets it back to the start of the Rainbow Rocket arc, when you enter your house, you meet Sophocles and go the Festival Plaza
- `USUM` **Reset Nanu Event**: ?
- `USUM` **Reset Team Skull Pose Event**: resets the event in Po Town where you help the Team Skull Grunt who can't make the Team Skull pose
- `USUM` **Reset Janitor Event**: resets the event that happens when you talk to the janitor in Hau'oli Mall
- `USUM` **Reset Shiny Exeggcute Battle**: resets the battle against the Poni Island trainer with the shiny Exeggcute
- `USUM` **Remove Stakataka and Blacephalon**: the reset scripts for these two cause them to respawn indefinitely after capture/defeat so this script was made to allow users to end that if they want
- `USUM` **Reset Red and Blue**: resets initial Battle Tree event in which you battle Red or Blue
- `ORAS` **Reset Delta Episode**: resets back to before the battle with Wallace in front of Sky Pillar
- `BW, B2W2` **Reset Geonet**: allows you to change the location you registered on the Geonet
- `B2W2` **Reset N and Shadow Triad**: allows you to rematch the trainers without waiting for the season to change
- `HGSS` **Reset Sinjoh Ruins**: resets the event where you take an Arceus to the Ruins of Alph and eventually receive a lv1 Dialga/Palkia/Giratina holding its respective Orb
- `HGSS` **Reset Red**: respawns Red at Mt. Silver without having to defeat the Elite Four
- `DP` **Set all legendaries battlable/disappeared**: same as **Reset [pokemon]** above

### Battle Facility Scripts
- `DP, PT, HGSS, XY, ORAS, SM, USUM` **Streak**: sets the current streak to just before a battle with the facility's leader
- `PT, HGSS` **Battle Factory Max Trades**: This will set your trade count to 9999. The more trades you do, the better Pokemon you can choose to rent at the start
- `PT, HGSS` **Battle Castle Points**: This will set your CP to 9999, allowing you to buy as many upgrades, items, heals, skips etc as you want. Note, you don't unlock the ability to skip a battle until you win 21 battles.

### Black City / White Forest
These codes fill all the settlement's slots in your game with predefined residents as described below. You can find details about what a particular resident provides on Bulbapedia's pages on [Black City](https://bulbapedia.bulbagarden.net/wiki/Black_City) and [White Forest](https://bulbapedia.bulbagarden.net/wiki/White_Forest).

`Front` means you will see them in your game, `Back` means others will see them when they connect to your game via Entralink

| Resident            | Set 1 | Set 2 | Set 3 |
| ------------------- | ----- | ----- | ----- |
| Ace Trainer Vincent | Front | Back  | -     |
| Battle Girl Karenna | Front | Back  | -     |
| Black Belt Ryder    | Front | Back  | -     |
| Clerk Britney       | Front | Back  | -     |
| Clerk Doug          | Front | Back  | -     |
| Lass Miki           | Front | Back  | -     |
| Roughneck Dave      | Front | Back  | -     |
| School Kid Leo      | Front | Back  | -     |
| School Kid Silvia   | Front | Back  | -     |
| Youngster Robbie    | Front | Back  | -     |
| Backpacker Emi      | Back  | -     | Front |
| Backpacker Herman   | Back  | -     | Front |
| Clerk Collin        | Back  | -     | Front |
| Pkm Ranger Eliza    | Back  | -     | Front |
| Pkm Ranger Ralph    | Back  | -     | Front |
| School Kid Shane    | Back  | -     | Front |
| Scientist Jacques   | Back  | -     | Front |
| Socialite Grace     | Back  | -     | Front |
| Veteran Ken         | Back  | -     | Front |
| Veteran Rosa        | Back  | -     | Front |
| Ace Trainer Lena    | -     | Front | Back  |
| Backpacker Carlos   | -     | Front | Back  |
| Backpacker Molly    | -     | Front | Back  |
| Clerk Piper         | -     | Front | Back  |
| Gentleman Frederic  | -     | Front | Back  |
| Hiker Gene          | -     | Front | Back  |
| Lady Lynette        | -     | Front | Back  |
| Nursery Aide Miho   | -     | Front | Back  |
| Rich Boy Pierce     | -     | Front | Back  |
| Scientist Marie     | -     | Front | Back  |

### Other Scripts
- `SM, USUM` **Shop 6 Tent Bonus**: set which bonus is active from the tent shop located in slot 6 (requires a tent shop to be in that slot)
- `USUM` **Set 100 hatched eggs**: set the number of hatched eggs to 100 so that you can just talk to the stats judge to unlock IV checking in the PC
- `USUM` **Set Sun/Moon time**: sets the in-game time of day, to allow access to time limited events (only available during day/night)
- `XY, ORAS` **Supreme Honor Pokepuffs**: fill all 100 Pokepuff slots with Supreme Honor Pokepuffs
- `XY, ORAS` **Pokemon Link**: These codes will allow you to acquire these event Pokemon from the Pokemon Link on the main menu. Until you claim it in-game, using more than one at a time will overwrite any you've already injected. If you care about legality, Celebi can only come from X & Y and Glalie and Steelix can only be received from ORAS. For some reason, trying to inject the ORAS Demo Pokemon won't work more than once.
- `ORAS` **Mirage Spots**: Sets the available Mirage Spots to the set selected, all of which also include Crescent Isle where you can find Cresselia. Spots will change when the date changes, and may change if you pass people through the PSS
- `BW, B2W2` **Pass Power MAX**: changes your currently equipped Pass Power. These MAX versions are as powerful as Lv3 and last for 1 full hour, but cost 9999 Pass Orbs to activate so you will need to use these along with the **Items slot 1 - Pass Orb x65535** script
- `BW, B2W2` **Season**: changes the current season of the save -- Note that changing area (leaving a building/cave, changing route, etc.) will update the season to match the system's current date
- `B2W2` **Join Avenue - Restock All Shops**: This will refill all the shops contents and therefore, you can buy from all the shops again without having to wait for the next day.
- `B2W2` **Join Avenue - 7 Day Promotion**: This will cause a week long promotional event. When this code is used, for one week from when the game was last saved, all the shop's items are only half price!
- `B2W2` **Join Avenue - Lv9 All Shops**: this code will set all of your shops to level 9 and as such, only one visitor referral will be necessary to max out each shop
- `DP, Pt` **Fulfill Spiritomb encounter requirements**: sets everything up so that you will battle Spiritomb the next time you examine the Broken Tower / Hallowed Tower on Route 209

---

## Making Scripts
See the [docs README](https://github.com/FlagBrew/PKSM-Scripts/blob/master/docs/README.md)

---

## Credits
- bernardogiordano - PKSM, PKSMScript.py, dump.py, scripts
- Lavorther - scripts
- piepie62 - genScripts.py
- PKMWM1 - scripts
- PlasticJustice - scripts
- SpiredMoth - scripts, documentation, Node.js versions of Python scripts
- trainboy2019 - scripts
- wrathsoffire - scripts

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
