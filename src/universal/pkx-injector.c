#include <pksm.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned char version = *argv[2];
    struct directory* pkxFiles = read_directory("/3ds/PKSM/inject");
    int box = 0;
    int slot = 0;
    sav_box_decrypt();
    for (int i = 0; i < pkxFiles->count; i++)
    {
        int numChars = strlen(pkxFiles->files[i]);
        bool ekx = true;
        FILE* file = fopen(pkxFiles->files[i], "rb");
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* data = malloc(size);
        fread(data, size, size, file);
        fclose(file);

        if (pkxFiles->files[i][numChars - 3] == 'P' || pkxFiles->files[i][numChars - 3] == 'p')
        {
            ekx = false;
        }
        if (version == 42 || version == 43)
        {
            if ((pkxFiles->files[i][numChars - 2] == 'b' || pkxFiles->files[i][numChars - 2] == 'B') && (version == 42 || version == 43))
            {
                if (ekx)
                {
                    pkx_decrypt(data, GEN_LGPE);
                    sav_inject_pkx(data, GEN_LGPE, box, slot, 0);
                }
                else
                {
                    sav_inject_pkx(data, GEN_LGPE, box, slot, 0);
                }
            }
        }
        else
        {
            if (pkxFiles->files[i][numChars - 1] == '7' && pkxFiles->files[i][numChars - 2] != 'b' && pkxFiles->files[i][numChars - 2] != 'B')
            {
                if (ekx)
                {
                    pkx_decrypt(data, GEN_SEVEN);
                    sav_inject_pkx(data, GEN_SEVEN, box, slot, 0);
                }
                else
                {
                    sav_inject_pkx(data, GEN_SEVEN, box, slot, 0);
                }
            }
            else if (pkxFiles->files[i][numChars - 1] == '6')
            {
                if (ekx)
                {
                    pkx_decrypt(data, GEN_SIX);
                    sav_inject_pkx(data, GEN_SIX, box, slot, 0);
                }
                else
                {
                    sav_inject_pkx(data, GEN_SIX, box, slot, 0);
                }
            }
            else if (pkxFiles->files[i][numChars - 1] == '5')
            {
                if (ekx)
                {
                    pkx_decrypt(data, GEN_FIVE);
                    sav_inject_pkx(data, GEN_FIVE, box, slot, 0);
                }
                else
                {
                    sav_inject_pkx(data, GEN_FIVE, box, slot, 0);
                }
            }
            else if (pkxFiles->files[i][numChars - 1] == '4')
            {
                if (ekx)
                {
                    pkx_decrypt(data, GEN_FOUR);
                    sav_inject_pkx(data, GEN_FOUR, box, slot, 0);
                }
                else
                {
                    sav_inject_pkx(data, GEN_FOUR, box, slot, 0);
                }
            }
        }

        if (slot < 29)
        {
            slot++;
        }
        else
        {
            slot = 0;
            box++;
        }

        free(data);
    }
    
    delete_directory(pkxFiles);
    sav_box_encrypt();
    return 0;
}
