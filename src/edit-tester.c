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
    int offset, lastOfs[4] = { atoi(argv[1]), atoi(argv[1]), atoi(argv[1]) - 2, atoi(argv[1]) - 4 };
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
