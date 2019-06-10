#include <pksm.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);

    char *editTypes[] = {
        "Toggle bit",
        "Write 1 byte (unsigned char)",
        "Write 2 bytes (unsigned short)",
        "Write 4 bytes (unsigned int)",
        "Exit script"};
    char value[11] = {'\0'};
    char offsetStr[8] = {'\0'};
    int offset, bit;

    int type = gui_menu_20x2("Choose an edit type to perform", 7, editTypes);
    while (type < 4)
    {
        gui_keyboard(&offsetStr, "Offset to change (if hex prefix with 0x)", 8);
        offset = (unsigned int)strtol(offsetStr, NULL, 0);

        switch (type)
        {
            case 0:
                gui_numpad(&bit, "Which bit (0-7) should be toggled?", 1);
                saveData[offset] ^= (1 << bit);
                break;
            case 1:
                gui_keyboard(value, "Value to assign (if hex prefix with 0x)", 5);
                saveData[offset] = (unsigned char)strtol(value, NULL, 0);
                break;
            case 2:
                gui_keyboard(value, "Value to assign (if hex prefix with 0x)", 7);
                *(unsigned short *)(saveData + offset) = (unsigned short)strtol(value, NULL, 0);
                break;
            case 3:
                gui_keyboard(value, "Value to assign (if hex prefix with 0x)", 11);
                *(unsigned int *)(saveData + offset) = (unsigned int)strtol(value, NULL, 0);
                break;
            default:
                gui_warn("How did you get here?!", "");
                break;
        }

        type = gui_menu_20x2("Choose an edit type to perform", 7, editTypes);
    }

    return 0;
}
