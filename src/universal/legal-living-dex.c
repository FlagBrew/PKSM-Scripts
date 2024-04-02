#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    // Future updates should only have to add entries to
    // these two variables and the switch block
    enum Generation gens[] = {
        GEN_ONE,
        GEN_TWO,
        GEN_THREE,
        GEN_FOUR,
        GEN_FIVE,
        GEN_SIX,
        GEN_SEVEN,
        GEN_LGPE,
        GEN_EIGHT
    };
    char *dexFiles[] = {
        "PK1", "https://cdn.sigkill.tech/dex/pk1.txt",  // contains 1-151
        "PK2", "https://cdn.sigkill.tech/dex/pk2.txt",  // contains 1-251
        "PK3", "https://cdn.sigkill.tech/dex/pk3.txt",  // contains 1-386
        "PK4", "https://cdn.sigkill.tech/dex/pk4.txt",  // contains 387-493
        "PK5", "https://cdn.sigkill.tech/dex/pk5.txt",  // contains 494-649
        "PK6", "https://cdn.sigkill.tech/dex/pk6.txt",  // contains 650-721
        "PK7", "https://cdn.sigkill.tech/dex/pk7.txt",  // contains 722-807
        "PB7", "https://cdn.sigkill.tech/dex/pb7.txt",  // contains 1-151, 808-809
        "PK8", "https://cdn.sigkill.tech/dex/pk8.txt"   // contains 810-893
    };
    int start = 2, end = 9, box = 30;
    enum Generation genSave = GEN_EIGHT;

    char *targets[4] = {
        "Exit script",
        "Use save boxes",
        "Use current bank",
        "Choose bank"
    };
    int target = gui_menu_20x2("Where should the living dex\nbe injected?\n\nWarning:\nInjection starts at\nBox 1 Slot 1\nwhich may overwrite\nanything already there", 4, targets);
    if (target == 0)
    {
        return 0;
    }
    else if (target == 1)
    {
        switch (*argv[0])
        {
            case 35: case 36: case 37:  // R/G/B (VC)
            case 38:                    // Y (VC)
                start = 0;
                end = 1;
                genSave = GEN_ONE;
                break;
            case 39: case 40:  // G/S (VC)
            case 41:           // C (VC)
                start = 1;
                end = 2;
                genSave = GEN_TWO;
                break;
            case  1: case  2:  // RS
            case  3:           // E
            case  4: case  5:  // FRLG
                end = 3;
                genSave = GEN_THREE;
                break;
            case 10: case 11:  // DP
            case 12:           // PT
            case  7: case  8:  // HGSS
                end = 4;
                genSave = GEN_FOUR;
                break;
            case 20: case 21:  // BW
            case 22: case 23:  // B2W2
                end = 5;
                genSave = GEN_FIVE;
                break;
            case 24: case 25:  // XY
            case 26: case 27:  // ORAS
                end = 6;
                genSave = GEN_SIX;
                break;
            case 30: case 31:  // SM
            case 32: case 33:  // USUM
                end = 7;
                genSave = GEN_SEVEN;
                break;
            case 42: case 43:  // LGPE
                start = 7;
                end = 8;
                genSave = GEN_LGPE;
                break;
            case 44: case 45:  // SwSh
                // end = 9;
                // genSave = GEN_EIGHT;
                break;
            default:
                gui_warn("This game is not yet supported");
                return 0;
        }
        box = sav_get_max(MAX_SLOTS) / sav_get_max(MAX_BOXES);
        sav_box_decrypt();
    }
    else if (target == 3)
    {
        bank_select();
    }

    char *url = NULL,
         *currentData = NULL,
         *currentPokemon = NULL,
         *pos = NULL;
    unsigned char *newPkmn = NULL;
    int currentDataSize = 0, slot = 0,
        response, i, size, newPkmSize, species;
    enum Generation genData;

    gui_splash("Injecting legal living dex...");
    for (i = start; i < end; i++)
    {
        free(currentData);
        url = dexFiles[i * 2 + 1];
        response = fetch_web_content(&currentData, &currentDataSize, url);
        if (response != 200 || currentData == NULL || currentDataSize == 0)
        {
            free(currentData);
            if (target == 1)
            {
                sav_box_encrypt();
            }

            char printMe[64];
            sprintf(printMe, "Problem downloading %s dex: %i", dexFiles[i * 2], response);
            gui_warn(printMe);
            return 1;
        }
        currentPokemon = currentData;
        genData = gens[i];

        while ((pos = strchr(currentPokemon, '\n')) != NULL)
        {
            size = (int)pos - (int)currentPokemon - (*(pos - 1) == '\r' ? 1 : 0);
            base64_decode(&newPkmn, &newPkmSize, currentPokemon, size);

            species = pkx_get_value((char*)newPkmn, genData, SPECIES);
            if (target == 1)
            {
                if (sav_check_value(SAV_VALUE_SPECIES, species) &&
                    (genData != GEN_LGPE ||  // always inject non-LGPE data
                     species > 151 ||        // always inject Meltan and Melmetal
                     genSave == GEN_LGPE)    // inject LGPE data into LGPE saves
                )
                {
                    sav_inject_pkx((char*)newPkmn, genData, slot / box, slot % box, 0);
                    slot += 1;
                }
            }
            else
            {
                if (genData != GEN_LGPE || species > 151)
                {
                    bank_inject_pkx((char*)newPkmn, genData, slot / box, slot % box);
                    slot += 1;
                }
            }
            free(newPkmn);
            currentPokemon = pos + 1;
        }
    }

    if (target == 1)
    {
        sav_box_encrypt();
    }
    free(currentData);
    gui_warn("Legal living dex injected successfully!");
    return 0;
}
