#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int offset;
    enum Generation gen;

    switch (version)
    {
        case 24:
        case 25:
            offset = 0x4250;
            gen = GEN_SIX;
            break;
        case 26:
        case 27:
            offset = 0x4244;
            gen = GEN_SIX;
            break;
        case 30:
        case 31:
            offset = 0x4130;
            gen = GEN_SEVEN;
            break;
        case 32:
        case 33:
            offset = 0x4530;
            gen = GEN_SEVEN;
            break;
        default:
            gui_warn("Vivillon didn't exist before Gen 6");
            return 1;
    }

    struct pkx vivillon[20];
    char pattern;
    for (int i = 0; i < 20; i++)
    {
        vivillon[i].species = 666;
        vivillon[i].form = i;
    }
    char *labels[20] = {
        "Icy Snow", "Polar", "Tundra", "Continental", "Garden",
        "Elegant", "Meadow", "Modern", "Marine", "Archipelago",
        "High Plains", "Sandstorm", "River", "Monsoon", "Savannah",
        "Sun", "Ocean", "Jungle", "Fancy", "Poke Ball"
    };

    while(true){
        pattern = (char)gui_menu_6x5("Choose a Vivillon pattern", 20, &labels[0], &vivillon[0], gen);
        if (pattern > 17)
        {
            if (gui_choice("Fancy and Poke Ball\nare event-exclusive patterns"))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    sav_set_byte(pattern, offset, 0);
    char message[50] = {'\0'};
    sprintf(message, "Save\'s native Vivillon pattern set to %s", labels[pattern]);
    gui_warn(message);

    return 0;
}
