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
        case 44:
        case 45:
            configOffset = 0x92EB0306; //actually a key to a uint32
            break;
        default:
            if (version < 24) {
                gui_warn("Game not supported,\nbecause it has no instant speed option.");
            }
            else if (version > 45) {
                gui_warn("Game not supported,\nbecause it released after this script's latest update.");
            }
            else {
                gui_warn("Game not supported.");
            }
            return 1;
    }
    
    char *opts[5] = {
        "Cancel",
        "Slow",
        "Medium",
        "Fast",
        "Instant"
    };
    int choice = gui_menu_20x2("Pick a text speed option", 5, opts);
    if (choice) {
        sav_set_byte((sav_get_byte(configOffset, 0) & 0xFC) | (choice - 1), configOffset, 0);
    }

    return 0;
}
