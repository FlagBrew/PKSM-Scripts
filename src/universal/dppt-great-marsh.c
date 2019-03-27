#include <pksm.h>   /* virtual header, required */
#include <unistd.h> /* ? */
#include <stdlib.h> /* General utilities: memory management, program utilities, string conversions, random numbers */

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int offset, optStart = 0, count;
    char *labelPool[15] = {'\0'};
    struct pkx pkmPool[15];
    int i;

    switch (version)
    {
    case 10: // Diamond
    case 11: // Pearl
        offset = 0x72d0 + sav_gbo();
        int poolDP[] = {
            46, 55, 102, 115, 193, 285, 315, 316,
            397, 451, 452, 453, 454, 455};
        count = 14;
        for (i = 0; i < count; i++)
        {
            pkmPool[i].species = poolDP[i];
            pkmPool[i].form = 0;
            labelPool[i] = i18n_species(poolDP[i]);
        }
        break;
    case 12: // Platinum
        offset = 0x7f24 + sav_gbo();
        optStart = 32;
        int poolPT[] = {
            46, 102, 114, 115, 193, 195, 285, 316,
            352, 357, 451, 452, 453, 454, 455};
        count = 15;
        for (i = 0; i < count; i++)
        {
            pkmPool[i].species = poolPT[i];
            pkmPool[i].form = 0;
            labelPool[i] = i18n_species(poolPT[i]);
        }
        break;
    default:
        gui_warn("This script doesn't work", "on this game.");
        return 1;
    }

    /*
    A number of slots change when the player receives
    the National Dex. This keyNumbers list is only
    applicable to post-National Dex save files
    */
    int keyNumbers[64] = {
        // DP
        453, 451, 455, 453, 451, 455, 55, 453,
        451, 455, 315, 397, 454, 452, 102, 55,
        397, 453, 451, 455, 193, 285, 46, 115,
        316, 315, 397, 453, 451, 455, 315, 55,

        // Pt
        454, 352, 352, 455, 451, 453, 195, 452,
        451, 453, 195, 115, 46, 452, 102, 102,
        451, 453, 451, 455, 193, 285, 46, 115,
        316, 357, 316, 285, 451, 455, 453, 114};
    struct pkx pkmAreas[7];
    char *labelAreas[] = {
        "Area 1",
        "Area 2",
        "Area 3",
        "Area 4",
        "Area 5",
        "Area 6",
        "Exit script",
    };

    int marsh = *(int *)(saveData + offset);
    int slot;
    for (slot = 0; slot < 6; slot++)
    {
        pkmAreas[slot].species = keyNumbers[((marsh >> slot * 5) & 31) + optStart];
        pkmAreas[slot].form = 0;
    }
    pkmAreas[6].species = 0;
    pkmAreas[6].form = 0;

    gui_warn("Some displayed options require", "National Dex to appear");

    do
    {
        slot = gui_menu_6x5("Edit which Great Marsh area?", 7, labelAreas, pkmAreas, GEN_FOUR);

        if (slot < 6)
        {
            marsh = marsh & ~(31 << slot * 5);
            int choice = gui_menu_6x5("Who should be the\ndaily (binocular) Pokemon\nfor this area?", count, labelPool, pkmPool, GEN_FOUR);

            int spec = pkmPool[choice].species;
            for (i = 0; i < 32; i++)
            {
                if (keyNumbers[optStart + i] == spec)
                {
                    break;
                }
            }

            pkmAreas[slot].species = spec;
            marsh = marsh | (i << slot * 5);
            *(int *)(saveData + offset) = marsh;
        }
    } while (slot < 6);

    return 0;
}
