#include <pksm.h>
#include <stdlib.h>

//This data is derived from https://projectpokemon.org/home/files/file/4041-swsh-fashion-block/ accessed May 27th, 2022, and bzip2-compressed

char sw_f[0x7F] = {
    0x42, 0x5A, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0xB0, 0xB1, 0x78, 0x6C, 0x00, 0x00,
    0x0C, 0x69, 0x82, 0xFF, 0xD2, 0x68, 0x00, 0x80, 0x00, 0x80, 0xBE, 0xFA, 0x42, 0x80, 0x00, 0x81,
    0x09, 0xA0, 0x00, 0x72, 0x30, 0xF5, 0x00, 0x00, 0x0C, 0x00, 0xF5, 0x1A, 0x09, 0x26, 0xA4, 0x35,
    0x32, 0x1A, 0x7A, 0x9E, 0xA0, 0x01, 0xE9, 0x03, 0xF4, 0xAE, 0x70, 0xA9, 0x7D, 0x37, 0x3D, 0x35,
    0xBC, 0x72, 0xD9, 0x7C, 0xF2, 0x0D, 0xF1, 0x82, 0x10, 0x10, 0x40, 0xB3, 0xC2, 0x77, 0x16, 0x8A,
    0xD5, 0xA0, 0xA4, 0x01, 0xAA, 0x74, 0xA9, 0x21, 0x06, 0x39, 0x95, 0x24, 0x4E, 0x22, 0xD6, 0x72,
    0x46, 0x8D, 0x1C, 0xBE, 0xB1, 0x2E, 0x27, 0xC6, 0x02, 0x1C, 0x81, 0x19, 0x02, 0x03, 0x79, 0xE0,
    0x26, 0x66, 0x7F, 0x65, 0x41, 0x77, 0x24, 0x53, 0x85, 0x09, 0x0B, 0x0B, 0x17, 0x86, 0xC0
};
char sw_m[0x8F] = {
    0x42, 0x5A, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x2A, 0x2C, 0x69, 0x75, 0x00, 0x00,
    0x35, 0xE9, 0xA9, 0xFF, 0xC8, 0x08, 0x00, 0x80, 0x40, 0x80, 0x30, 0xDD, 0x40, 0x80, 0x04, 0x80,
    0x00, 0x80, 0x00, 0x82, 0xE7, 0xA0, 0x00, 0x64, 0x25, 0x13, 0x45, 0x3C, 0xA7, 0x94, 0x6D, 0x4C,
    0x80, 0xD0, 0x7A, 0x98, 0xD0, 0x68, 0x50, 0x00, 0x00, 0x00, 0x0F, 0xD2, 0x8E, 0x73, 0x5D, 0xD3,
    0xE5, 0x15, 0xC1, 0xF9, 0x3C, 0x66, 0x25, 0x59, 0x03, 0x3E, 0x68, 0x20, 0x0C, 0x28, 0x97, 0xAD,
    0x79, 0xE7, 0x8C, 0x73, 0x54, 0x19, 0x6A, 0xA2, 0x1E, 0xE7, 0x28, 0x3D, 0x54, 0xDA, 0x90, 0x0E,
    0xAA, 0x22, 0x61, 0xD8, 0xC4, 0x5D, 0xAF, 0x04, 0xA1, 0x19, 0xD1, 0x72, 0xB5, 0xAD, 0x24, 0x20,
    0x08, 0x3A, 0xB8, 0x54, 0x40, 0x0A, 0xA2, 0x15, 0x01, 0x1B, 0x91, 0x87, 0x6C, 0x15, 0xA6, 0x26,
    0x21, 0xF1, 0x84, 0x3F, 0xE2, 0xEE, 0x48, 0xA7, 0x0A, 0x12, 0x05, 0x45, 0x8D, 0x2E, 0xA0
};
char sh_f[0x7F] = {
    0x42, 0x5A, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x69, 0xCE, 0x54, 0xD0, 0x00, 0x00,
    0x0C, 0x69, 0x82, 0xFF, 0xD2, 0x68, 0x00, 0x80, 0x00, 0x80, 0xBE, 0xFA, 0x42, 0x80, 0x00, 0x81,
    0x03, 0xA0, 0x00, 0x72, 0x30, 0xF5, 0x00, 0x00, 0x0C, 0x00, 0xF5, 0x1A, 0x09, 0x26, 0xA4, 0x35,
    0x32, 0x1A, 0x7A, 0x9E, 0xA0, 0x01, 0xE9, 0x03, 0xF4, 0xAE, 0x70, 0xA9, 0x7D, 0x37, 0x3D, 0x35,
    0xBC, 0x72, 0xD9, 0x7C, 0xF2, 0x0D, 0xF1, 0x82, 0x10, 0x10, 0x40, 0xB3, 0xC2, 0x77, 0x16, 0x8A,
    0xD5, 0xA0, 0xA4, 0x01, 0xAA, 0x74, 0xA9, 0x21, 0x06, 0x39, 0x95, 0x24, 0x4E, 0x22, 0xD6, 0x72,
    0x46, 0x8D, 0x1C, 0xBE, 0xB1, 0x2E, 0x27, 0xC6, 0x02, 0x1C, 0x81, 0x19, 0x02, 0x03, 0x79, 0xE0,
    0x26, 0x66, 0x7F, 0x65, 0x41, 0x77, 0x24, 0x53, 0x85, 0x09, 0x06, 0x9C, 0xE5, 0x4D, 0x00
};
char sh_m[0x8F] = {
    0x42, 0x5A, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x66, 0x8B, 0xDC, 0xD3, 0x00, 0x00,
    0x35, 0xE9, 0xA3, 0xFF, 0xC8, 0x08, 0x00, 0x80, 0x40, 0x80, 0x30, 0xDD, 0x40, 0x80, 0x04, 0x80,
    0x00, 0x80, 0x00, 0x82, 0xE7, 0xA0, 0x00, 0x64, 0x25, 0x13, 0x45, 0x3C, 0xA7, 0x94, 0x6D, 0x4C,
    0x80, 0xD0, 0x7A, 0x98, 0xD0, 0x68, 0x50, 0x00, 0x00, 0x00, 0x0F, 0xD2, 0x8E, 0x73, 0x5D, 0xD3,
    0xE5, 0x15, 0xC1, 0xF9, 0x3C, 0x66, 0x25, 0x59, 0x03, 0x3E, 0x68, 0x20, 0x0C, 0x28, 0x97, 0xAD,
    0x79, 0xE7, 0x8C, 0x73, 0x54, 0x19, 0x6A, 0xA2, 0x1E, 0xE7, 0x28, 0x3D, 0x54, 0xDA, 0x90, 0x0E,
    0xAA, 0x22, 0x61, 0xD8, 0xC4, 0x5D, 0xAF, 0x04, 0xA1, 0x19, 0xD1, 0x72, 0xB5, 0xAD, 0x24, 0x20,
    0x08, 0x3A, 0xB8, 0x54, 0x40, 0x0A, 0xA2, 0x15, 0x01, 0x1B, 0x91, 0x87, 0x6C, 0x15, 0xA6, 0x26,
    0x21, 0xF1, 0x84, 0x3F, 0xE2, 0xEE, 0x48, 0xA7, 0x0A, 0x12, 0x0C, 0xD1, 0x7B, 0x9A, 0x60
};

