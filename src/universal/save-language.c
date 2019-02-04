#include <pksm.h>
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
            gui_warn("Changing language not supported", "for this game");
            return 1;
    }

    char *languages[9] = {"\u65e5\u672c\u8a9e", "English", "Fran\u00e7ais", "Italiano", "Deutsche", "Espa\u00f1ol", "\ud55c\uad6d\uc5b4", "\u4e2d\u6587 (\u7b80\u4f53)", "\u4e2d\u6587 (\u7e41\u9ad4)"};
    char choice = (char)gui_menu_20x2("Choose the language you want\nfor your save", version < 30 ? 7 : 9, &languages[0]);

    saveData[offset] = choice + (choice >= 6 ? 2 : 1);
    gui_warn("Save\'s language set to", languages[choice]);

    return 0;
}
