#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)argv[0];
    unsigned char version = *argv[2];
    enum Generation gen;
    int gbo = sav_gbo(), numOpts = 3, pkmSize,
        ofsSlots[5] = {0}, ofsPkm, ofsExp;

    switch (version)
    {
        case 10:
        case 11:
            gen = GEN_FOUR;
            ofsSlots[1] = 0x141c;
            ofsSlots[2] = 0x1508;
            pkmSize = pkx_party_size(gen);
            ofsPkm = 0;
            ofsExp = pkmSize - 4;
            break;
        case 12:
            gen = GEN_FOUR;
            ofsSlots[1] = 0x1654;
            ofsSlots[2] = 0x1740;
            pkmSize = pkx_party_size(gen);
            ofsPkm = 0;
            ofsExp = pkmSize - 4;
            break;
        case 7:
        case 8:
            gen = GEN_FOUR;
            ofsSlots[1] = 0x15fc;
            ofsSlots[2] = 0x16e8;
            pkmSize = pkx_party_size(gen);
            ofsPkm = 0;
            ofsExp = pkmSize - 4;
            break;
        case 20:
        case 21:
            gen = GEN_FIVE;
            ofsSlots[1] = 0x20e00;
            ofsSlots[2] = 0x20ee4;
            pkmSize = pkx_party_size(gen);
            ofsPkm = 4;
            ofsExp = 4 + pkmSize;
            break;
        case 22:
        case 23:
            gen = GEN_FIVE;
            ofsSlots[1] = 0x20d00;
            ofsSlots[2] = 0x20de4;
            pkmSize = pkx_party_size(gen);
            ofsPkm = 4;
            ofsExp = 4 + pkmSize;
            break;
        case 24:
        case 25:
            gen = GEN_SIX;
            ofsSlots[1] = 0x1b200;
            ofsSlots[2] = 0x1b2f0;
            pkmSize = pkx_box_size(gen);
            ofsExp = 4;
            ofsPkm = 8;
            break;
        case 26:
        case 27:
            gen = GEN_SIX;
            numOpts += 2;
            ofsSlots[1] = 0x1bc00;
            ofsSlots[2] = 0x1bcf0;
            ofsSlots[3] = 0x1bdf0;
            ofsSlots[4] = 0x1bee0;
            pkmSize = pkx_box_size(gen);
            ofsExp = 4;
            ofsPkm = 8;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 0;
    }

    char *pkm = malloc(pkmSize);
    if (pkm == NULL)
    {
        gui_warn("An error occurred.\nPlease try running the script again.");
        return 1;
    }

    // read data from save
    int i, steps[5] = {0};
    struct pkx slots[5];
    for (i = 0; i < 5; i++)
    {
        slots[i].species = 0;
        slots[i].form = 0;
        if (ofsSlots[i] == 0)
        {
            continue;
        }
        memcpy(pkm, saveData + gbo + ofsSlots[i] + ofsPkm, pkmSize);
        pkx_decrypt(pkm, gen, gen != GEN_SIX);

        // verify occupied slot
        if ((gen == GEN_FOUR && pkx_is_valid(pkm, gen)) ||
            (gen != GEN_FOUR && saveData[ofsSlots[i]] == 1))
        {
            // fill pkx and EXP
            slots[i].species = pkx_get_value(pkm, gen, SPECIES);
            slots[i].form = pkx_get_value(pkm, gen, FORM);
            steps[i] = *(int *)(saveData + gbo + ofsSlots[i] + ofsExp);
        }
    }
    free(pkm);

    // query user new Daycare EXP values
    char expString[41] = {'\0'};
    char *labels[5] = {
        "Exit script",
        "Slot 1",
        "Slot 2",
        "Battle Resort\nSlot 1",
        "Battle Resort\nSlot 2"
    };
    unsigned int newExp;
    while (1)
    {
        i = gui_menu_6x5("Edit which slot's EXP?", numOpts, labels, slots, gen);
        if (i == 0)
        {
            break;
        }
        if (slots[i].species == 0)
        {
            gui_warn("Slot is not occupied.");
            continue;
        }

        sprintf(expString, "Input new experience\nCurrent: %i", steps[i]);
        gui_warn(expString);
        gui_numpad(&newExp, expString, 7);
        steps[i] = newExp;
        steps[0] += 1; // track changes
    }

    // store EXP back to save
    if (steps[0])
    {
        for (i = 0; i < 5; i++)
        {
            if (slots[i].species != 0)
            {
                *(int *)(saveData + gbo + ofsSlots[i] + ofsExp) = steps[i];
            }
        }
    }
    return 0;
}
