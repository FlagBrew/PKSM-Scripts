#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// NOTE: 46 and 47 are unused, and only <= 48 are valid for BW
char* power_names[62] = {"None", "Encounter +1", "Encounter +2", "Encounter +3", "Encounter -1",
    "Encounter -2", "Encounter -3", "Hatching +1", "Hatching +2", "Hatching +3", "Befriending +1",
    "Befriending +2", "Befriending +3", "Bargain +1", "Bargain +2", "Bargain +3", "HP +1", "HP +2",
    "HP +3", "PP +1", "PP +2", "PP +3", "EXP +1", "EXP +2", "EXP +3", "EXP -1", "EXP -2", "EXP -3",
    "PrizeMoney +1", "PrizeMoney +2", "PrizeMoney +3", "Capture +1", "Capture +2", "Capture +3",

    "Hatching S", "Bargain S", "Befriending S", "EXP S", "PrizeMoney S", "Capture S",
    "HP Full Recovery", "Hatch MAX", "Bargain MAX", "Befriending MAX", "EXP MAX", "PrizeMoney MAX",
    "Capture MAX",

    "Search +1", "Search +2", "Search +3", "HiddenGrotto +1", "HiddenGrotto +2", "HiddenGrotto +3",
    "Charm +1", "Charm +2", "Charm +3",

    "Search S", "Search MAX", "HiddenGrotto S", "HiddenGrotto MAX", "Charm S", "Charm MAX"};

int power_values[62] = {48, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
    44, 45, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

char* valToString(int val)
{
    if (val <= 45)
    {
        return power_names[val + 1];
    }
    else if (val <= 48)
    {
        return power_names[0];
    }
    else
    {
        return power_names[val - 2];
    }
}

int main(int argc, char** argv)
{
    char version = *argv[0];
    if (version < 20 || version > 23)
    {
        gui_warn("Script only works with Black, White, Black 2, and White 2");
        return 1;
    }

    int namesSize;
    int offset;

    char slot1[30];
    char slot2[30];
    char slot3[30];

    char** choices;
    int numChoices;
    char* bwchoices[2] = {slot1, "Exit"};
    char* b2w2choices[4] = {slot1, slot2, slot3, "Exit"};

    switch (version)
    {
        case 20: // B
        case 21: // W
            choices=bwchoices;
            numChoices = 2;
            offset    = 0x214A0;
            namesSize = 47;
            break;
        case 22: // B2
        case 23: // W2
            choices = b2w2choices;
            numChoices = 4;
            offset    = 0x213A0;
            namesSize = 62;
            break;
    }

    sprintf(slot1, "Slot 1: %s", valToString(sav_get_byte(0, offset)));
    sprintf(slot2, "Slot 2: %s", valToString(sav_get_byte(0, offset + 1)));
    sprintf(slot3, "Slot 3: %s", valToString(sav_get_byte(0, offset + 2)));

    int choice;

    do
    {
        choice = gui_menu_20x2("Which slot would you like to edit?", numChoices, choices);

        if (choice != numChoices-1)
        {
            char newval =
                (char)gui_menu_20x2("Which pass power would you like?", namesSize, &power_names[0]);

            sav_set_byte(power_values[newval], 0, offset + choice);

            sprintf(choices[choice], "Slot %i: %s", (int)choice + 1, valToString(power_values[newval]));
        }
    }
    while (choice != numChoices-1);
    return 0;
}
