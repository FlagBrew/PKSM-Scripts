#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    struct pkx options[28];
    char *optionLabels[28] = {0};
    int totalOptions;
    enum Generation gen;
    int ofs = 0;
    int winter = 0;

    switch (version)
    {
    case 10:
    case 11:
        int dpSpecies[28] = {
            84, 263, 104, 299, 231, 206,
            209, 359, 325, 96, 225, 220,
            100, 83, 300, 177, 296, 98,
            327, 374, 16, 222, 283, 108,
            238, 309, 287, 81};
        char *dpNames[] = {
            "Doduo", "Zigzagoon", "Cubone", "Nosepass", "Phanpy", "Dunsparce",
            "Snubbull", "Absol", "Spoink", "Drowzee", "Delibird", "Swinub",
            "Voltorb", "Farfetch'd", "Skitty", "Natu", "Makuhita", "Krabby",
            "Spinda", "Beldum", "Pidgey", "Corsola", "Surskit", "Lickitung",
            "Smoochum", "Electrike", "Slakoth", "Magnemite"};
        for (totalOptions = 0; totalOptions < 28; totalOptions++)
        {
            options[totalOptions].species = dpSpecies[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = dpNames[totalOptions];
        }
        ofs = sav_gbo() + 0x72d4;
        gen = GEN_FOUR;
        break;
    case 12:
        int ptSpecies[22] = {
            84, 263, 104, 246, 231, 206,
            209, 325, 96, 225, 100, 83,
            300, 177, 296, 98, 327, 374,
            127, 222, 309, 287};
        char *ptNames[] = {
            "Doduo", "Zigzagoon", "Cubone", "Larvitar", "Phanpy", "Dunsparce",
            "Snubbull", "Spoink", "Drowzee", "Delibird", "Voltorb", "Farfetch'd",
            "Skitty", "Natu", "Makuhita", "Krabby", "Spinda", "Beldum",
            "Pinsir", "Corsola", "Electrike", "Slakoth"};
        for (totalOptions = 0; totalOptions < 22; totalOptions++)
        {
            options[totalOptions].species = ptSpecies[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = ptNames[totalOptions];
        }
        ofs = sav_gbo() + 0x7f28;
        totalOptions = 22;
        gen = GEN_FOUR;
        break;
    case 7:
    case 8:
        int hgssSpecies[20] = {
            261, 343, 302, 369, 113, 366,
            211, 427, 370, 280, 193, 209,
            223, 333, 132, 183, 206, 401,
            278, 340};
        char *hgssNames[] = {
            "Poochyena", "Baltoy / Gulpin", "Sableye / Mawile", "Relicanth", "Chansey", "Clamperl",
            "Qwilfish", "Buneary", "Luvdisc", "Ralts", "Yanma", "Snubbull",
            "Remoraid", "Swablu", "Ditto", "Marill", "Dunsparce", "Kricketot",
            "Wingull", "Whiscash"};
        for (totalOptions = 0; totalOptions < 20; totalOptions++)
        {
            options[totalOptions].species = hgssSpecies[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = hgssNames[totalOptions];
        }
        ofs = sav_gbo() + 0x68a8;
        gen = GEN_FOUR;
        break;
    case 20:
        int wSpecies[17] = {
            83, 360, 314, 449, 235, 312,
            161, 453, 261, 236, 46, 84,
            353, 193, 56, 204, 102};
        char *wNames[] = {
            "Farfetch'd", "Wynaut", "Illumise", "Hippopotas", "Smeargle", "Minun",
            "Sentret", "Croagunk", "Poochyena", "Tyrogue", "Paras", "Doduo",
            "Shuppet", "Yanma", "Mankey", "Pineco", "Exeggcute"};
        for (totalOptions = 0; totalOptions < 17; totalOptions++)
        {
            options[totalOptions].species = wSpecies[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = wNames[totalOptions];
        }
        winter = 453;
        ofs = 0x21b30;
        gen = GEN_FIVE;
        break;
    case 21:
        int bSpecies[17] = {
            83, 360, 313, 449, 235, 311,
            161, 453, 228, 236, 285, 84,
            353, 193, 56, 204, 102};
        char *bNames[] = {
            "Farfetch'd", "Wynaut", "Volbeat", "Hippopotas", "Smeargle", "Plusle",
            "Sentret", "Croagunk", "Houndour", "Tyrogue", "Shroomish", "Doduo",
            "Shuppet", "Yanma", "Mankey", "Pineco", "Exeggcute"};
        for (totalOptions = 0; totalOptions < 17; totalOptions++)
        {
            options[totalOptions].species = bSpecies[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = bNames[totalOptions];
        }
        winter = 453;
        ofs = 0x21b30;
        gen = GEN_FIVE;
        break;
    case 22:
        int w2Species[19] = {
            83, 97, 312, 314, 317, 450,
            177, 162, 84, 195, 284, 277,
            79, 22, 204, 187, 332, 122,
            166};
        char *w2Names[] = {
            "Farfetch'd", "Hypno", "Minun", "Illumise", "Swalot", "Hippowdon",
            "Natu", "Furret", "Doduo", "Quagsire", "Masquerain", "Swellow",
            "Slowpoke", "Fearow", "Pineco", "Hoppip", "Cacturne", "Mr. Mime",
            "Ledian"};
        for (totalOptions = 0; totalOptions < 19; totalOptions++)
        {
            options[totalOptions].species = w2Species[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = w2Names[totalOptions];
        }
        winter = 195;
        ofs = 0x2192c;
        gen = GEN_FIVE;
        break;
    case 23:
        int b2Species[19] = {
            83, 97, 311, 313, 317, 450,
            177, 162, 84, 195, 284, 277,
            79, 22, 204, 187, 332, 185,
            168};
        char *b2Names[] = {
            "Farfetch'd", "Hypno", "Plusle", "Volbeat", "Swalot", "Hippowdon",
            "Natu", "Furret", "Doduo", "Quagsire", "Masquerain", "Swellow",
            "Slowpoke", "Fearow", "Pineco", "Hoppip", "Cacturne", "Sudowoodo",
            "Ariados"};
        for (totalOptions = 0; totalOptions < 19; totalOptions++)
        {
            options[totalOptions].species = b2Species[totalOptions];
            options[totalOptions].form = 0;
            optionLabels[totalOptions] = b2Names[totalOptions];
        }
        winter = 195;
        ofs = 0x2192c;
        gen = GEN_FIVE;
        break;
    default:
        gui_warn("This script doesn't work", "on this game.");
        return 1;
    }

    int choice = gui_menu_6x5("Choose swarming species", totalOptions, &optionLabels[0], &options[0], gen);
    if (gen == GEN_FIVE && options[choice].species == winter)
    {
        gui_warn("Unova Route 8 is frozen over", "during winter preventing encounters");
    }
    if (gen == GEN_FOUR)
    {
        *(int *)(saveData + ofs) = choice;
    }
    else
    {
        saveData[ofs] = (char)choice;
    }
    return 0;
}
