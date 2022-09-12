#include <pksm.h>   // PKSM provided virtual header giving access to scripting API
#include <stdlib.h> // malloc, free

int main(int argc, char **argv)
{
    enum Generation genSav;
    switch (*argv[0])
    {
        case 1: case 2:
        case 3:
        case 4: case 5:
            genSav = GEN_THREE;
            break;
        case 10: case 11:
        case 12:
        case 7: case 8:
            genSav = GEN_FOUR;
            break;
        case 20: case 21:
        case 22: case 23:
            genSav = GEN_FIVE;
            break;
        case 24: case 25:
        case 26: case 27:
            genSav = GEN_SIX;
            break;
        case 30: case 31:
        case 32: case 33:
            genSav = GEN_SEVEN;
            break;
        case 42: case 43:
            genSav = GEN_LGPE;
            break;
        case 44: case 45:
            genSav = GEN_EIGHT;
            break;
        default:
            gui_warn("This script does not yet\nsupport this game.");
            return 0;
    }

    char *bankOpts[] = {
        "Exit script",
        "Current bank",
        "Another bank"
    };
    int choice = gui_menu_20x2("Which bank should be injected\ninto your save's Pokédex?", 3, bankOpts);
    if (choice == 2)
    {
        bank_select();
    }

    if (choice)
    {
        sav_box_decrypt();
        int pkmSizeSav = pkx_box_size(genSav), maxSlots = sav_get_max(MAX_SLOTS) - 1, species, isEgg = 0;
        char *pkxSav = malloc(pkmSizeSav), *pkxInject = malloc(pkmSizeSav), *pkxBank;
        enum Generation genBank;
        sav_get_pkx(pkxSav, 0, 0); // save what's already in Box 1 slot 1

        gui_splash("Injecting data\nThis may take a while.");
        maxSlots = bank_get_size() * 30;
        pkx_generate(pkxInject, 1);
        for (int i = 0; i < maxSlots; i++)
        {
            pkxBank = bank_get_pkx(&genBank, i / 30, i % 30);
            if (pkx_is_valid(pkxBank, genBank))
            {
                // make sure pkm from bank is valid for save
                species = pkx_get_value(pkxBank, genBank, SPECIES);
                isEgg = pkx_get_value(pkxBank, genBank, EGG);
                if (!isEgg && sav_check_value(SAV_VALUE_SPECIES, species))
                {
                    pkx_set_value(pkxInject, genSav, SPECIES, species);
                    pkx_set_value(pkxInject, genSav, GENDER, pkx_get_value(pkxBank, genBank, GENDER));
                    pkx_set_value(pkxInject, genSav, SHINY, pkx_get_value(pkxBank, genBank, SHINY));
                    pkx_set_value(pkxInject, genSav, LANGUAGE, pkx_get_value(pkxBank, genBank, LANGUAGE));

                    // some validation for forms
                    int form = pkx_get_value(pkxBank, genBank, FORM);
                    if (form >= sav_get_max(MAX_FORM, species) ||
                        (species == 25 && genSav != genBank &&
                         ((genSav == GEN_SIX || genBank == GEN_SIX) || (genSav == GEN_LGPE || genBank == GEN_LGPE))))
                    {
                        form = 0;
                    }
                    pkx_set_value(pkxInject, genSav, FORM, form);

                    // native/foreign for XY
                    pkx_set_value(pkxInject, genSav, ORIGINAL_GAME, pkx_get_value(pkxBank, genBank, ORIGINAL_GAME));

                    sav_inject_pkx(pkxInject, genSav, 0, 0, 0);
                }
            }
            free(pkxBank);
        }

        // cleanup
        sav_inject_pkx(pkxSav, genSav, 0, 0, 0);
        sav_box_encrypt();
        free(pkxSav);
        free(pkxInject);

        gui_warn("Bank contents successfully injected\ninto save's Pokédex.");
    }
    else
    {
        gui_warn("Exiting script without editing the Pokédex");
    }

    return 0;
}
