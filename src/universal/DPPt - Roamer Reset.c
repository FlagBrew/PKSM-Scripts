#include <pksm.h>
#include <stdio.h> /* sprintf */

/* Mesprit and Cresselia are the two roamers shared by DP and Pt. Each one is
   tracked by three things in the general block:
     - a "disappeared" event flag, set once the roamer leaves its home spot
     - a status work value: 0 = pending, 1 = caught, 2 = fainted/can respawn
     - a 0x14 byte roamer struct holding the generated PID, IVs, level, etc.
   Putting the flag back to 0, the status back to pending and wiping the struct
   returns the encounter to its pre-battle state, so the roamer is standing at
   Verity Cavern / Fullmoon Island again on the next visit. */

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int flagOffset[3], flagBit[3], workOffset[3], roamerOffset[3];
    struct pkx options[3];
    int species[3] = {0, 481, 488};
    char *labels[3] = {"Exit script", "Mesprit", "Cresselia"};
    char blank[20];
    char message[96];
    int gbo = sav_gbo(), i, choice;

    switch (version)
    {
        case 10:
        case 11:
            /* flag 509 (Mesprit), flag 621 (Cresselia) */
            flagOffset[1] = 0x101B;
            flagBit[1] = 5;
            flagOffset[2] = 0x1029;
            flagBit[2] = 5;
            /* work 89 (Mesprit), work 88 (Cresselia) */
            workOffset[1] = 0xE4E;
            workOffset[2] = 0xE4C;
            roamerOffset[1] = 0x73A0;
            roamerOffset[2] = 0x73B4;
            break;
        case 12:
            /* flag 479 (Mesprit), flag 591 (Cresselia) */
            flagOffset[1] = 0x1027;
            flagBit[1] = 7;
            flagOffset[2] = 0x1035;
            flagBit[2] = 7;
            /* work 89 (Mesprit), work 88 (Cresselia) */
            workOffset[1] = 0xE5E;
            workOffset[2] = 0xE5C;
            roamerOffset[1] = 0x7FF4;
            roamerOffset[2] = 0x8008;
            break;
        default:
            gui_warn("This script is only meant for\nthe Sinnoh games (DPPt)");
            return 1;
    }

    for (i = 0; i < 20; i++)
    {
        blank[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        options[i].species = species[i];
        options[i].form = 0;
    }

    choice = gui_menu_6x5("Which roamer do you want to reset?", 3, labels, options, GEN_FOUR);
    if (choice < 1 || choice > 2)
    {
        return 0;
    }

    sav_set_bit(0, gbo, flagOffset[choice], flagBit[choice]);
    sav_set_short(0, gbo, workOffset[choice]);
    sav_set_data(blank, 20, gbo, roamerOffset[choice]);

    sprintf(message, "%s can be encountered again\nat its original location.", labels[choice]);
    gui_warn(message);
    return 0;
}
