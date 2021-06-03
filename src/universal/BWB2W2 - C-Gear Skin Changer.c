#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//code ported from PKHeX

short skinSize = 0x2600;

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
    int skinInfoOffset, dataOffset;
    char skinPresentPlayerInfoOffset;
    if (version < 22) {
        skinInfoOffset = 0x1C024;
        dataOffset = 0x52000;
        skinPresentPlayerInfoOffset = 0x54;
    }
    else {
        skinInfoOffset = 0x1C034;
        dataOffset = 0x52800;
        skinPresentPlayerInfoOffset = 0x6C;
    }

    char dlcFooter[] = {0, 0, 1, 0, 0, 0, 0x14, 0x27, 0, 0, 0x27, 0x35, 5, 0x31, 0, 0};
    int footerOffset = dataOffset + skinSize;
    short skinChecksum = crc16_ccitt(data, skinSize);

    sav_set_data(data, skinSize, dataOffset, 0);
    sav_set_short(1, footerOffset, 0); //updates to block
    sav_set_short(skinChecksum, footerOffset, 2);
    sav_set_short(skinChecksum, footerOffset, 0x100);
    sav_set_data(dlcFooter, 0x10, footerOffset, 0x102);

    char* check2Data = malloc(4);
    sav_get_data(check2Data, 4, footerOffset, 0x100);
    short secondChecksum = crc16_ccitt(check2Data, 4);
    free(check2Data);

    sav_set_short(secondChecksum, footerOffset, 0x112);
    sav_set_short(0xC21E, 0x19400, 0x38); //signals skin presence
    sav_set_short(skinChecksum, skinInfoOffset, 0);
    sav_set_byte(1, 0x19400, skinPresentPlayerInfoOffset);
    sav_set_byte(1, skinInfoOffset, 2);
}

//following two adapted from PKHeX
void CGBtoPSK (char* data) {
    unsigned short x, rot, tile;
    for (int i = 0x2000; i < skinSize; i += 2) {
        x = *((short*)(data + i));

        rot = x & 0xFF00;
        tile = x & 0x00FF;
        if (tile == 0xFF) tile = 0;
        x = tile + (15 * (tile / 17)) + 0xA0A0 + rot;

        data[i] = x;
        data[i + 1] = x >> 8;
    }
}

void PSKtoCGB (char* data) {
    char rot, tile;
    unsigned short x, trunc;
    for (int i = 0x2000; i < skinSize; i += 2) {
        x = *((short*)(data + i));
        
        trunc = x & 0x3FF;
        if (trunc < 0xA0 || trunc > 0x280) {
            x = (x & 0x5C00) | 0xFF;
        }
        else {
            x = ((x % 0x20) + (17 * ((trunc - 0xA0) / 0x20))) | (x & 0x5C00);
        }

        tile = x;
        rot = x >> 8;
        if (tile == 0xFF) tile = 0;
        data[i] = tile;
        data[i + 1] = rot;
    }
}

//another near-verbatim from PKHeX
char isCGB (char *data) {
    //check the odd bytes for anything that isn't a rotation flag
    char inverseOfFlags = ~0b1100;
    for (int i = 0x2001; i < 0x2600; i += 2) {
        if ((data[i] & inverseOfFlags)) return 0;
    }
    return 1;
}

int main (int argc, char **argv) {
    char version = *argv[0];
    if (version < 20 || version > 23) {
        gui_warn("Script only works with Black, White, Black 2, and White 2");
        return 1;
    }

    mkdir("/3ds", 0777);
    mkdir("/3ds/PKSM", 0777);
    mkdir("/3ds/PKSM/C-Gear", 0777);

    struct directory *skins = read_directory("/3ds/PKSM/C-Gear");

    if (skins->count == 0) {
        gui_warn("There are no files in \'/3ds/PKSM/C-Gear\'!\nPlace .cgb or .psk files there");
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
    //BW uses PSK, B2W2 uses CGB.
    if (!(((int)extension && !strcasecmp(extension, "cgb")) || ((int)extension && !strcasecmp(extension, "psk")))) {
        gui_warn("Unsupported extension.\nOnly .cgb and .psk files are supported.");
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
    char* data = malloc(size);
    if (data == NULL) {
        gui_warn("An error occurred.");
        return -1;
    }
    fread(data, 1, size, file);
    fclose(file);

    char cgb = isCGB(data);

    if (cgb && version < 22) {
        CGBtoPSK(data);
    }
    else if (!cgb && version > 21) {
        PSKtoCGB(data);
    }
    
    writeSkin(data, version);

    free(data);

    return 0;
}
