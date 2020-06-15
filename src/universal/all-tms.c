#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int block = 0, ofs = 0;
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
        1230, // last SWSH TM
        1130, 1131, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, // SWSH TRs
        1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148, 1149,
        1150, 1151, 1152, 1153, 1154, 1155, 1156, 1157, 1158, 1159,
        1160, 1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169,
        1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178, 1179,
        1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189,
        1190, 1191, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199,
        1200, 1201, 1202, 1203, 1204, 1205, 1206, 1207, 1208, 1209,
        1210, 1211, 1212, 1213, 1214, 1215, 1216, 1217, 1218, 1219,
        1220, 1221, 1222, 1223, 1224, 1225, 1226, 1227, 1228, 1229
    };
    int tmCount = 100;
    int hmCount = 8;
    unsigned int quant = 1;
    unsigned short foundHMs[8] = {0};

    switch (version)
    {
        case 1:
        case 2:
            tmCount = 50;
            ofs = 0x640;
            gui_numpad(&quant, "How many of each TM?", 2);
            break;
        case 3:
            tmCount = 50;
            ofs = 0x690;
            gui_numpad(&quant, "How many of each TM?", 2);
            break;
        case 4:
        case 5:
            tmCount = 50;
            ofs = 0x464;
            gui_numpad(&quant, "How many of each TM?", 2);
            break;
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
            tmCount = gui_choice("Exclude unreleased TM95 Snarl?") ? 94 : 95;
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
        case 44:
        case 45:
            block = 0x1177c2c4;
            tmCount = 99;
            ofs = 0xb90;
            gui_numpad(&quant, "How many of each TR?", 3);
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    int i, j, k = 0;
    for(i = 0; i < tmCount; i++)
    {
        if (version < 30) {
            unsigned short item = sav_get_short(block, ofs + i * 4);
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
            sav_set_short(tms[i], 0, ofs + i * 4);
            sav_set_short(quant, 0, ofs + i * 4 + 2);
        }
        else if (version >= 42)
        {
            sav_set_int((1 << 15) + tms[i], block, ofs + i * 4);
        }
        else
        {
            sav_set_int((1 << 10) + tms[i], ofs, i * 4);
        }
    }
    if (k > 0) {
        ofs += tmCount * 4;
        for (i = 0; i < k; i++)
        {
            sav_set_short(foundHMs[i], 0, ofs + i * 4);
            sav_set_short(1, 0, ofs + i * 4 + 2);
        }
    }
    // add SWSH TRs
    if (version == 44 || version == 45)
    {
        for (i = 99; i < 200; i++)
        {
            sav_set_int((quant << 15) + tms[i + 1], block, ofs + i * 4);
        }
    }
    gui_warn("All TMs placed in pouch.");

    return 0;
}
