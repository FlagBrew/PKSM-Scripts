#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int musicalSize = 0x17C00;

void writeMusical (char *data, char version) {
    char dlcFooter[] = {0, 0, 3, 0, 0, 0, 0x14, 0x7D, 1, 0, 0x27, 0x35, 5, 0x31, 0, 0};
    int dataOffset;
    char skinPresentPlayerInfoOffset;
    if (version < 22) {
        dlcFooter[2] = 4;
        dlcFooter[7] = 0xFD;
        dataOffset = 0x56000;
        skinPresentPlayerInfoOffset = 0x5C;
    }
    else {
        dataOffset = 0x55800;
        skinPresentPlayerInfoOffset = 0x74;
    }

    int footerOffset = dataOffset + musicalSize;

    sav_set_data(data, musicalSize + 0x178, dataOffset, 0);
    sav_set_short(2, footerOffset, 0); //updates to block
    sav_set_data(dlcFooter, 0x10, footerOffset, 0x102);
    sav_set_short(0xC21E, 0x19400, 0x3C); //signals presence
    sav_set_data(data + musicalSize + 0x114, 0x26, 0x1F908, 0);
    sav_set_byte(1, 0x1F99E, 0);
    sav_set_byte(dlcFooter[2], 0x19400, skinPresentPlayerInfoOffset);
}

int main (int argc, char **argv) {
    char version = *argv[0];
    if (version < 20 || version > 23) {
        gui_warn("Script only works with Black, White, Black 2, and White 2");
        return 1;
    }
    if (version < 22) {
        musicalSize = 0x1FC00;
    }

    mkdir("/3ds", 0777);
    mkdir("/3ds/PKSM", 0777);
    mkdir("/3ds/PKSM/Musicals", 0777);

    struct directory *skins = read_directory("/3ds/PKSM/Musicals");

    if (skins->count == 0) {
        gui_warn("There are no files in \'/3ds/PKSM/Musicals\'!\nPlace .pms files there");
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
    if (!((int)extension && !strcasecmp(extension, "pms"))) {
        gui_warn("Unsupported extension.\nOnly .pms files are supported.");
        return 1;
    }

    FILE* file = fopen(skins->files[chosen], "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    if (size != musicalSize + 0x178) {
        gui_warn("Either the file is not correctly formatted,\nor it was made for the other game set.");
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
    
    writeMusical(data, version);

    free(data);

    return 0;
}
