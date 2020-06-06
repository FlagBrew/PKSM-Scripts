#include <pksm.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *editTypes[5] = {
        "Toggle bit",
        "Write 1 byte (char)",
        "Write 2 bytes (short)",
        "Write 4 bytes (int)",
        "Exit script"};
    char inputStr[11] = {'\0'};
    int offset, lastOfs[4];
    switch (*argv[0])
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            lastOfs[0] = 0x20000 - 1;
            lastOfs[1] = 0x20000 - 1;
            lastOfs[2] = 0x20000 - 2;
            lastOfs[3] = 0x20000 - 4;
            break;
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
        case 20:
        case 21:
        case 22:
        case 23:
            lastOfs[0] =0x80000 - 1;
            lastOfs[1] =0x80000 - 1;
            lastOfs[2] =0x80000 - 2;
            lastOfs[3] =0x80000 - 4;
            break;
        case 24:
        case 25:
            lastOfs[0] =0x65600 - 1;
            lastOfs[1] =0x65600 - 1;
            lastOfs[2] =0x65600 - 2;
            lastOfs[3] =0x65600 - 4;
            break;
        case 26:
        case 27:
            lastOfs[0] =0x76000 - 1;
            lastOfs[1] =0x76000 - 1;
            lastOfs[2] =0x76000 - 2;
            lastOfs[3] =0x76000 - 4;
            break;
        case 30:
        case 31:
            lastOfs[0] =0x6BE00 - 1;
            lastOfs[1] =0x6BE00 - 1;
            lastOfs[2] =0x6BE00 - 2;
            lastOfs[3] =0x6BE00 - 4;
            break;
        case 32:
        case 33:
            lastOfs[0] =0x6CC00 - 1;
            lastOfs[1] =0x6CC00 - 1;
            lastOfs[2] =0x6CC00 - 2;
            lastOfs[3] =0x6CC00 - 4;
            break;
        case 42:
        case 43:
            lastOfs[0] =0x100000 - 1;
            lastOfs[1] =0x100000 - 1;
            lastOfs[2] =0x100000 - 2;
            lastOfs[3] =0x100000 - 4;
            break;
        case 44:
        case 45:
            lastOfs[0] =0x17195E - 1;
            lastOfs[1] =0x17195E - 1;
            lastOfs[2] =0x17195E - 2;
            lastOfs[3] =0x17195E - 4;
            break;
        default:
            gui_warn("This script does not work with this game")
            return 1;
    }
    unsigned int bit;

    int type = gui_menu_20x2("Choose an edit type to perform", 5, editTypes);
    while (type < 4)
    {
        gui_keyboard(inputStr, "Offset to change (if hex prefix with 0x)", 8);
        offset = (int)strtol(inputStr, NULL, 0);

        if (offset >= lastOfs[type] || offset < 0)
        {
            gui_warn("Offset out of range\nto make this type of edit");
        }
        else
        {
            switch (type)
            {
                case 0:
                    gui_numpad(&bit, "Which bit (0-7) should be toggled?", 1);
                    sav_set_byte(sav_get_byte(offset, 0) ^ (1 << bit), offset, 0);
                    break;
                case 1:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 5);
                    sav_set_byte((char)strtol(inputStr, NULL, 0), offset, 0);
                    break;
                case 2:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 7);
                    sav_set_short(strtol(inputStr, NULL, 0), offset, 0);
                    break;
                case 3:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 11);
                    sav_set_int(strtol(inputStr, NULL, 0), offset, 0);
                    break;
                default:
                    gui_warn("How did you get here?!");
                    break;
            }
        }

        type = gui_menu_20x2("Choose an edit type to perform", 5, editTypes);
    }

    return 0;
}
