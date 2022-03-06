#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deleteFile(char* dir)
{
    struct directory* folder = read_directory(dir);
    int file                 = gui_menu_20x2(
        "Please select the script\nyou wish to delete!", (*folder).count, (*folder).files);
    char* data = malloc(48 + 1 + strlen((*folder).files[file]) + 1);
    sprintf(data, "Do you wish to delete the following file/folder?\n%s", (*folder).files[file]);
    int confirmDelete = gui_choice(data);
    if (confirmDelete)
    {
        remove((*folder).files[file]);
        gui_warn("The file has been deleted!");
    }
    delete_directory(folder);
    free(data);
    return;
}

int main(int argc, char** argv)
{
    int loop     = 1;
    int sameDir  = 0;
    int firstRun = 1;
    int f;
    struct directory* folder = NULL;
    while (1)
    {
        if (sameDir)
        {
            deleteFile((*folder).files[f]);
        }
        else
        {
            if (folder != NULL)
            {
                delete_directory(folder);
                folder = NULL;
            }
            folder = read_directory("/3ds/pksm/scripts");
            f = gui_menu_20x2("Please select the folder\nyou wish to delete from!", (*folder).count,
                (*folder).files);
            deleteFile((*folder).files[f]);
        }
        loop = gui_choice("Do you want to delete another file/folder?");
        if (!loop)
            break;
        sameDir = gui_choice("Do you want to use the same directory?");
    }

    if (folder != NULL)
    {
        delete_directory(folder);
    }
    return 0;
}
