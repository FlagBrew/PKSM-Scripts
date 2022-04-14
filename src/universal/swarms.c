#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    struct pkx options[28];
    char *labels[28] = {0};
    int total, gbo = sav_gbo(), ofs = 0, winter = 0, current;
    int *list;
    enum Generation gen;

    // Swarm lists
    int dp[28] = {
         84, 263, 104, 299, 231, 206,
        209, 359, 325,  96, 225, 220,
        100,  83, 300, 177, 296,  98,
        327, 374,  16, 222, 283, 108,
        238, 309, 287,  81};
    int pt[22] = {
         84, 263, 104, 246, 231, 206,
        209, 325,  96, 225, 100,  83,
        300, 177, 296,  98, 327, 374,
        127, 222, 309, 287};
    int hgss[20] = {
        261, 343, 302, 369, 113, 366,
        211, 427, 370, 280, 193, 209,
        223, 333, 132, 183, 206, 401,
        278, 340};
    int ss[2] = {317, 303}; // SS exclusives (Gulpin, Mawile)
    int w[17] = {
         83, 360, 314, 449, 235, 312,
        161, 453, 261, 236,  46,  84,
        353, 193,  56, 204, 102};
    int b[17] = {
         83, 360, 313, 449, 235, 311,
        161, 453, 228, 236, 285,  84,
        353, 193,  56, 204, 102};
    int w2[19] = {
         83,  97, 312, 317, 450, 177,
        162,  84, 195, 284, 277,  79,
         22, 204, 187, 332, 314, 122,
        166};
    int b2[19] = {
         83,  97, 311, 313, 317, 450,
        177, 162,  84, 195, 284, 277,
         79,  22, 204, 187, 332, 185,
        168};

    switch (version)
    {
        case 10:
        case 11:
            list = dp;
            total = 28;
            ofs = 0x72d4;
            gen = GEN_FOUR;
            break;
        case 12:
            list = pt;
            total = 22;
            ofs = 0x7f28;
            gen = GEN_FOUR;
            break;
        case 7:
        case 8:
            list = hgss;
            total = 20;
            ofs = 0x68a8;
            gen = GEN_FOUR;
            break;
        case 20:
            list = w;
            total = 17;
            winter = 453;
            ofs = 0x21b30;
            gen = GEN_FIVE;
            break;
        case 21:
            list = b;
            total = 17;
            winter = 453;
            ofs = 0x21b30;
            gen = GEN_FIVE;
            break;
        case 22:
            list = w2;
            total = 19;
            winter = 195;
            ofs = 0x2192c;
            gen = GEN_FIVE;
            break;
        case 23:
            list = b2;
            total = 19;
            winter = 195;
            ofs = 0x2192c;
            gen = GEN_FIVE;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    char tempStr[2][33] = {'\0', '\0'};
    char msg[66] = {'\0'};
    for (int i = 0; i < total; i++)
    {
        options[i].species = list[i];
        options[i].form = 0;
        if ((version == 7 || version == 8) && (i == 1 || i == 2))
        {
            sprintf(tempStr[i - 1], "%s (HG)\n%s (SS)", i18n_species(list[i]), i18n_species(ss[i - 1]));
            labels[i] = tempStr[i - 1];
        }
        else
        {
            labels[i] = i18n_species(list[i]);
        }
    }

    if (gen == GEN_FOUR)
    {
        current = sav_get_int(gbo, ofs) % total;
    }
    else if (gen == GEN_FIVE)
    {
        current = sav_get_byte(0, ofs) % total;
    }
    sprintf(msg, "Choose swarming species\n\nCurrent:\n%s", labels[current]);

    int choice = gui_menu_6x5(msg, total, labels, options, gen);
    if (gen == GEN_FIVE && options[choice].species == winter)
    {
        gui_warn("Unova Route 8 is frozen over\nduring winter preventing encounters");
    }
    if (gen == GEN_FOUR)
    {
        sav_set_int(choice, gbo, ofs);
    }
    else
    {
        sav_set_byte(choice, 0, ofs);
    }
    return 0;
}
