#include <pksm.h>
#include <stdlib.h>

// This data is derived from PKHeX as of 11/29/2020

char xy[108] = {
    0xFE, 0xFF, 0xFF, 0x7E, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFB, 0xFF, 0xF7, 0xFF, 0xFF,
    0xF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0, 0xFE, 0xFF, 0xFF, 0x7E,
    0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF,
    0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFB, 0xFF, 0xF7, 0xFF, 0xFF, 0xF, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
char sm_f[142] = {
    1, 34, 0, 24, 1, 12, 0, 56, 1, 35, 0, 32, 1, 20, 0, 32, 1, 11, 3, 1, 1, 12, 0, 24,
    1, 11, 0, 24, 1, 13, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 11, 0, 24,
    1, 13, 0, 24, 1, 34, 0, 24, 1, 11, 0, 24, 1, 1, 0, 5, 1, 24, 0, 24, 1, 28, 0, 24,
    1, 17, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 11, 0, 24, 1, 1, 0, 55, 3, 1, 1, 12,
    0, 24, 1, 17, 0, 24, 1, 24, 0, 56, 3, 1, 1, 14, 0, 24, 1, 22, 0, 24, 1, 22, 0, 24,
    1, 12, 0, 54, 3, 1, 1, 12, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24
};
char sm_f_illegal[48] = {
    1, 94, 0, 32, 1, 35, 0, 32, 1, 20, 0, 32, 1, 11, 3, 1, 1, 255, 1, 127, 0, 5, 1, 4,
    3, 1, 1, 244, 0, 55, 3, 1, 1, 125, 0, 32, 3, 1, 1, 166, 0, 30, 3, 1, 1, 144
};
char sm_m[80] = {
    1, 34, 0, 159, 1, 20, 0, 32, 1, 23, 0, 24, 1, 19, 0, 24, 1, 34, 0, 24, 1, 11, 0, 24,
    1, 13, 0, 24, 1, 11, 0, 24, 1, 1, 0, 143, 1, 24, 0, 24, 1, 28, 0, 24, 1, 5, 0, 199,
    3, 1, 1, 12, 0, 145, 3, 1, 1, 14, 0, 24, 1, 22, 0, 24, 1, 10, 0, 102, 3, 1, 1, 12,
    0, 24, 1, 12, 0, 24, 1, 12
};
char sm_m_illegal[42] = {
    1, 58, 0, 135, 1, 20, 0, 32, 1, 6, 3, 1, 1, 249, 0, 143, 1, 11, 3, 1, 1, 93, 0, 199,
    3, 1, 1, 36, 0, 121, 3, 1, 1, 94, 0, 102, 3, 1, 1, 108, 0, 36
};
char usum_f[164] = {
    1, 34, 0, 24, 1, 12, 0, 24, 3, 1, 1, 4, 0, 21, 1, 37, 0, 31, 1, 21, 0, 9, 1, 24, 0,
    24, 1, 11, 0, 24, 1, 13, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 11, 0,
    24, 1, 13, 0, 24, 1, 2, 3, 1, 1, 31, 0, 24, 1, 11, 0, 24, 1, 1, 3, 1, 1, 16, 0, 24,
    1, 1, 0, 14, 1, 24, 0, 24, 1, 28, 0, 24, 1, 17, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24,
    1, 11, 0, 24, 1, 1, 3, 1, 1, 2, 0, 28, 3, 1, 1, 12, 0, 24, 1, 17, 0, 24, 1, 24, 0,
    56, 1, 15, 0, 24, 1, 22, 0, 24, 1, 22, 0, 24, 1, 12, 0, 24, 3, 1, 1, 1, 0, 28, 1,
    13, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 1, 12, 0, 24, 3, 1
};
char usum_f_illegal[56] = {
    1, 94, 3, 1, 1, 4, 0, 21, 1, 37, 0, 31, 1, 21, 0, 9, 1, 255, 1, 47, 3, 1, 1, 91, 3,
    1, 1, 41, 0, 14, 1, 249, 3, 1, 1, 2, 0, 28, 3, 1, 1, 125, 0, 32, 1, 167, 3, 1, 1,
    1, 0, 28, 1, 145, 3, 1
};
char usum_m[108] = {
    1, 34, 0, 24, 3, 1, 1, 5, 0, 124, 1, 21, 0, 9, 1, 23, 0, 24, 3, 1, 1, 18, 0, 24, 1,
    34, 0, 24, 1, 11, 0, 24, 1, 13, 0, 24, 1, 11, 0, 24, 1, 1, 3, 1, 1, 15, 0, 24, 1,
    2, 0, 152, 1, 24, 0, 24, 1, 28, 0, 24, 1, 5, 3, 1, 1, 2, 0, 173, 1, 12, 0, 24, 3,
    1, 1, 1, 0, 119, 1, 15, 0, 24, 1, 22, 0, 24, 1, 10, 3, 1, 1, 1, 0, 100, 1, 13, 0,
    24, 1, 12, 0, 24, 1, 12, 0, 24, 3, 1
};
char usum_m_illegal[56] = {
    1, 58, 3, 1, 1, 5, 0, 124, 1, 21, 0, 9, 1, 47, 3, 1, 1, 208, 3, 1, 1, 38, 0, 1, 1,
    2, 0, 152, 1, 105, 3, 1, 1, 2, 0, 173, 1, 36, 3, 1, 1, 1, 0, 119, 1, 95, 3, 1, 1,
    1, 0, 100, 1, 109, 3, 1
};

void writeArray (char *array, int fashionOffset, int rleSize) {
    int arraySize = 0;
    for (int i = 1; i < rleSize; i += 2) {
        arraySize += array[i];
    }

    char* finalArray = malloc(arraySize);
    int faPosition = 0;
    char times = 0;
    for (int i = 0; i < rleSize; i += 2) {
        times = array[i + 1];
        for (int j = 0; j < times; j++) {
            finalArray[faPosition] = array[i];
            faPosition++;
        }
    }

    sav_set_data(finalArray, arraySize, fashionOffset, 0);
    free(finalArray);
}

int main (int argc, char **argv) {
    unsigned char version = *argv[0];
    unsigned int fashionOffset;
    unsigned int rleSize;
    char *array = NULL;
    switch (version) {
        case 24:
        case 25:
            sav_set_data(xy, sizeof(xy), 0x1A00, 0); // didn't RLE-compress XY
            return 0;
        case 30:
        case 31:
            fashionOffset = 0x42000;
            int illegal = gui_choice("Would you like illegal clothes as well?");
            if (sav_get_value(SAV_GENDER)) { // checks if it's not 0, which is male, so it checks for female
                if (illegal) {
                    array = sm_f_illegal;
                    rleSize = sizeof(sm_f_illegal);
                }
                else {
                    array = sm_f;
                    rleSize = sizeof(sm_f);
                }
            }
            else {
                if (illegal) {
                    array = sm_m_illegal;
                    rleSize = sizeof(sm_m_illegal);
                }
                else {
                    array = sm_m;
                    rleSize = sizeof(sm_m);
                }
            }
            break;
        case 32:
        case 33:
            fashionOffset = 0x42600;
            int illegal = gui_choice("Would you like illegal clothes as well?");
            if (sav_get_value(SAV_GENDER)) {
                if (illegal) {
                    array = usum_f_illegal;
                    rleSize = sizeof(usum_f_illegal);
                }
                else {
                    array = usum_f;
                    rleSize = sizeof(usum_f);
                }
            }
            else {
                if (illegal) {
                    array = usum_m_illegal;
                    rleSize = sizeof(usum_m_illegal);
                }
                else {
                    array = usum_m;
                    rleSize = sizeof(usum_m);
                }
            }
            break;
        default:
            if (version > 41) {
                gui_warn("Game not supported,\ntry All Clothing - Switch.");
            }
            else if (version != 34) {
                gui_warn("Game not supported,\nbecause it has no changeable clothes.");
            }
            else {
                gui_warn("Game not supported.");
            }
            return 1;
    }
    if (array == NULL) {
        gui_warn("An error occurred, exiting.\nNo changes were made."); // I do NOT want to see what a null pointer would do
        return 1;
    }

    writeArray(array, fashionOffset, rleSize);
    return 0;
}
