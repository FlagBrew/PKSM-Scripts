#include <pksm.h> // PKSM provided virtual header giving access to scripting API
#include <stdlib.h>

int main(int argc, char **argv)
{
    int version = *argv[0], ofs, species, block = sav_gbo();
    switch (version)
    {
        case 1: case 2:
        case 3:
        case 4: case 5:
            ofs = 0x18 + 0x10; // PokeDex = BlockOfs[0] + 0x18
            species = 386;
            break;
        case 10: case 11:
            ofs = 0x12e0;
            species = 493;
            break;
        case 12:
            ofs = 0x132c;
            species = 493;
            break;
        case 7: case 8:
            ofs = 0x12bc;
            species = 493;
            break;
        case 20: case 21:
            ofs = 0x21608;
            species = 649;
            break;
        case 22: case 23:
            ofs = 0x21408;
            species = 649;
            break;
        case 24: case 25:
        case 26: case 27:
            ofs = 0x15008;
            species = 721;
            break;
        case 30: case 31:
            ofs = 0x2a88;
            species = 802;
            break;
        case 32: case 33:
            ofs = 0x2c88;
            species = 807;
            break;
        case 42: case 43:
            ofs = 0x2a00;
            species = 153;
            break;
        default:
            gui_warn("This script does not yet\nsupport this game.");
            return 0;
    }

    int bytes = species / 8, i;
    for (i = 0; i < bytes; i++)
    {
        sav_set_byte(0, block, ofs + i);
    }
    for (i = bytes * 8; i < species; i++)
    {
        sav_set_bit(0, block, ofs + i / 8, i & 7);
    }

    if (version == 24 || version == 25)
    {
        ofs = 0x1564c;
        for (i = 0; i < bytes; i++)
        {
            sav_set_byte(0, block, ofs + i);
        }
        for (i = bytes * 8; i < species; i++)
        {
            sav_set_bit(0, block, ofs + i / 8, i & 7);
        }
    }

    gui_warn("Owned flags in save's Pokédex have been cleared.");

    return 0;
}
