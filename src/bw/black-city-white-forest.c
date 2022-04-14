#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int ofs = 0x1fa08,
        ofsRes, i, slot, choice, opts,
        current[21];
    short species[2][31] = {
        {16, 265, 92, 187, 239, 175,
         66, 287, 403, 240, 81, 280,
         396, 298, 406, 43, 179, 304,
         69, 273, 111, 270, 328, 63,
         32, 29, 293, 137, 440, 371,
         0},
        {18, 267, 94, 189, 466, 468,
         68, 289, 405, 467, 462, 282,
         398, 184, 407, 45, 181, 306,
         71, 275, 464, 272, 330, 65,
         34, 31, 295, 474, 242, 373,
         0}};
    char game = version == 21,
         present,
         *trainers[] = {
             "Leo", "Silvia", "Dave", "Britney", "Robbie", "Miki",
             "Ryder", "Karenna", "Doug", "Vincent", "Marie", "Lena",
             "Carlos", "Molly", "Frederic", "Lynette", "Pierce", "Gene",
             "Piper", "Miho", "Shane", "Ralph", "Eliza", "Collin",
             "Ken", "Jacques", "Rosa", "Herman", "Emi", "Grace",
             "none"},
         *slots[] = {
             "Front 1", "Front 2", "Front 3", "Front 4", "Front 5", "Front 6",
             "Front 7", "Front 8", "Front 9", "Front 10", "Back 1", "Back 2",
             "Back 3", "Back 4", "Back 5", "Back 6", "Back 7", "Back 8",
             "Back 9", "Back 10", "Exit script"};
    struct pkx residents[21];
    struct pkx pkxOpts[62];

    for (i = 0; i < 30; i++)
    {
        // White Forest species
        pkxOpts[i].species = species[0][i];
        pkxOpts[i].form = 0;
        // Black City species
        pkxOpts[i + 31].species = species[1][i];
        pkxOpts[i + 31].form = 0;
    }
    // options for clearing slot
    pkxOpts[30].species = 0;
    pkxOpts[30].form = 0;
    pkxOpts[61].species = 0;
    pkxOpts[61].form = 0;

    // determine current slot contents
    for (slot = 0; slot < 20; slot++)
    {
        ofsRes = ofs + 0x18 * slot;
        // only add visible trainers
        if (sav_get_byte(ofsRes, 0))
        {
            current[slot] = sav_get_byte(ofsRes + 1, 0);
            residents[slot].species = species[game][current[slot]];
        }
        else
        {
            current[slot] = 30;
            residents[slot].species = 0;
        }
        residents[slot].form = 0;
        // toggle game before and after reading back slots
        if (slot % 10 == 9)
        {
            game ^= 1;
        }
    }
    residents[20].species = 0;
    residents[20].form = 0;

    slot = gui_menu_6x5("Edit which slot?\nBack = shareable", 21, slots, residents, GEN_FIVE);
    char message[29] = {0};
    while (slot < 20)
    {
        present = 0;
        // front slots match loaded save, back slots are opposite
        opts = (game ^ (slot > 9)) * 31;
        choice = gui_menu_6x5("Pick a resident\n\nNote: you can find a 'none'\noption by scrolling to\nthe second page", 31, trainers, &pkxOpts[opts], GEN_FIVE);

        // do not duplicate trainers
        if (choice < 30) {
            for(i = 0; i < 20; i++)
            {
                if (i != slot && current[i] == choice) {
                    present = 1;
                    sprintf(message, "%s\nis already present", trainers[choice]);
                    gui_warn(message);
                    memset(message, '\0', 29);
                    break;
                }
            }
        }

        if (present == 0) {
            current[slot] = choice;
            residents[slot].species = pkxOpts[opts + choice].species;
            ofsRes = ofs + slot * 0x18;
            sav_set_byte(choice < 30, ofsRes, 0); // resident presence
            sav_set_byte(choice % 30, ofsRes + 1, 0); // resident ID
            if (slot < 10) {
                // only set "stay" value for front slots
                sav_set_byte(100, ofsRes + 2, 0); // "stay" value
            }
        }

        slot = gui_menu_6x5("Edit which slot?\nBack = shareable", 21, slots, residents, GEN_FIVE);
    }

    return 0;
}
