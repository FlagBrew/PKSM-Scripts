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
    int block = 0, offset, lastOfs[4];
    enum Generation gen;
    switch (*argv[0])
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            gen = GEN_THREE;
            block = -1;  // assume absolute offset
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
            gen = version < 20 ? GEN_FOUR : GEN_FIVE;
            lastOfs[0] = 0x80000 - 1;
            lastOfs[1] = 0x80000 - 1;
            lastOfs[2] = 0x80000 - 2;
            lastOfs[3] = 0x80000 - 4;
            break;
        case 24:
        case 25:
            gen = GEN_SIX;
            lastOfs[0] = 0x65600 - 1;
            lastOfs[1] = 0x65600 - 1;
            lastOfs[2] = 0x65600 - 2;
            lastOfs[3] = 0x65600 - 4;
            break;
        case 26:
        case 27:
            gen = GEN_SIX;
            lastOfs[0] = 0x76000 - 1;
            lastOfs[1] = 0x76000 - 1;
            lastOfs[2] = 0x76000 - 2;
            lastOfs[3] = 0x76000 - 4;
            break;
        case 30:
        case 31:
            gen = GEN_SEVEN;
            lastOfs[0] = 0x6BE00 - 1;
            lastOfs[1] = 0x6BE00 - 1;
            lastOfs[2] = 0x6BE00 - 2;
            lastOfs[3] = 0x6BE00 - 4;
            break;
        case 32:
        case 33:
            gen = GEN_SEVEN;
            lastOfs[0] = 0x6CC00 - 1;
            lastOfs[1] = 0x6CC00 - 1;
            lastOfs[2] = 0x6CC00 - 2;
            lastOfs[3] = 0x6CC00 - 4;
            break;
        case 42:
        case 43:
            gen = GEN_LGPE;
            lastOfs[0] = 0x100000 - 1;
            lastOfs[1] = 0x100000 - 1;
            lastOfs[2] = 0x100000 - 2;
            lastOfs[3] = 0x100000 - 4;
            break;
        case 44:
        case 45:
            gen = GEN_EIGHT;
            lastOfs[0] = 0x17195E - 1;
            lastOfs[1] = 0x17195E - 1;
            lastOfs[2] = 0x17195E - 2;
            lastOfs[3] = 0x17195E - 4;
            break;
        default:
            gui_warn("This script does not work with this game");
            return 1;
    }
    unsigned int bit;

    // Game-specific block related variables
    // Gen 4
    int dp[2] = {0xC100, 0x20000},
        pt[2] = {0xCF2C, 0x20000},
        hgss[2] = {0xF700, 0x23000};
    int *g4;
    if (gen == GEN_FOUR)
    {
        g4 = version == 12 ? pt : (version < 10 ? hgss : dp);
    }
    // SwSh
    char *swshBlocks[13] = {
        "Box",
        "WondercardData",
        "Party",
        "PokeDex",
        "ArmorDex",
        "CrownDex",
        "Items",
        "BoxLayout",
        "Misc",
        "TrainerCard",
        "PlayTime",
        "Status",
        "Custom..."
    };
    int swshKeys[13] = {
        0x0d66012c,
        0x112d5141,
        0x2985fe5d,
        0x4716c404,
        0x3F936BA9,
        0x3C9366F0,
        0x1177c2c4,
        0x19722c89,
        0x1b882b09,
        0x874da6fa,
        0x8cbbfd90,
        0xf25c070e,
        0
    };

    int type = gui_menu_20x2("Choose an edit type to perform", 5, editTypes);
    while (type < 4)
    {
        // SwSh block selection
        if (gen == GEN_EIGHT)
        {
            block = swshKeys[gui_menu_20x2("Which block do you\nwant to edit?", 13, swshBlocks)];
            if (block == 12)
            {
                gui_keyboard(inputStr, "Key of block to edit, in hex", 11);
                block = (int)strtol(inputStr, NULL, 0);
            }
        }
        gui_keyboard(inputStr, "Offset to change (if hex, prefix with 0x)", 8);
        offset = (int)strtol(inputStr, NULL, 0);

        if (offset >= lastOfs[type] || offset < 0)
        {
            gui_warn("Offset out of range\nto make this type of edit");
        }
        else
        {
            // account for variable Gen 4 block offsets
            if (gen == GEN_FOUR)
            {
                offset %= 0x40000;
                block = offset < g4[0] ? sav_gbo() : (offset < g4[1] ? sav_sbo() : 0);
            }

            switch (type)
            {
                case 0:
                    gui_numpad(&bit, "Which bit (0-7) should be toggled?", 1);
                    sav_set_byte(sav_get_byte(offset, 0) ^ (1 << bit), block, offset);
                    break;
                case 1:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 5);
                    sav_set_byte((char)strtol(inputStr, NULL, 0), block, offset);
                    break;
                case 2:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 7);
                    sav_set_short(strtol(inputStr, NULL, 0), block, offset);
                    break;
                case 3:
                    gui_keyboard(inputStr, "Value to assign (if hex prefix with 0x)", 11);
                    sav_set_int(strtol(inputStr, NULL, 0), block, offset);
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
