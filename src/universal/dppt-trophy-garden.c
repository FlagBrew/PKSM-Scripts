#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)argv[0];
    unsigned char version = *argv[2];
    int offsetToday, offsetYesterday;
    struct pkx options[16];
    int species[16] = {133, 438, 440, 52, 173, 35, 174, 311, 39, 137, 351, 312, 439, 183, 113, 298};
    char *labels[16];

    switch (version)
    {
        case 10:
        case 11:
            offsetToday = 0x72dc;
            offsetYesterday = 0x72de;
            break;
        case 12:
            offsetToday = 0x7f30;
            offsetYesterday = 0x7f32;
            species[9] = 132;
            break;
        default:
            gui_warn("This script is only meant for\nthe Sinnoh games (DPPt)");
            return 1;
    }

    int gbo = sav_gbo(), i, slot, choice;
    for (i = 0; i < 16; i++)
    {
        options[i].species = species[i];
        options[i].form = 0;
        labels[i] = i18n_species(species[i]);
    }

    char *visiting[55] = {'\0'};
    struct pkx slotPkx[3];
    char *slots[] = {
        "Exit script", "Today", "Yesterday"
    };
    int current[3] = {
        0,
        saveData[gbo + offsetToday],
        saveData[gbo + offsetYesterday]
    };
    for(i = 0; i < 3; i++)
    {
        slotPkx[i].species = species[current[i]];
        slotPkx[i].form = 0;
    }
    slotPkx[0].species = 0;

    slot = gui_menu_6x5("Which day's visitor do you\nwant to edit?", 3, slots, slotPkx, GEN_FOUR);
    while(slot > 0){
        choice = gui_menu_6x5("Choose new Trophy Garden visitor", 16, labels, options, GEN_FOUR);

        if (current[slot % 2 + 1] == choice)
        {
            sprintf(visiting, "%s is already a visitor", labels[choice]);
            gui_warn(visiting);
            continue;
        }
        if (current[slot] != choice)
        {
            current[slot] = choice;
            slotPkx[slot].species = species[choice];
            saveData[gbo + (slot == 1 ? offsetToday : offsetYesterday)] = (char)choice;
        }
        slot = gui_menu_6x5("Which day's visitor do you\nwant to edit?", 3, slots, slotPkx, GEN_FOUR);
    }

    return 0;
}
