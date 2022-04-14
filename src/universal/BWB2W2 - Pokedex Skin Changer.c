#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//code ported from PKHeX

short skinSize = 0x6200;

//this is almost verbatim from PKHeX
short crc16_ccitt (char *data, short size) {
    char top = 0xFF;
    char bot = 0xFF;
    char x;

    for (short i = 0; i < size; i++) {
        x = data[i] ^ top;
        x ^= (x >> 4);
        top = bot ^ (x >> 3) ^ (x << 4);
        bot = x ^ (x << 5);
    }

    return (top << 8) | bot;
}

void writeSkin (char *data, char version) {
    int dataOffset;
    char skinPresentPlayerInfoOffset;
    if (version < 22) {
        sav_set_short(4, 0x1C028, 0);
        sav_set_short(1, 0x1C029, 0);
        dataOffset = 0x76000;
        skinPresentPlayerInfoOffset = 0x60;
    }
    else {
        dataOffset = 0x6D800;
        skinPresentPlayerInfoOffset = 0x78;
    }

    char dlcFooter[] = {0, 0, 1, 0, 0, 0, 0x14, 0x63, 0, 0, 0x27, 0x35, 5, 0x31, 0, 0};
    int footerOffset = dataOffset + skinSize;
    short skinChecksum = crc16_ccitt(data, skinSize + 4);

    sav_set_data(data, skinSize, dataOffset, 0);
    sav_set_int(1, footerOffset, 0);

    sav_set_short(skinChecksum, footerOffset, 6);
    sav_set_short(skinChecksum, footerOffset, 0x100);
    sav_set_data(dlcFooter, 0x10, footerOffset, 0x102);

    char *check2Data = malloc(4);
    sav_get_data(check2Data, 4, footerOffset, 0x100);
    short secondChecksum = crc16_ccitt(check2Data, 4);
    free(check2Data);

    sav_set_short(secondChecksum, footerOffset, 0x112);
    sav_set_short(0xC21E, 0x19400, 0x3E); //signals skin presence
    sav_set_byte(1, 0x19400, skinPresentPlayerInfoOffset);
}

int main (int argc, char **argv) {
    char version = *argv[0];
    if (version < 20 || version > 23) {
        gui_warn("Script only works with Black, White, Black 2, and White 2");
        return 1;
    }

    mkdir("/3ds", 0777);
    mkdir("/3ds/PKSM", 0777);
    mkdir("/3ds/PKSM/PokedexSkins", 0777);

    struct directory *skins = read_directory("/3ds/PKSM/PokedexSkins");

    if (skins->count == 0) {
        gui_warn("There are no files in \'/3ds/PKSM/PokedexSkins\'!\nPlace .pds files there");
        delete_directory(skins);
        return 0;
    }

    int chosen = gui_menu_20x2("Choose a file to inject", skins->count, skins->files);

    char* extension = NULL;
    if (strlen(skins->files[chosen]) > 3)
    {
        if (skins->files[chosen][strlen(skins->files[chosen]) - 4] == '.')
        {
            extension = skins->files[chosen] + strlen(skins->files[chosen]) - 3;
        }
    }

    if (!((int)extension && !strcasecmp(extension, "pds"))) {
        gui_warn("Unsupported extension.\nOnly .pds files are supported.");
        return 1;
    }

    FILE* file = fopen(skins->files[chosen], "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    if (size != skinSize) {
        gui_warn("File not correctly formatted.");
        return 1;
    }
    fseek(file, 0, SEEK_SET);
    char *data = malloc(size + 4);  //we need to include an int for the checksum
    *((int*)(data + skinSize)) = 1;
    if (data == NULL) {
        gui_warn("An error occurred.");
        return -1;
    }
    fread(data, 1, size, file);
    fclose(file);
    
    writeSkin(data, version);

    free(data);

    return 0;
}
