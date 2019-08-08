#include <stdio.h>
#include <stdlib.h>
#include <pksm.h>



void deleteFile(char *dir)
{
    struct directory *folder = read_directory(dir);
    int file = gui_menu_20x2("Please select the script\nyou wish to delete!", (*folder).count, (*folder).files);
    int confirmDelete = gui_choice("Do you wish to delete the following file/folder?", (*folder).files[file]);
    if(confirmDelete)
    {
        remove((*folder).files[file]);
        gui_warn("The file has been deleted!", "");
    }
    delete_directory(folder);
    return;
}

int main(int argc, char **argv)
{
    int loop = 1;
    int sameDir = 0;
    int firstRun = 1;
    int f;
    struct directory *folder;
    while(1)
    {
        if(sameDir)
        {
            deleteFile((*folder).files[f]);
        } else 
        {
            if(firstRun)
            {
                firstRun = 0;
            } else 
            {
                delete_directory(folder);
            }
            folder = read_directory("/3ds/pksm/scripts");
            f = gui_menu_20x2("Please select the folder\nyou wish to delete from!", (*folder).count, (*folder).files);
            deleteFile((*folder).files[f]);
        }
        loop = gui_choice("Do you want to delete another file/folder?", "");
        if(!loop) break;
        sameDir = gui_choice("Do you want to use the same directory?", "");
    }
    return 0;
}
