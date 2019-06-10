#include <pksm.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    char *editTypes[5] = {
        "Toggle bit",
        "Write 1 byte (char)",
        "Write 2 bytes (short)",
        "Write 4 bytes (int)",
        "Exit script"};
    char inputStr[11] = {'\0'};
    int offset, bit, lastOfs[4] = { atoi(argv[1]), atoi(argv[1]), atoi(argv[1]) - 2, atoi(argv[1]) - 4 };

    int type = gui_menu_20x2("Choose an edit type to perform", 5, editTypes);
    while (type < 4)
    {
        gui_keyboard(inputStr, "Offset to change (if hex prefix with 0x)", 8);
        offset = (int)strtol(inputStr, NULL, 0);

        if (offset >= lastOfs[type] || offset < 0)
        {
            gui_warn("Offset out of range", "to make this type of edit");
        }
        else
        {
            switch (type)
            {
                case 0:
                    gui_numpad(&bit, "Which bit (0-7) should be toggled?", 1);
                    saveData[offset] ^= (1 << bit);
                    break;
                case 1:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 5);
                    saveData[offset] = (char)strtol(inputStr, NULL, 0);
                    break;
                case 2:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 7);
                    *(short *)(saveData + offset) = (short)strtol(inputStr, NULL, 0);
                    break;
                case 3:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 11);
                    *(int *)(saveData + offset) = (int)strtol(inputStr, NULL, 0);
                    break;
                default:
                    gui_warn("How did you get here?!", "");
                    break;
            }
        }

        type = gui_menu_20x2("Choose an edit type to perform", 5, editTypes);
    }

    return 0;
}
