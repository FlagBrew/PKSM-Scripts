#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int start = 0x1e7ff;
    int size = 0x15;
    for(int i = 1; i < 101; i++)
    {
        int ofs = start + (i * size);
        if (sav_get_byte(ofs, 0) != 0) {
            sav_set_byte(0x3d, ofs, 0);
        }
    }
    gui_warn("All Friend Safari slots\nunlocked and revealed");

    return 0;
}
