#include <pksm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On the 3DS, fopen on a folder returns NULL, so a path we cannot open as a
// file is treated as a directory to navigate into.
int is_directory(char* path)
{
    FILE* file = fopen(path, "rb");
    if (file)
    {
        fclose(file);
        return 0;
    }
    return 1;
}

// Returns a pointer to the last path component (the part after the final '/').
char* base_name(char* path)
{
    int last = -1;
    for (int i = 0; path[i] != '\0'; i++)
    {
        if (path[i] == '/')
        {
            last = i;
        }
    }
    return path + last + 1;
}

// Trims the last path component in place, moving one level up.
void path_up(char* path)
{
    int last = -1;
    for (int i = 0; path[i] != '\0'; i++)
    {
        if (path[i] == '/')
        {
            last = i;
        }
    }
    if (last > 0)
    {
        path[last] = '\0';
    }
}

int main(int argc, char** argv)
{
    unsigned char version = *argv[0];

    char path[768];
    strcpy(path, "/3ds/PKSM/inject");

    struct directory* root = read_directory(path);
    int rootCount          = root->count;
    delete_directory(root);

    if (rootCount == 0)
    {
        gui_warn("There are no files in \'/3ds/PKSM/inject\'!\nPlace Wonder Card or Pokemon files there");
        return 0;
    }

    // Browse starting from the inject folder, descending into folders until a
    // file is chosen. chosenFile ends up holding the path of the picked file.
    char chosenFile[768];
    chosenFile[0] = '\0';

    while (chosenFile[0] == '\0')
    {
        struct directory* dir = read_directory(path);
        int atRoot            = !strcmp(path, "/3ds/PKSM/inject");

        // First entry navigates up (or cancels at the root), the rest are the
        // folder contents shown by name.
        int total     = dir->count + 1;
        char** labels = malloc(total * sizeof(char*));
        if (!labels)
        {
            delete_directory(dir);
            gui_warn("Out of memory.");
            return 0;
        }
        if (atRoot)
        {
            labels[0] = "[ Cancel ]";
        }
        else
        {
            labels[0] = "[ .. ]";
        }
        for (int i = 0; i < dir->count; i++)
        {
            labels[i + 1] = base_name(dir->files[i]);
        }

        int chosen = gui_menu_20x2("Choose a file to inject.\nSelect a folder to open it.", total, labels);
        free(labels);

        if (chosen <= 0)
        {
            delete_directory(dir);
            if (atRoot)
            {
                return 0;
            }
            path_up(path);
            continue;
        }

        if (strlen(dir->files[chosen - 1]) >= 768)
        {
            gui_warn("Path is too long to open.");
            delete_directory(dir);
            continue;
        }

        if (is_directory(dir->files[chosen - 1]))
        {
            strcpy(path, dir->files[chosen - 1]);
            delete_directory(dir);
            continue;
        }

        strcpy(chosenFile, dir->files[chosen - 1]);
        delete_directory(dir);
    }

    char* extension = NULL;
    if (strlen(chosenFile) > 3)
    {
        if (chosenFile[strlen(chosenFile) - 4] == '.')
        {
            extension = chosenFile + strlen(chosenFile) - 3;
        }
        else if (strlen(chosenFile) > 7 && chosenFile[strlen(chosenFile) - 8] == '.')
        {
            extension = chosenFile + strlen(chosenFile) - 7;
        }
    }

    if ((int)extension && (!strcasecmp(extension, "pgt") || !strcasecmp(extension, "wc4") ||
                              !strcasecmp(extension, "pgf") || !strcasecmp(extension, "wc8") ||
                              !strcasecmp(extension, "wc6") || !strcasecmp(extension, "wc6full") ||
                              !strcasecmp(extension, "wc7") || !strcasecmp(extension, "wc7full") ||
                              !strcasecmp(extension, "wb7") || !strcasecmp(extension, "wb7full")))
    {
        FILE* file = fopen(chosenFile, "rb");
        if (!file)
        {
            gui_warn("Could not open the selected file.");
            return 0;
        }
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* data = malloc(size);
        if (!data)
        {
            fclose(file);
            gui_warn("Out of memory.");
            return 0;
        }
        fread(data, 1, size, file);
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
    else if ((int)extension && ( !strcasecmp(extension, "pk1") || !strcasecmp(extension, "ek1") ||
                                   !strcasecmp(extension, "pk2") || !strcasecmp(extension, "ek2") ||
                                   !strcasecmp(extension, "pk3") || !strcasecmp(extension, "ek3") ||
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
            FILE* file = fopen(chosenFile, "rb");
            if (!file)
            {
                gui_warn("Could not open the selected file.");
                sav_box_encrypt();
                return 0;
            }
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char* data = malloc(size);
            if (!data)
            {
                fclose(file);
                gui_warn("Out of memory.");
                sav_box_encrypt();
                return 0;
            }
            fread(data, 1, size, file);
            fclose(file);

            enum Generation gen;
            if ((extension[1] == 'b' || extension[1] == 'B') && extension[2] == '7')
            {
                gen = GEN_LGPE;
            }
            else if (extension[2] == '1')
            {
                gen = GEN_ONE;
            }
            else if (extension[2] == '2')
            {
                gen = GEN_TWO;
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

    return 0;
}
