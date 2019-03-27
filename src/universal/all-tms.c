#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int ofs = 0;
    unsigned short hms[8] = {420, 421, 422, 423, 424, 425, 426, 427};
    int tms[100] = {
        328, 329, 330, 331, 332, 333, 334, 335, 336, 337,
        338, 339, 340, 341, 342, 343, 344, 345, 346, 347,
        348, 349, 350, 351, 352, 353, 354, 355, 356, 357,
        358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
        368, 369, 370, 371, 372, 373, 374, 375, 376, 377,
        378, 379, 380, 381, 382, 383, 384, 385, 386, 387,
        388, 389, 390, 391, 392, 393, 394, 395, 396, 397,
        398, 399, 400, 401, 402, 403, 404, 405, 406, 407,
        408, 409, 410, 411, 412, 413, 414, 415, 416, 417,
        418, 419, 618, 619, 620, 690, 691, 692, 693, 694
    };
    int tmCount = 100;
    int hmCount = 8;
    int quant = 1;
    unsigned short foundHMs[8] = {0};

    switch (version)
    {
        case 7:
        case 8:
            ofs += 0x14;
            // intentional fallthrough
        case 12:
            ofs += 0xc;
            // intentional fallthrough
        case 10:
        case 11:
            tmCount = 92;
            ofs += sav_gbo() + 0x980;
            gui_numpad(&quant, "How many of each TM?", 2);
            break;
        case 20:
        case 21:
            tmCount = gui_choice("Exclude unreleased TM95 Snarl?", "") ? 94 : 95;
            hmCount = 6;
            ofs = 0x18a24;
            break;
        case 22:
        case 23:
            tmCount = 95;
            hmCount = 6;
            ofs = 0x18a24;
            break;
        case 24: // X
        case 25: // Y
            hmCount = 5;
            ofs = 0xbc0;
            break;
        case 26:
        case 27:
            hmCount = 7;
            hms[6] = 737;
            ofs = 0xbc0;
            break;
        case 30:
        case 31:
            ofs = 0x998;
            break;
        case 32:
        case 33:
            ofs = 0x9c4;
            break;
        case 42:
        case 43:
            tmCount = 60;
            ofs = 0xf0;
            break;
        default:
            gui_warn("This script doesn't work", "on this game.");
            return 1;
    }

    int i, j, k = 0;
    for(i = 0; i < tmCount; i++)
    {
        if (version < 30) {
            unsigned short item = *(unsigned short *)(saveData + ofs + i * 4);
            if (item != 0) {
                for (j = 0; j < hmCount; j++)
                {
                    if (item == hms[j]) {
                        foundHMs[k] = item;
                        k++;
                        break;
                    }
                }
            }
            *(unsigned short *)(saveData + ofs + i * 4) = (unsigned short)tms[i];
            *(unsigned short *)(saveData + ofs + i * 4 + 2) = (unsigned short)quant;
        }
        else if (version == 42 || version == 43)
        {
            *(int *)(saveData + ofs + i * 4) = (1 << 15) + tms[i];
        }
        else
        {
            *(int *)(saveData + ofs + i * 4) = (1 << 10) + tms[i];
        }
    }
    if (k > 0) {
        ofs += tmCount * 4;
        for (i = 0; i < k; i++)
        {
            *(unsigned short *)(saveData + ofs + i * 4) = foundHMs[i];
            *(unsigned short *)(saveData + ofs + i * 4 + 2) = 1;
        }
    }
    gui_warn("All TMs placed in pouch.", "");

    return 0;
}
