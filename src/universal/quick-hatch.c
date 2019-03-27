#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int boxes, egg, friend;
    enum Generation gen;

    switch (version)
    {
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen = GEN_FOUR;
            boxes = 18;
            egg = 0x3b;
            friend = 0x14;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen = GEN_FIVE;
            boxes = 24;
            egg = 0x3b;
            friend = 0x14;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen = GEN_SIX;
            boxes = 31;
            egg = 0x77;
            friend = 0xca; // OT Friendship controls egg cycles
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            gen = GEN_SEVEN;
            boxes = 32;
            egg = 0x77;
            friend = 0xca; // OT Friendship controls egg cycles
            break;
        default:
            gui_warn("This script doesn't work", "on this game.");
            return 1;
    }

    int box, slot, ofs, boxEggs = 0, partyEggs = 0;
    unsigned short species;
    char isEgg;
    char *pkm = malloc(260);

    sav_box_decrypt();
    for (box = 0; box < boxes; box++)
    {
        for (slot = 0; slot < 30; slot++)
        {
            sav_get_pkx(pkm, box, slot);
            species = *(unsigned short *)(pkm + 0x08);
            if (species > 0)
            {
                isEgg = (pkm[egg] >> 6) & 0x1;
                if (isEgg)
                {
                    boxEggs++;
                    pkm[friend] = 0;
                    sav_inject_pkx(pkm, gen, box, slot);
                }
            }
        }
    }
    sav_box_encrypt();
    if (boxEggs > 0)
    {
        gui_warn("All eggs in PC set to hatch", "as soon as possible.");
    }

    for (slot = 0; slot < 6; slot++)
    {
        party_get_pkx(pkm, slot);
        species = *(unsigned short *)(pkm + 0x08);
        if (species > 0)
        {
            isEgg = (pkm[egg] >> 6) & 0x1;
            if (isEgg)
            {
                partyEggs++;
                pkm[friend] = 0;
                party_inject_pkx(pkm, gen, slot);
            }
        }
    }
    if (partyEggs > 0)
    {
        gui_warn("All eggs in party set to", "hatch as soon as possible.");
    }

    if (boxEggs + partyEggs == 0)
    {
        gui_warn("No eggs found in save.", "");
    }
    free(pkm);
    return 0;
}
