#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int gbo = sav_gbo();
    int offsetToday;
    int offsetYesterday;
    struct pkx options[16];
    int species[16] = {133, 438, 440, 52, 173, 35, 174, 311, 39, 137, 351, 312, 439, 183, 113, 298};
    char *optionLabels[] = {
        "Eevee", "Bonsly", "Happiny", "Meowth",
        "Cleffa", "Clefairy", "Igglybuff", "Plusle",
        "Jigglypuff", "Porygon", "Castform", "Minun",
        "Mime Jr.", "Marill", "Chansey", "Azurill"};
    char yestText[60] = {'\0'};

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
        optionLabels[9] = "Ditto";
        break;
    default:
        gui_warn("This script is only meant for", "the Sinnoh games (DPPt)");
        return 1;
    }

    for (int i = 0; i < 16; i++)
    {
        options[i].species = species[i];
        options[i].form = 0;
    }

    char choiceToday = (char)gui_menu_6x5("Choose new Trophy Garden visitor", 16, &optionLabels[0], &options[0], GEN_FOUR);
    sprintf(&yestText, "Choose old Trophy Garden visitor\nSelect %s to skip", optionLabels[choiceToday]);
    char choiceYesterday = (char)gui_menu_6x5(yestText, 16, &optionLabels[0], &options[0], GEN_FOUR);

    saveData[gbo + offsetToday] = choiceToday;
    if (choiceYesterday != choiceToday)
    {
        saveData[gbo + offsetYesterday] = choiceYesterday;
    }

    return 0;
}
