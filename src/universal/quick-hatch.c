#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int friend, remaining = 0;
    enum Generation gen;

    switch (version)
    {
        case 39: // VC Gold
        case 40: // VC Silver
        case 41: // VC Crystal
            gen = GEN_TWO;
            remaining = 1;
            friend = 0x1e;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            gen = GEN_THREE;
            friend = 0x29;
            break;
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen = GEN_FOUR;
            friend = 0x14;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen = GEN_FIVE;
            friend = 0x14;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen = GEN_SIX;
            friend = 0xca; // OT Friendship controls egg cycles
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            gen = GEN_SEVEN;
            friend = 0xca; // OT Friendship controls egg cycles
            break;
        case 44:
        case 45:
            gen = GEN_EIGHT;
            friend = 0x112; // OT Friendship controls egg cycles
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    int slots = sav_get_max(MAX_SLOTS), slot,
        boxEggs = 0, partyEggs = 0, slotsPerBox = slots / sav_get_max(MAX_BOXES);
    char isEgg;
    char *pkm = malloc(pkx_party_size(gen));

    sav_box_decrypt();
    for (slot = 0; slot < slots; slot++)
    {
        sav_get_pkx(pkm, slot / slotsPerBox, slot % slotsPerBox);
        if (pkx_is_valid(pkm, gen) && pkx_get_value(pkm, gen, EGG))
        {
            boxEggs++;
            pkm[friend] = remaining;
            sav_inject_pkx(pkm, gen, slot / slotsPerBox, slot % slotsPerBox, 0);
        }
    }
    sav_box_encrypt();
    if (boxEggs > 0)
    {
        gui_warn("All eggs in PC set to hatch\nas soon as possible.");
    }

    for (slot = 0; slot < 6; slot++)
    {
        party_get_pkx(pkm, slot);
        if (pkx_is_valid(pkm, gen) && pkx_get_value(pkm, gen, EGG))
        {
            partyEggs++;
            pkm[friend] = remaining;
            party_inject_pkx(pkm, gen, slot);
        }
    }
    if (partyEggs > 0)
    {
        gui_warn("All eggs in party set to\nhatch as soon as possible.");
    }

    if (boxEggs + partyEggs == 0)
    {
        gui_warn("No eggs found in save.");
    }
    free(pkm);
    return 0;
}
