#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    int saveLength = atoi(argv[1]);
    unsigned char version = *argv[2];
    sav_gbo();
    sav_sbo();

    struct pkx showMe[13];
    char *labels[13];
    for (int i = 0; i < 13; i++)
    {
        showMe[i].species = 666;
        showMe[i].form = i;
        labels[i] = "Label";
    }
    /* species of 0 results in an Egg */
    showMe[0].species = 0;
    labels[0] = i18n_species(0);

    /* gui_warn and gui_choice demos */
    gui_warn("Tests incoming!", "");
    if (!gui_choice("Would you like to continue testing?", ""))
    {
        return 1;
    }

    /* gui_menu function demos */
    gui_menu_6x5("This displays Pokemon!", 13, &labels[0], &showMe[0], GEN_SEVEN);
    gui_menu_20x2("And this displays text!", 13, &labels[0]);

    /* keyboard and numpad demos */
    int quant = 21;
    char str[21];
    gui_numpad(&quant, "Enter a 2 digit number", 2);
    gui_keyboard(&str, "This lets you enter text", quant);

    /* box selection GUI */
    int stor, box, slot;
    gui_boxes(&stor, &box, &slot);

    /* PC pkm editing */
    char pkm[260];
    box = 0;
    slot = 0;
    sav_box_decrypt();
    sav_get_pkx(pkm, box, slot);
    /* edits to boxed Pokemon go here */
    sav_inject_pkx(pkm, GEN_SEVEN, box, slot);
    sav_box_encrypt();

    // party editing
    party_get_pkx(pkm, slot);
    /* edits go here... */
    party_inject_pkx(pkm, GEN_SEVEN, slot);

    return 0;
}
