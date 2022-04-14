#include <pksm.h>
#include <stdlib.h>

void set_flag(unsigned short index, unsigned char version)
{
    int block;
    int flagsOffset = 0;
    
    switch(version)
    {
        case 1:
        case 2:
            block = 2;
            flagsOffset = 0x2A0;
            break;
        case 3:
            block = 2;
            flagsOffset = 0x2F0;
            break;
        case 4:
        case 5:
            if (index >= 0x500)
            {
                block = 2;
                index -= 0x500;
            } 
            else 
            {
                block = 1;
                flagsOffset = 0xEE0;
            }
            break;
    }
    
    sav_set_bit(1, block, flagsOffset + index / 8, index & 7);
}

void warn_bag_full(void)
{
    gui_warn("There is no key item space left.\nThe items won't be injected.");
    gui_warn("However, you can still use this\nscript to toggle the required flags.");
}

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    
    unsigned int keyItemsOffset;
    unsigned int key = 0;
    unsigned char n_opts, injected;
    unsigned int keyItemsSize = 120;
    
    switch (version)
    {
        case 1:
        case 2:
            keyItemsOffset = 0x05B0;
            //key doesn't exist, and xor 0 is an identity
            n_opts = 2;
            injected = 14;
            keyItemsSize = 80;
            break;
        case 3:
            keyItemsOffset = 0x05D8;
            key = sav_get_int(0, 0xAC);
            n_opts = 5;
            injected = 0;
            break;
        case 4:
        case 5:
            keyItemsOffset = 0x03B8;
            key = sav_get_int(0, 0xAF8);
            n_opts = 3;
            injected = 12;
            break;
        default:
            gui_warn("This script only works on\nGen III games.");
            return 1;
    }
    
    unsigned int offs = 0;
    unsigned short item;
    unsigned char owned = 0;
    do
    {
        item = sav_get_short(1, keyItemsOffset + offs);
        if(item == 0x113)
            owned |= version < 3 ? 1 : 8;
        if(item == 0x173)
            owned |= 1;
        if(item == 0x172)
            owned |= 2;
        if(item == 0x178)
            owned |= 4;
        offs += 4;
        if(offs >= keyItemsSize)
        {
            warn_bag_full();
        }
    } while(item && offs < keyItemsSize);
    
    char *opts[5] = {
        "Exit script",
        "AuroraTicket",
        "MysticTicket",
        "Old Sea Map",
        "Eon Ticket"
    };
    if (version < 3)
        opts[1] = "Eon Ticket";
    int inject_another;
    do
    {
        int choice = gui_menu_20x2("Select the ticket\nyou want to inject", n_opts, opts);
        switch(choice)
        {
            case 0:
                return 0;
            case 1: //Eon Ticket RS, AuroraTicket FrLgE
                if(!(owned & 1) && offs < keyItemsSize)
                {
                    sav_set_short(version < 3 ? 0x113 : 0x173, 1, keyItemsOffset + offs);
                    sav_set_short(1 ^ (key & 0xFFFF), 1, keyItemsOffset + offs + 2);
                    owned |= 1;
                    offs += 4;
                }
                if (version < 3)
                    set_flag(0x853, version);
                else {
                    set_flag(version == 3 ? 0x13A : 0x2A7, version);
                    set_flag(version == 3 ? 0x8D5 : 0x84B, version);
                }
                injected |= 1;
                break;
            case 2: //MysticTicket
                if(!(owned & 2) && offs < keyItemsSize)
                {
                    sav_set_short(0x172, 1, keyItemsOffset + offs);
                    sav_set_short(1 ^ (key & 0xFFFF), 1, keyItemsOffset + offs + 2);
                    owned |= 2;
                    offs += 4;
                }
                set_flag(version == 3 ? 0x13B : 0x2A8, version);
                set_flag(version == 3 ? 0x8E0 : 0x84A, version);
                injected |= 2;
                break;
            case 3: //Old Sea Map
                if(!(owned & 4) && offs < keyItemsSize)
                {
                    sav_set_short(0x178, 1, keyItemsOffset + offs);
                    sav_set_short(1 ^ (key & 0xFFFF), 1, keyItemsOffset + offs + 2);
                    owned |= 4;
                    offs += 4;
                }
                set_flag(0x13C, version);
                set_flag(0x8D6, version);
                injected |= 4;
                break;
            case 4: //Eon Ticket E
                if(!(owned & 8) && offs < keyItemsSize)
                {
                    sav_set_short(0x113, 1, keyItemsOffset + offs);
                    sav_set_short(1 ^ (key & 0xFFFF), 1, keyItemsOffset + offs + 2);
                    owned |= 8;
                    offs += 4;
                }
                set_flag(0x8B3, version);
                injected |= 8;
                break;
            default:
                break;
        }
        if(offs >= keyItemsSize)
            warn_bag_full();
        if(injected ^ 15)
            inject_another = gui_choice("Would you like to\ninject another ticket?");
        else 
            inject_another = 0;
    } while(inject_another);
    return 0;
}
