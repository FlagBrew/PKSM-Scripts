#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);

    int start = 0x1e7ff;
    int size = 0x15;
    for(int i = 1; i < 101; i++)
    {
        int ofs = start + (i * size);
        if (saveData[ofs] != 0) {
            saveData[ofs] = 0x3d;
        }
    }
    gui_warn("All Friend Safari slots", "unlocked and revealed");

    return 0;
}
