#include <pksm.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char version = *argv[0];
    
    unsigned int key = 0;
    unsigned int moneyOffset;
    
    switch(version)
    {
        case 3:
            key = sav_get_int(0, 0xAC); //RS and E have the money stored at the same place, but you only need the security key in E
        case 1:
        case 2:
            moneyOffset = 0x490;
            break;
        case 4:
        case 5:
            key = sav_get_int(0, 0xAF8);
            moneyOffset = 0x290;
            break;
        default:
            gui_warn("This script only works\non a gen 3 game");
            return 1;
    }
    
    unsigned int amount;
    gui_numpad(&amount, "How much money do you want?\n Max : 999999", 6);
    sav_set_int(amount ^ key, 1, moneyOffset);
    return 0;
}