char* error = "An error occurred, exiting.\nNo changes were made.";

int main (int argc, char **argv) {
    unsigned char version = *argv[0];
    unsigned int fashionOffset, compressedSize, decompressedSize;
    char *compressedData = NULL, *decompressedData;
    switch (version) {
        case 44:
            fashionOffset = 0xD224F9AC; // key to the Fashion block
            if (sav_get_value(SAV_GENDER)) {
                compressedData = sw_f;
                compressedSize = sizeof(sw_f);
            }
            else {
                compressedData = sw_m;
                compressedSize = sizeof(sw_m);
            }
            break;
        case 45:
            fashionOffset = 0xD224F9AC;
            if (sav_get_value(SAV_GENDER)) {
                compressedData = sh_f;
                compressedSize = sizeof(sh_f);
            }
            else {
                compressedData = sh_m;
                compressedSize = sizeof(sh_m);
            }
            break;
        default:
            if (version < 42) {
                gui_warn("Game not supported,\ntry All Clothing.");
            }
            else if (version > 45) {
                gui_warn("Game not supported,\ntoo new.");
            }
            else {
                gui_warn("Game not supported.");
            }
            return 1;
    }
    if (compressedData == NULL) {
        gui_warn(error);
        return 1;
    }

    pksm_bz2_decompress(&decompressedData, &decompressedSize, compressedData, compressedSize);

    if (decompressedData == NULL) {
        gui_warn(error);
        return 1;
    }

    sav_set_data(decompressedData, decompressedSize, fashionOffset, 0);
    free(decompressedData);

    return 0;
}
