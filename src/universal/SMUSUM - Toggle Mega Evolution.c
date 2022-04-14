#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    unsigned char version = *argv[0];
    int offset;

    switch (version)
    {
        case 30:
        case 31:
            offset = 0x1278;
            break;
        case 32:
        case 33:
            offset = 0x1478;
            break;
        default:
            gui_warn("Mega evolution unlock not\nsupported for this game");
            return 1;
    }

    char currentVal = sav_get_byte(offset, 0);
    if ((currentVal & 0x01) == 0)
    {
        if (gui_choice("Mega evolution is locked.\nUnlock it?"))
        {
            sav_set_byte(currentVal ^ 0x01, offset, 0);
            gui_warn("Mega evolution successfully unlocked!");
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (gui_choice("Mega evolution is unlocked.\nLock it?"))
        {
            sav_set_byte(currentVal ^ 0x01, offset, 0);
            gui_warn("Mega evolution successfully locked!");
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
