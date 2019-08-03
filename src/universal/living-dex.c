#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[2];
    enum Generation gen;

    int maxSpecies = 0;

    int shiny = gui_choice("Would you like your Pok\u00e1mon to be shiny?", NULL);

    switch (version)
    {
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen = GEN_FOUR;
            maxSpecies = 493;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen = GEN_FIVE;
            maxSpecies = 649;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen = GEN_SIX;
            maxSpecies = 721;
            break;
        case 30:
        case 31:
            gen = GEN_SEVEN;
            maxSpecies = 802;
            break;
        case 32:
        case 33:
            gen = GEN_SEVEN;
            maxSpecies = 807;
            break;
        case 42:
        case 43:
            gen = GEN_LGPE;
            break;
    }

    sav_box_decrypt();
    if (gen != GEN_LGPE)
    {
        char* data = malloc(pkx_box_size(gen));
        for (int i = 0; i < maxSpecies; i++)
        {
            pkx_generate(data, i + 1);
            pkx_set_shiny(data, gen, shiny);
            sav_inject_pkx(data, gen, i / 30, i % 30, 0);
        }
        free(data);
    }
    else
    {
        char* data = malloc(pkx_box_size(gen));
        for (int i = 0; i < 151; i++)
        {
            pkx_generate(data, i + 1);
            pkx_set_shiny(data, gen, shiny);
            sav_inject_pkx(data, gen, i / 30, i % 30, 0);
        }
        pkx_generate(data, 808);
        pkx_set_shiny(data, gen, shiny);
        sav_inject_pkx(data, gen, 151 / 30, 151 % 30, 0);
        pkx_generate(data, 809);
        pkx_set_shiny(data, gen, shiny);
        sav_inject_pkx(data, gen, 152 / 30, 152 % 30, 0);
        free(data);
    }
    sav_box_encrypt();
    return 0;
}
