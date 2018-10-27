#include <picoc_unix.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned char* saveData = (unsigned char*) atoi(argv[0]);
    unsigned char version = *argv[2];
    int offset;

    switch (version)
    {
        case 24:
        case 25:
        case 26:
        case 27:
            offset = 0x1402D;
            break;
        case 30:
        case 31:
            offset = 0x1235;
            break;
        case 32:
        case 33:
            offset = 0x1435;
            break;
        default:
            gui_warn("DS games cannot change language", "");
            return 1;
    }

    char *languages[9] = {"Japanese", "English", "French", "Italian", "German", "Spanish", "Korean", "Simplified Chinese", "Traditional Chinese"};
    char choice = (char)gui_menu20x2("Choose the language you want\nfor your save", version < 30 ? 7 : 9, &languages[0]);

    saveData[offset] = choice + 1;
    gui_warn("Save\'s language set to", languages[choice]);

    return 0;
}
