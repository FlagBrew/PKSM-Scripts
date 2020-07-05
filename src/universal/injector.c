#include <pksm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    unsigned char version         = *argv[0];
    struct directory* injectables = read_directory("/3ds/PKSM/inject");

    if (injectables->count == 0)
    {
        delete_directory(injectables);
        gui_warn("There are no files in \'/3ds/PKSM/inject\'!\nPlace Wonder Card or Pokemon files there");
        return 0;
    }

    int chosen = gui_menu_20x2("Choose a file to inject", injectables->count, injectables->files);
    char* extension = NULL;
    if (strlen(injectables->files[chosen]) > 3)
    {
        if (injectables->files[chosen][strlen(injectables->files[chosen]) - 4] == '.')
        {
            extension = injectables->files[chosen] + strlen(injectables->files[chosen]) - 3;
        }
        else if (strlen(injectables->files[chosen]) > 7 && injectables->files[chosen][strlen(injectables->files[chosen]) - 8] == '.')
        {
            extension = injectables->files[chosen] + strlen(injectables->files[chosen]) - 7;
        }
    }

    if ((int)extension && (!strcasecmp(extension, "pgt") || !strcasecmp(extension, "wc4") ||
                              !strcasecmp(extension, "pgf") || !strcasecmp(extension, "wc8") ||
                              !strcasecmp(extension, "wc6") || !strcasecmp(extension, "wc6full") ||
                              !strcasecmp(extension, "wc7") || !strcasecmp(extension, "wc7full") ||
                              !strcasecmp(extension, "wb7") || !strcasecmp(extension, "wb7full")))
    {
        FILE* file = fopen(injectables->files[chosen], "rb");
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* data = malloc(size);
        fread(data, size, size, file);
        fclose(file);

        int slot = sav_wcx_free_slot();

        if (!strncasecmp(extension, "pgt", 3) || !strncasecmp(extension, "wc4", 3))
        {
            sav_inject_wcx(data, GEN_FOUR, slot, extension[0] == 'w' || extension[0] == 'W');
        }
        else if (!strncasecmp(extension, "pgf", 3))
        {
            sav_inject_wcx(data, GEN_FIVE, slot, 0);
        }
        else if (!strncasecmp(extension, "wc6", 3))
        {
            sav_inject_wcx(data, GEN_SIX, slot, strlen(extension) > 3);
        }
        else if (!strncasecmp(extension, "wc7", 3))
        {
            sav_inject_wcx(data, GEN_SEVEN, slot, strlen(extension) > 3);
        }
        else if (!strncasecmp(extension, "wb7", 3))
        {
            sav_inject_wcx(data, GEN_LGPE, slot, strlen(extension) > 3);
        }
        else if (!strncasecmp(extension, "wc8", 3))
        {
            sav_inject_wcx(data, GEN_EIGHT, slot, 0);
        }

        free(data);
    }
    else if ((int)extension && (!strcasecmp(extension, "pk3") || !strcasecmp(extension, "ek3") ||
                                   !strcasecmp(extension, "pk4") || !strcasecmp(extension, "ek4") ||
                                   !strcasecmp(extension, "pk5") || !strcasecmp(extension, "ek5") ||
                                   !strcasecmp(extension, "pk6") || !strcasecmp(extension, "ek6") ||
                                   !strcasecmp(extension, "pk7") || !strcasecmp(extension, "ek7") ||
                                   !strcasecmp(extension, "pb7") || !strcasecmp(extension, "eb7") ||
                                   !strcasecmp(extension, "pk8") || !strcasecmp(extension, "ek8")))
    {
        sav_box_decrypt();
        int fromStorage = 0;
        int box         = 0;
        int slot        = 0;
        gui_warn("Choose a slot to inject to. Press B to cancel.");
        if (!gui_boxes(&fromStorage, &box, &slot, 0))
        {
            bool ekx   = true;
            FILE* file = fopen(injectables->files[chosen], "rb");
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char* data = malloc(size);
            fread(data, size, size, file);
            fclose(file);

            enum Generation gen;
            if ((extension[1] == 'b' || extension[1] == 'B') && extension[2] == '7')
            {
                gen = GEN_LGPE;
            }
            else if (extension[2] == '3')
            {
                gen = GEN_THREE;
            }
            else if (extension[2] == '4')
            {
                gen = GEN_FOUR;
            }
            else if (extension[2] == '5')
            {
                gen = GEN_FIVE;
            }
            else if (extension[2] == '6')
            {
                gen = GEN_SIX;
            }
            else if (extension[2] == '7')
            {
                gen = GEN_SEVEN;
            }
            else if (extension[2] == '8')
            {
                gen = GEN_EIGHT;
            }

            if (extension[0] == 'P' || extension[0] == 'p')
            {
                ekx = false;
            }
            if (ekx)
            {
                pkx_decrypt(data, gen, 0);
            }

            if (fromStorage)
            {
                bank_inject_pkx(data, gen, box, slot);
            }
            else
            {
                if (gen == GEN_LGPE && (version == 42 || version == 43))
                {
                    sav_inject_pkx(data, gen, box, slot, 0);
                }
                else if (gen != GEN_LGPE && version != 42 && version != 43)
                {
                    sav_inject_pkx(data, gen, box, slot, 0);
                }
            }

            free(data);
        }
        sav_box_encrypt();
    }
    else
    {
        gui_warn("Extension not recognized!");
    }

    delete_directory(injectables);
    return 0;
}
