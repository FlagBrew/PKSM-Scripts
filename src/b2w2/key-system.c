#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
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
    int ID = *(int *)(saveData + 0x25800 + 0x5c);
    int keyOffset = 0x25800 + 0x28;
    int choice;
    char *message[25] = {'\0'};

    do
    {
        choice = gui_menu_20x2("Obtain which key or\nunlock which feature?", 11, &keyStrings[0]);
        if (choice != 10) {
            *(int *)(saveData + keyOffset + choice * 4) = ID ^ keyVals[choice];
            if (choice < 5) {
                sprintf(message, "%s obtained", keyStrings[choice]);
                gui_warn(message);
            }
            else
            {
                sprintf(message, "%s unlocked", keyStrings[choice]);
                gui_warn(message);
            }
        }
    } while (choice != 10);
    return 0;
}
