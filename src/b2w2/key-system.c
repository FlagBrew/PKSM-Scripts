#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    char *keyStrings[] = {
        "Easy Key", "Challenge Key", "Treehollow Key", "Iron Key", "Iceberg Key",
        "Easy Mode", "Challenge Mode", "White Forest", "Iron Chamber", "Iceberg Chamber",
        "None (exit script)"};

    if (version == 22) {
        keyStrings[2] = "Tower Key";
        keyStrings[7] = "Black City";
    }

    int keyVals[] = {
        0x35691, 0x18256, 0x59389, 0x48292, 0x9892,
        0x93389, 0x22843, 0x34771, 0xab031, 0xb3818};
    int ID = sav_get_int(0x25800, 0x5c);
    int keyOffset = 0x25800 + 0x28;
    int choice;
    char message[51] = {'\0'};

    do
    {
        choice = gui_menu_20x2("Obtain which key or\nunlock which feature?", 11, &keyStrings[0]);
        if (choice < 5) {
            sav_set_int(ID ^ keyVals[choice], keyOffset, choice * 4);
            sprintf(message, "%s obtained\nAlso unlock %s?", keyStrings[choice], keyStrings[choice + 5]);
            if (gui_choice(message))
            {
                choice += 5;
            }
            memset(message, '\0', 51);
        }
        if (choice > 4 && choice < 10)
        {
            sav_set_int(ID ^ keyVals[choice], keyOffset, choice * 4);
            sprintf(message, "%s unlocked", keyStrings[choice]);
            gui_warn(message);
        }
    } while (choice != 10);
    return 0;
}
