#include <pksm.h>
#include <stdlib.h> /* rand */
#include <stdio.h> /* sprintf */
#include <time.h> /* time */

int limit_num(int min, int max, int max_digits)
{
    unsigned int num;
    char hint[35] = {'\0'};
    sprintf(hint, "Enter a number from %d to %d", min, max);
    while (1)
    {
        gui_warn(hint);
        gui_numpad(&num, hint, max_digits);
        if (num >= min && num <= max)
        {
            break;
        }
        gui_warn("Invalid input\nPlease try again.");
    }
    return (int)num;
}

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    enum Generation gen_sav;
    int limit_lang = 9, limit_name = 13, limit_ball = 26;

    switch (version)
    {
        case 1: // R
        case 2: // S
        case 3: // E
        case 4: // FR
        case 5: // LG
            gen_sav = GEN_THREE;
            limit_lang = 7;
            limit_name = 8;
            limit_ball = 13;
            break;
        case 10: // D
        case 11: // P
        case 12: // PT
        case 7:  // HG
        case 8:  // SS
            gen_sav = GEN_FOUR;
            limit_lang = 7;
            limit_name = 8;
            limit_ball = 24;
            break;
        case 20: // W
        case 21: // B
        case 22: // W2
        case 23: // B2
            gen_sav = GEN_FIVE;
            limit_lang = 7;
            limit_name = 8;
            limit_ball = 25;
            break;
        case 24: // X
        case 25: // Y
        case 26: // AS
        case 27: // OR
            gen_sav = GEN_SIX;
            limit_lang = 7;
            limit_ball = 25;
            break;
        case 30: // Su
        case 31: // Mo
        case 32: // US
        case 33: // UM
            gen_sav = GEN_SEVEN;
            break;
        case 42: // LGP
        case 43: // LGE
            gen_sav = GEN_LGPE;
            limit_ball = 6;
            break;
        case 44: // SW
        case 45: // SH
            gen_sav = GEN_EIGHT;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    char *targets[4] = {
        "Exit script",
        "Use save boxes",
        "Use current bank",
        "Choose bank"
    };
    int target = -1, prop = -1,
        boxes, skip, pkm_size = pkx_box_size(gen_sav),
        choice = 0, slots_per_box;
    int values[3] = {0};

    /* Editable Props */
    char *props[21] = {
        "Exit Script",
        "Previous menu",
        "Set OT name",
        "Set OT TID",
        "Set OT SID",
        "Set OT Gender",
        "Set Level",
        "Set Shiny",
        "Set all IVs",
        "Set Language",
        "Set Pokérus",
        "Set Nature",
        "Set Ball",
        "Set PP Ups",
        "Clear moves",
        "Randomize PIDs",
        "Remove all ribbons",
        "Set Met Date",
        "Set Egg Date",
        "Clear nicknames",

        // NEW: add new options here

        "Set Item"
    };
    enum PKX_Field fields[21] = {
        NICKNAME, // filler -- Exit Script
        GENDER,   // filler -- Previous menu
        OT_NAME,
        TID,
        SID,
        OT_GENDER,
        LEVEL,
        SHINY,
        IV_HP,
        LANGUAGE,
        POKERUS,
        NATURE,
        BALL,
        PP_UPS,
        MOVE,
        PID,
        NICKNAME, // filler -- Remove all ribbons
        MET_YEAR, // filler -- Set Met Date
        EGG_YEAR, // filler -- Set Egg Date
        NICKNAMED,

        // NEW: add 1 PKX_FIELD for your new option here

        ITEM};

    /* Sub-option variables */
    char *languages[9] = {
        "\u65e5\u672c\u8a9e",          // JAP
        "English",                     // ENG
        "Fran\u00e7ais",               // FRE
        "Italiano",                    // ITA
        "Deutsche",                    // GER
        "Espa\u00f1ol",                // SPA
        "\ud55c\uad6d\uc5b4",          // KOR
        "\u4e2d\u6587 (\u7b80\u4f53)", // CHS?
        "\u4e2d\u6587 (\u7e41\u9ad4)"  // CHT?
    };
    char *pokerus[3] = {"Infected", "Cured", "Not infected"};
    char *genders[2] = {"Male", "Female"};
    char *shininess[2] = {"Shiny", "Normal"};
    char *natures[25] = {
        "Hardy", "Lonely", "Brave", "Adamant", "Naughty",
        "Bold", "Docile", "Relaxed", "Impish", "Lax",
        "Timid", "Hasty", "Serious", "Jolly", "Naive",
        "Modest", "Mild", "Quiet", "Bashful", "Rash",
        "Calm", "Gentle", "Sassy", "Careful", "Quirky"};
    char *balls[26] = {
        "Cherish Ball", "Poke Ball", "Great Ball", "Ultra Ball",
        "Master Ball", "Premier Ball", "Dive Ball", "Luxury Ball",
        "Nest Ball", "Net Ball", "Repeat Ball", "Safari Ball",
        "Timer Ball", "Dusk Ball", "Heal Ball", "Quick Ball",
        "Fast Ball", "Friend Ball", "Heavy Ball", "Level Ball",
        "Love Ball", "Lure Ball", "Moon Ball", "Sport Ball",
        "Dream Ball", "Beast Ball"};
    int ball_ids[26] = {
        16, 4, 3, 2,
        1, 12, 7, 11,
        8, 6, 9, 5,
        10, 13, 14, 15,
        17, 22, 20, 18,
        21, 19, 23, 24,
        25, 26};
    enum Generation gen_pkm;
    char name[0x27] = {'\0'};

    srand(time(0) + version);
    int props_count = sizeof(props);
    if (sizeof(fields) < props_count)
    {
        props_count = sizeof(fields);
    }

    gui_warn("Edits made by this script may result\nin illegal Pokémon");
    while (target && prop)
    {
        target = gui_menu_20x2("Pick a group of Pokémon to edit", 4, targets);
        if (target == 0)
        {
            break;
        }
        else if (target == 3)
        {
            bank_select();
        }

        if (target == 1)
        {
            boxes = sav_get_max(MAX_BOXES);
            gen_pkm = gen_sav;
            sav_box_decrypt();
            if (gen_sav != GEN_LGPE) {
                slots_per_box = sav_get_max(MAX_SLOTS) / boxes;
            }
            else {
                slots_per_box = 30;
            }
        }
        else
        {
            boxes = bank_get_size();
            slots_per_box = 30;
        }

        while (prop)
        {
            skip = 0;
            prop = gui_menu_20x2("Pick a property to edit\n\nWarning: these edits will affect\nEVERYTHING in the boxes of\nyour save/bank, and may result\nin illegal Pokémon", props_count, props);
            switch (prop)
            {
                case 2: // OT Name
                    gui_keyboard(name, "Enter an OT name", target == 1 ? limit_name : 0xD);
                    break;
                case 3: // OT TID
                case 4: // OT SID
                    gui_warn("IDs must be the old style\nin the range of 0 to 65535");
                    values[0] = limit_num(0, 65535, 5);
                    break;
                case 5: // OT Gender
                    values[0] = gui_menu_20x2("Choose OT gender", 2, genders);
                    break;
                case 6: // Level
                    values[0] = limit_num(1, 100, 3);
                    break;
                case 7: // Shiny
                    values[0] = 1 - gui_menu_20x2("Shiny or not?\n\nWarning:\nShiny may take a while", 2, shininess);
                    break;
                case 8: // all IVs
                    values[0] = limit_num(0, 31, 2);
                    break;
                case 9: // Language
                    choice = gui_menu_20x2("Choose a language", target == 1 ? limit_lang : 9, languages);
                    values[0] = choice + (choice >= 6 ? 2 : 1);
                    break;
                case 10: // Pokerus
                    choice = gui_menu_20x2("Pick a Pokerus option", 3, pokerus);
                    values[0] = choice < 2 ? 0xF : 0; // strain
                    values[1] = choice == 0 ? 4 : 0; // days
                    break;
                case 11: // Nature
                    values[0] = gui_menu_20x2("Pick a nature", 25, natures);
                    break;
                case 12: // Ball
                    choice = gui_menu_20x2("Pick a ball", target == 1 ? limit_ball : 26, balls);
                    values[0] = ball_ids[choice];
                    break;
                case 13: // PP Ups
                    values[0] = limit_num(0, 3, 1);
                    break;
                case 14: // Clear moves
                    values[0] = 0;
                    break;
                case 15: // Random PID
                    choice = gui_choice("Should shiny Pokémon remain shiny?");
                    break;
                case 16: // Remove all ribbons
                    // Since Ribbons not supplied through PKX_Field harcoded offsets
                    // are required. This test lets allows updates to this script
                    // subfunction to lag behind PKSM adding new generations
                    if (target == 1 && gen_sav > GEN_THREE)
                    {
                        skip = 1;
                        gui_warn("This generation is not yet supported.");
                    }
                    else
                    {
                        gui_warn("Some generations may be missing support.\nSome Pokémon may be skipped.");
                    }
                    break;
                case 18: // Set Egg Date
                    gui_warn("Only things with an Egg Date\nwill be edited.");
                    // intentional fallthrough
                case 17: // Set Met Date
                    gui_warn("Input new year value to use");
                    values[0] = limit_num(prop == 17 ? 2001 : 2000, 2255, 4);
                    gui_warn("Input new month value to use");
                    values[1] = limit_num(1, 12, 2); // month
                    gui_warn("Input new day value to use");
                    values[2] = limit_num(1, 31, 2); // day
                    break;
                case 19: // Clear nicknames
                    break;
                // NEW: add case for new option here
                // case 20: // Item
                //     // int (0-?)
                //     break;
                default:
                    if (prop > 1)
                    {
                        gui_warn("This edit type is not available.\nPlease choose another.");
                    }
                    skip = 1;
                    break;
            }

            if (prop < 2)
            {
                break;
            }
            if (skip)
            {
                continue;
            }

            gui_splash("This may take some time");
            for (int box = 0; box < boxes; box++)
            {
                for (int slot = 0; slot < slots_per_box; slot++)
                {
                    if (target == 1 && gen_sav == GEN_LGPE && box * 30 + slot == 1000)
                    {
                        break;
                    }

                    char *pkm;
                    if (target == 1)
                    {
                        pkm = malloc(pkm_size);
                        sav_get_pkx(pkm, box, slot);
                    }
                    else
                    {
                        pkm = bank_get_pkx(&gen_pkm, box, slot);
                    }

                    if (!pkx_is_valid(pkm, gen_pkm))
                    {
                        free(pkm);
                        continue;
                    }

                    if (prop == 15 && gen_pkm != GEN_FOUR && gen_pkm != GEN_THREE)
                    {
                        values[0] = (rand() & 0xFFFF) << 16;
                        values[0] |= (rand() & 0xFFFF);
                    }

                    if (prop == 2) // OT name
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], &name[0]);
                    }
                    else if (prop == 8) // IVs
                    {
                        for (int i = 0; i < 6; i++)
                        {
                            pkx_set_value(pkm, gen_pkm, fields[prop] + i, values[0]);
                        }
                    }
                    else if (prop == 10) // Pokerus
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], values[0], values[1]);
                    }
                    else if (prop == 13 || prop == 14) // PP Ups, Clear moves
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            int move = pkx_get_value(pkm, gen_pkm, MOVE, i);
                            if (move)
                            {
                                pkx_set_value(pkm, gen_pkm, fields[prop], i, values[0]);
                            }
                        }
                        if (prop == 14)
                        {
                            pkx_set_value(pkm, gen_pkm, fields[prop], 0, 1);
                        }
                    }
                    else if (prop == 15) // Randomize PID
                    {
                        values[1] = pkx_get_value(pkm, gen_pkm, SHINY);
                        if (gen_pkm == GEN_FOUR || gen_pkm == GEN_THREE)
                        {
                            // Gen 3/4 PID is rerolled when setting PID-dependent value
                            pkx_set_value(pkm, gen_pkm, fields[1], pkx_get_value(pkm, gen_pkm, fields[1]));
                        }
                        else
                        {
                            pkx_set_value(pkm, gen_pkm, PID, values[0]);
                        }
                        if (choice && values[1])
                        {
                            pkx_set_value(pkm, gen_pkm, SHINY, 1);
                        }
                    }
                    else if (prop == 16) // Remove all ribbons
                    {
                        // No Ribbon entries in PKX_Field enum so offsets are hardcoded
                        if (gen_pkm == GEN_THREE)
                        {
                            *(short *)(pkm + 0x4C) = 0;
                            pkm[0x4E] = 0;
                            pkm[0x4F] = 0x80 & pkm[0x4F]; // preserve Fateful Encounter flag if present
                        }
                        else if (gen_pkm == GEN_FOUR || gen_pkm == GEN_FIVE)
                        {
                            *(int *)(pkm + 0x24) = 0;
                            *(int *)(pkm + 0x3C) = 0;
                            *(int *)(pkm + 0x60) = 0;
                        }
                        else if (gen_pkm < GEN_EIGHT)
                        {
                            *(int *)(pkm + 0x30) = 0;
                            *(short *)(pkm + 0x34) = 0;
                            pkm[0x36] = 0;
                            if (gen_pkm != GEN_LGPE)
                            {
                                *(short *)(pkm + 0x38) = 0;
                            }
                        }
                        else if (gen_pkm == GEN_EIGHT)
                        {
                            pkm[0x33] = 0;
                            *(int *)(pkm + 0x34) = 0;
                            *(int *)(pkm + 0x38) = 0;
                            *(short *)(pkm + 0x38) = 0;
                        }
                    }
                    else if (prop == 17) // Set Met Date
                    {
                        pkx_set_value(pkm, gen_pkm, MET_YEAR, values[0]);
                        pkx_set_value(pkm, gen_pkm, MET_MONTH, values[1]);
                        pkx_set_value(pkm, gen_pkm, MET_DAY, values[2]);
                    }
                    else if (prop == 18) // Set Egg Date
                    {
                        // only edit things with an Egg Date
                        if (pkx_get_value(pkm, gen_pkm, EGG_LOCATION))
                        {
                            pkx_set_value(pkm, gen_pkm, EGG_YEAR, values[0]);
                            pkx_set_value(pkm, gen_pkm, EGG_MONTH, values[1]);
                            pkx_set_value(pkm, gen_pkm, EGG_DAY, values[2]);
                        }
                    }
                    else if (prop == 19) // Clear nickname
                    {
                        pkx_set_value(pkm, gen_pkm, NICKNAME, i18n_species(pkx_get_value(pkm, gen_pkm, SPECIES)));
                        pkx_set_value(pkm, gen_pkm, NICKNAMED, 0);
                    }
                    // NEW: add new if case for prop editing here
                    else
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], values[0]);
                    }

                    if (target == 1)
                    {
                        sav_inject_pkx(pkm, gen_pkm, box, slot, 1);
                    }
                    else
                    {
                        bank_inject_pkx(pkm, gen_pkm, box, slot);
                    }
                    free(pkm);
                }
            }
        }

        if (target == 1)
        {
            sav_box_encrypt();
        }
    }

    return 0;
}
