#include <pksm.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];

    unsigned int configOffset;
    switch (version)
    {
        case 24:
        case 25:
            configOffset = 0x16200;
            break;
        case 26:
        case 27:
            configOffset = 0x16C00;
            break;
        case 30:
        case 31:
            configOffset = 0x4400;
            break;
        case 32:
        case 33:
            configOffset = 0x4800;
            break;
        case 42:
        case 43:
            configOffset = 0x5600;
            break;
        default:
            gui_warn("Game not supported");
            return 1;
    }

    if (!gui_choice("Would you like your in-game text speed instant?"))
    {
        return 1;
    }

    /* set the game save config's first byte's smallest bits to 11 for instant text */
    sav_set_byte(sav_get_byte(configOffset, 0) | 3, configOffset, 0);

    return 0;
}
