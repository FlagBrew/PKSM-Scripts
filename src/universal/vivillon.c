#include <picoc_unix.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int offset;
    int gen;

    switch (version)
    {
    case 24:
    case 25:
        offset = 0x4250;
        gen = 6;
        break;
    case 26:
    case 27:
        offset = 0x4244;
        gen = 6;
        break;
    case 30:
    case 31:
        offset = 0x4130;
        gen = 7;
        break;
    case 32:
    case 33:
        offset = 0x4530;
        gen = 7;
        break;
    default:
        gui_warn("Vivillon didn't exist before Gen 6", "");
        return 1;
    }

    struct pkx vivillon[20];
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
        char pattern = (char)gui_menu6x5("Choose a Vivillon pattern", 20, &labels[0], &vivillon[0], gen);
        if (pattern > 17)
        {
            gui_warn("Fancy and Poke Ball", "are event-exclusive patterns");
            if (gui_choice("Choose this one anyway (A)", "Choose another pattern (B)"))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    saveData[offset] = pattern;
    gui_warn("Save\'s native Vivillon pattern set to", vivillon[pattern]);

    return 0;
}
