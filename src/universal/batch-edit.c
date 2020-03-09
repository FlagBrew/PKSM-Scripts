#include <pksm.h>
#include <unistd.h>
#include <stdlib.h> /* rand */
#include <stdio.h> /* sprintf */
#include <time.h> /* time */

int limit_num(int min, int max, int max_digits)
{
    unsigned int num;
    char *hint[35] = {'\0'};
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
    unsigned char version = *argv[2];
    enum Generation gen_sav;

    switch (version)
    {
        case 10: // D
        case 11: // P
        case 12: // PT
        case 7:  // HG
        case 8:  // SS
            gen_sav = GEN_FOUR;
            break;
        case 20: // W
        case 21: // B
        case 22: // W2
        case 23: // B2
            gen_sav = GEN_FIVE;
            break;
        case 24: // X
        case 25: // Y
        case 26: // AS
        case 27: // OR
            gen_sav = GEN_SIX;
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
            break;
        case 44: // SW
        case 45: // SH
            gen_sav = GEN_EIGHT;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    char *targets = {
        "Exit script",
        "Use save boxes",
        "Use current bank",
        "Choose bank"
    };
    char *props[17] = {
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
        "Set Pokerus",
        "Set Nature",
        "Set Ball",
        "Set PP Ups",
        "Clear moves",
        "Randomize PIDs",
        "Set Item"
    };
    enum PKX_Field fields[17] = {
        NICKNAME, // filler
        GENDER, // filler
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
        ITEM
    };
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
        "Master Ball", "Ultra Ball", "Great Ball", "Poke Ball",
        "Safari Ball", "Net Ball", "Dive Ball", "Nest Ball",
        "Repeat Ball", "Timer Ball", "Luxury Ball", "Premier Ball",
        "Dusk Ball", "Heal Ball", "Quick Ball", "Cherish Ball",
        "Fast Ball", "Level Ball", "Lure Ball", "Heavy Ball",
        "Love Ball", "Friend Ball", "Moon Ball", "Sport Ball",
        "Dream Ball", "Beast Ball"};
    int boxes, box, slot,
        pkm_size = pkx_box_size(gen_sav),
        target = -1, prop = -1,
        choice, val_1, val_2;
    enum Generation gen_pkm;
    char name[0x27] = {'\0'};

    srand(time(0) + version);

    gui_warn("Edits made by this script may result in illegal Pokémon");
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
        }
        else
        {
            boxes = bank_get_size();
        }


        while (prop)
        {
            prop = gui_menu_20x2("Pick a property to edit", 15, props);
            if (prop < 2)
            {
                break;
            }

            switch (prop)
            {
                case 2: // OT Name
                    gui_keyboard(&name, "Enter an OT name", 0xD);
                    break;
                case 3: // OT TID
                case 4: // OT SID
                    gui_warn("IDs must be the old style\nin the range of 0 to 65535");
                    val_1 = limit_num(0, 65535, 5);
                    break;
                case 5: // OT Gender
                    val_1 = gui_menu_20x2("Choose OT gender", 2, genders);
                    break;
                case 6: // Level
                    val_1 = limit_num(1, 100, 3);
                    break;
                case 7: // Shiny
                    choice = gui_menu_20x2("Shiny or not?", 2, shininess);
                    val_1 = choice - 2;
                    break;
                case 8: // all IVs
                    val_1 = limit_num(0, 31, 2);
                    break;
                case 9: // Language
                    choice = gui_menu_20x2("Choose a language", version < 30 ? 7 : 9, languages);
                    val_1 = choice + (choice >= 6 ? 2 : 1);
                    break;
                case 10: // Pokerus
                    choice = gui_menu_20x2("Pick a Pokerus option", 3, pokerus);
                    val_1 = choice < 2 ? 0xF : 0; // strain
                    val_2 = choice == 0 ? 4 : 0; // days
                    break;
                case 11: // Nature
                    val_1 = gui_menu_20x2("Pick a nature", 25, natures);
                    break;
                case 12: // Ball
                    val_1 = gui_menu_20x2("Pick a ball", 18, balls) + 1;
                    break;
                case 13: // PP Ups
                    val_1 = limit_num(0, 3, 1);
                    break;
                case 14: // Clear moves
                    val_1 = 0;
                    break;
                case 15: // Random PID
                    break;
                // case 16: // Item
                //     // int (0-?)
                //     break;
                default:
                    gui_warn("This edit type is not available.\nPlease choose another.");
                    continue;
            }

            for (int box = 0; box < boxes; box++)
            {
                for (int slot = 0; slot < 30; slot++)
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
                        pkm = bank_get_pkx(gen_pkm, box, slot);
                    }

                    if (prop == 15 && gen_pkm != GEN_FOUR && gen_pkm != GEN_THREE)
                    {
                        val_1 = (rand() & 0xFFFF) << 16;
                        val_1 |= (rand() & 0xFFFF);
                    }

                    if (prop == 1) // OT name
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], name);
                    }
                    else if (prop == 8) // IVs
                    {
                        for (int i = 0; i < 6; i++)
                        {
                            pkx_set_value(pkm, gen_pkm, fields[prop] + i, val_1);
                        }
                    }
                    else if (prop == 10) // Pokerus
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], val_1, val_2);
                    }
                    else if (prop == 13 || prop == 14) // PP Ups, Clear moves
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            pkx_set_value(pkm, gen_pkm, fields[prop], i, val_1);
                        }
                        if (prop == 14)
                        {
                            pkx_set_value(pkm, gen_pkm, fields[prop], 0, 1);
                        }
                    }
                    else if (prop == 15 && (gen_pkm == GEN_FOUR || gen_pkm == GEN_THREE))
                    {
                        // Gen 3/4 PID is rerolled when setting PID-dependent value
                        pkx_set_value(pkm, gen_pkm, fields[1], pkx_get_value(pkm, gen_pkm, fields[1]));
                    }
                    else
                    {
                        pkx_set_value(pkm, gen_pkm, fields[prop], val_1);
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
