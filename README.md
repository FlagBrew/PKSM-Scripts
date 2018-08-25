# PKSMScript

## Installing Scripts
1. Download the [latest release](https://github.com/FlagBrew/PKSM-Scripts/releases/latest)
1. Extract the contents and copy the `scripts` folder to your SD card so that its path is `sd:/3ds/PKSM/scripts`

## Legality Warning
>There is risk to using some of these scripts, *particularly on the most recent games* (US/UM and Su/Mo).

The following is a list of unlabeled scripts (with no legal counterpart) known to edit parts of your save to illegal values:
- `all versions` **Set Vivillon Fancy Form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal
- `all versions` **Set Vivillon Pokeball form** -- any Scatterbug/Spewpa/Vivillon caught or bred after using this will be illegal

#### Gen 7 (US/UM and Su/Mo)
Discarding or selling the listed items **BEFORE** going online *should* let you avoid trouble
- `SM, USUM` **Give all items 99x** -- Black Flute, Blue Flute, Blue Scarf, Bug Gem, Cherish Ball, Dark Gem, Discount Coupon, Dragon Gem, Dream Ball, Electric Gem, Fairy Gem, Fighting Gem, Fire Gem, Fluffy Tail, Flying Gem, Ghost Gem, Grass Gem, Green Scarf, Greet Mail, Ground Gem, Ice Gem, Macho Brace, Odd Keystone, Old Amber, Pink Scarf, Poison Gem, Psychic Gem, Red Flute, Red Scarf, Relic Band, Relic Copper, Relic Crown, Relic Gold, Relic Silver, Relic Statue, Relic Vase, Rock Gem, Safari Ball, Shoal Salt, Shoal Shell, Sport Ball, Steel Gem, Water Gem, White Flute, Yellow Flute, Yellow Scarf
- `SM, USUM` **Give all berries 99x** -- Razz Berry, Nanab Berry, Wepear Berry, Cornn Berry, Magost Berry, Rabuta Berry, Nomel Berry, Spelon Berry, Pamtre Berry, Watmel Berry, Durin Berry, Belue Berry, Enigma Berry, Micle Berry, Custap Berry, Jaboca Berry, Rowap Berry

#### Past Gen
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

---

## Building Scripts
See the [docs README](./docs/README.md)


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
