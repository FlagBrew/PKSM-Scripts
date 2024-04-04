#include <pksm.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *
 * A simple testing script for viewing stored PalPark Pokemon.
 * Author: FM1337
 *
 */

int getPalParkOffset(int version)
{

    // TODO: are these offsets the same across language varients and different versions?
    switch (version)
    {
    case 10: // D
    case 11: // P
        return 0xBA28;
    case 12: // PT
        return 0xC7F0;
    case 7: // HG
    case 8: // SS
        return 0xB3C0;
    default:
        return -1;
    }
}

void readMon(char *mon, int offset, int index)
{
    sav_get_data(mon, 236, sav_gbo(), offset + (236 * index));
    pkx_decrypt(mon, GEN_FOUR, 1);
}

int main(int argc, char **argv)
{

    struct pkx pals[6];

    char *labels[6] = {
        "Slot #1", "Slot #2", "Slot #3", "Slot #4", "Slot #5", "Slot #6"};

    int offset = getPalParkOffset(*argv[0]);

    if (offset == -1)
    {
        gui_warn("Sorry only generation 4 games are supported");
        return 0;
    }

    for (int i = 0; i < 6; i++)
    {
        char mon[236];

        readMon(mon, offset, i);

        if (pkx_get_value(mon, GEN_FOUR, SPECIES) == 0)
        {
            gui_warn("You have no PalPark PKNN");
            return 0;
        }

        pals[i].species = pkx_get_value(mon, GEN_FOUR, SPECIES);
    }

    gui_menu_6x5("Stored PalPark mons", 6, &labels[0], &pals[0], GEN_FOUR);

    return 0;
}