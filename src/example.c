#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned char* saveData = (unsigned char*) atoi(argv[0]);
    int saveLength = atoi(argv[1]);
    unsigned char version = *argv[2];
    sav_gbo();
    sav_sbo();
    sav_box_decrypt();
    sav_box_encrypt();

    struct pkx showMe[13];
    char* labels[13];
    for (int i = 0; i < 13; i++)
    {
        showMe[i].species = 666;
        showMe[i].form = i;
        labels[i] = "Label";
    }
    gui_warn("Tests incoming!", "");
    if (!gui_choice("Would you like to continue testing?", ""))
    {
        return 1;
    }
    gui_menu_6x5("This displays Pokemon!", 13, &labels[0], &showMe[0], 7);
    gui_menu_20x2("And this displays text!", 13, &labels[0]);
    gui_warn("Debugging is a pain!", "Ask for a specific debugging build!");
    return 0;
}
