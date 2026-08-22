#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Items pocket, shared by BW and B2W2
#define POUCH_ITEMS 0x18400
#define POUCH_ITEMS_SLOTS 261
#define PASS_ORB 575
#define PASS_ORB_MAX 65535

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
    if (val < 0 || val > 63)
    {
        // Not a pass power value at all: BW only uses the first of the three
        // bytes, so the two after it hold unrelated data that must never be
        // used to index power_names
        return power_names[0];
    }
    else if (val <= 45)
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

// Gen 5 pockets are a contiguous list terminated by an empty entry, so the
// first id of 0 is both the end of the list and the first free slot.
// Returns -1 if the pocket is full and holds no Pass Orbs.
int findPassOrbSlot(void)
{
    int i;
    for (i = 0; i < POUCH_ITEMS_SLOTS; i++)
    {
        unsigned short id = sav_get_short(0, POUCH_ITEMS + i * 4);
        if (id == 0 || id == PASS_ORB)
        {
            return i;
        }
    }
    return -1;
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
    int numSlots;

    char slot1[30];
    char slot2[30];
    char slot3[30];
    char orbs[30];

    char** choices;
    int numChoices;
    char* bwchoices[3] = {slot1, orbs, "Exit"};
    char* b2w2choices[5] = {slot1, slot2, slot3, orbs, "Exit"};

    switch (version)
    {
        case 20: // B
        case 21: // W
            choices = bwchoices;
            numSlots = 1;
            numChoices = 3;
            offset    = 0x214A0;
            namesSize = 47;
            break;
        case 22: // B2
        case 23: // W2
            choices = b2w2choices;
            numSlots = 3;
            numChoices = 5;
            offset    = 0x213A0;
            namesSize = 62;
            break;
    }

    int i;
    for (i = 0; i < numSlots; i++)
    {
        sprintf(choices[i], "Slot %i: %s", i + 1, valToString(sav_get_byte(0, offset + i)));
    }

    int orbSlot = findPassOrbSlot();
    int orbCount = 0;
    if (orbSlot >= 0 && sav_get_short(0, POUCH_ITEMS + orbSlot * 4) == PASS_ORB)
    {
        // the count is a u16, so mask off any sign extension
        orbCount = sav_get_short(0, POUCH_ITEMS + orbSlot * 4 + 2) & 0xFFFF;
    }
    sprintf(orbs, "Pass Orbs: %i", orbCount);

    int choice;

    do
    {
        choice = gui_menu_10x2("What would you like to edit?", numChoices, choices);

        if (choice < numSlots)
        {
            char newval =
                (char)gui_menu_10x2("Which pass power would you like?", namesSize, &power_names[0]);

            sav_set_byte(power_values[newval], 0, offset + choice);

            sprintf(choices[choice], "Slot %i: %s", (int)choice + 1, valToString(power_values[newval]));
        }
        else if (choice == numSlots)
        {
            if (orbSlot < 0)
            {
                gui_warn("Your Items pocket is full,\nso Pass Orbs can't be added.");
            }
            else
            {
                // The MAX pass powers cost 9999 orbs to activate, which is well
                // past what the game itself lets you carry
                unsigned int quantity = 9999;
                gui_numpad(&quantity, "How many Pass Orbs?", 5);
                if (quantity < 1)
                {
                    quantity = 1;
                }
                else if (quantity > PASS_ORB_MAX)
                {
                    quantity = PASS_ORB_MAX;
                }

                sav_set_short(PASS_ORB, 0, POUCH_ITEMS + orbSlot * 4);
                sav_set_short(quantity, 0, POUCH_ITEMS + orbSlot * 4 + 2);

                sprintf(orbs, "Pass Orbs: %i", (int)quantity);
            }
        }
    }
    while (choice != numChoices-1);
    return 0;
}
