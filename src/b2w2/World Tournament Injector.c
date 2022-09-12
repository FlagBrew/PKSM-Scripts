#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//this was made by referencing a decomp of Download Tournament Editor

short tourneySize = 0x1314;

void writeTourney (char *data, char index) {
    int dataOffset = 0x7A000 + index * 0x1400; //the 1400 is size aligned to 0x100
    char tourneyPresentPlayerInfoOffset = 0xA0 + index * 4;

    sav_set_data(data, tourneySize, dataOffset, 0);
    sav_set_int(*((int *)(data + 0x1304)), 0x19400, tourneyPresentPlayerInfoOffset);
    sav_set_short(0xC21E, 0x19452, index * 2); //signals presence
}

int main (int argc, char **argv) {
    mkdir("/3ds", 0777);
    mkdir("/3ds/PKSM", 0777);
    mkdir("/3ds/PKSM/PWT", 0777);

    struct directory *tourneys = read_directory("/3ds/PKSM/PWT");

    if (tourneys->count == 0) {
        gui_warn("There are no files in \'/3ds/PKSM/PWT\'!\nPlace .pwt files there");
        delete_directory(tourneys);
        return 0;
    }

    char *data = malloc(0x1314);
    if (data == NULL) {
        gui_warn("An error occurred.");
        return -1;
    }

    char *options[] = {"Slot 1", "Slot 2", "Slot 3", "Exit Script"};

    while (1) {
        int choice = gui_menu_20x2("Choose a Tournament slot", 4, options);

        if (choice == 3) {
            free(data);
            return 0;
        }

        int chosen = gui_menu_20x2("Choose a file to inject", tourneys->count, tourneys->files);

        char* extension = NULL;
        if (strlen(tourneys->files[chosen]) > 3)
        {
            if (tourneys->files[chosen][strlen(tourneys->files[chosen]) - 4] == '.')
            {
                extension = tourneys->files[chosen] + strlen(tourneys->files[chosen]) - 3;
            }
        }

        if (!((int)extension && !strcasecmp(extension, "pwt"))) {
            gui_warn("Unsupported extension.\nOnly .pwt files are supported.");
            return 1;
        }

        FILE* file = fopen(tourneys->files[chosen], "rb");
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        if (size != tourneySize) {
            gui_warn("File not correctly formatted.");
            return 1;
        }
        fseek(file, 0, SEEK_SET);
        fread(data, 1, size, file);
        fclose(file);
        
        writeTourney(data, choice);
    }
}
