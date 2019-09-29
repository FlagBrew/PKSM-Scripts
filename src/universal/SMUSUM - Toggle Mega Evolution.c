#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    unsigned char* saveData = (unsigned char*) argv[0];
    unsigned char version = *argv[2];
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

    if ((saveData[offset] & 0x01) == 0)
    {
        if (gui_choice("Mega evolution is locked.\nUnlock it?"))
        {
            saveData[offset] = (saveData[offset] ^ 0x01);
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
            saveData[offset] = (saveData[offset] ^ 0x01);
            gui_warn("Mega evolution successfully locked!");
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
