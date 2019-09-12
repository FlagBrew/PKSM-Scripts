#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    struct pkx options[28];
    char *labels[28] = {0};
    int total, ofs = 0, winter = 0;
    enum Generation gen;

    switch (version)
    {
        case 10:
        case 11:
            int dp[28] = {
                84, 263, 104, 299, 231, 206,
                209, 359, 325, 96, 225, 220,
                100, 83, 300, 177, 296, 98,
                327, 374, 16, 222, 283, 108,
                238, 309, 287, 81};
            for (total = 0; total < 28; total++)
            {
                options[total].species = dp[total];
                options[total].form = 0;
                labels[total] = i18n_species(dp[total]);
            }
            ofs = sav_gbo() + 0x72d4;
            gen = GEN_FOUR;
            break;
        case 12:
            int pt[22] = {
                84, 263, 104, 246, 231, 206,
                209, 325, 96, 225, 100, 83,
                300, 177, 296, 98, 327, 374,
                127, 222, 309, 287};
            for (total = 0; total < 22; total++)
            {
                options[total].species = pt[total];
                options[total].form = 0;
                labels[total] = i18n_species(pt[total]);
            }
            ofs = sav_gbo() + 0x7f28;
            total = 22;
            gen = GEN_FOUR;
            break;
        case 7:
        case 8:
            int hgss[20] = {
                261, 343, 302, 369, 113, 366,
                211, 427, 370, 280, 193, 209,
                223, 333, 132, 183, 206, 401,
                278, 340};
            int ss[2] = {317, 303}; // SS exclusives (Gulpin, Mawile)
            char tempStr[2][33] = {'\0', '\0'};
            for (total = 0; total < 20; total++)
            {
                options[total].species = hgss[total];
                options[total].form = 0;
                if (total == 1 || total == 2) {
                    sprintf(tempStr[total - 1], "%s (HG)\n%s (SS)", i18n_species(hgss[total]), i18n_species(ss[total - 1]));
                    labels[total] = tempStr[total - 1];
                }
                else
                {
                    labels[total] = i18n_species(hgss[total]);
                }
            }
            ofs = sav_gbo() + 0x68a8;
            gen = GEN_FOUR;
            break;
        case 20:
            int w[17] = {
                83, 360, 314, 449, 235, 312,
                161, 453, 261, 236, 46, 84,
                353, 193, 56, 204, 102};
            for (total = 0; total < 17; total++)
            {
                options[total].species = w[total];
                options[total].form = 0;
                labels[total] = i18n_species(w[total]);
            }
            winter = 453;
            ofs = 0x21b30;
            gen = GEN_FIVE;
            break;
        case 21:
            int b[17] = {
                83, 360, 313, 449, 235, 311,
                161, 453, 228, 236, 285, 84,
                353, 193, 56, 204, 102};
            for (total = 0; total < 17; total++)
            {
                options[total].species = b[total];
                options[total].form = 0;
                labels[total] = i18n_species(b[total]);
            }
            winter = 453;
            ofs = 0x21b30;
            gen = GEN_FIVE;
            break;
        case 22:
            int w2[19] = {
                83, 97, 312, 314, 317, 450,
                177, 162, 84, 195, 284, 277,
                79, 22, 204, 187, 332, 122,
                166};
            for (total = 0; total < 19; total++)
            {
                options[total].species = w2[total];
                options[total].form = 0;
                labels[total] = i18n_species(w2[total]);
            }
            winter = 195;
            ofs = 0x2192c;
            gen = GEN_FIVE;
            break;
        case 23:
            int b2[19] = {
                83, 97, 311, 313, 317, 450,
                177, 162, 84, 195, 284, 277,
                79, 22, 204, 187, 332, 185,
                168};
            for (total = 0; total < 19; total++)
            {
                options[total].species = b2[total];
                options[total].form = 0;
                labels[total] = i18n_species(b2[total]);
            }
            winter = 195;
            ofs = 0x2192c;
            gen = GEN_FIVE;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    int choice = gui_menu_6x5("Choose swarming species", total, labels, options, gen);
    if (gen == GEN_FIVE && options[choice].species == winter)
    {
        gui_warn("Unova Route 8 is frozen over\nduring winter preventing encounters");
    }
    if (gen == GEN_FOUR)
    {
        *(int *)(saveData + sav_gbo() + ofs) = choice;
    }
    else
    {
        saveData[ofs] = (char)choice;
    }
    return 0;
}
