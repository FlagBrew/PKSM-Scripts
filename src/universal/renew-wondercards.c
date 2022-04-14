#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned char version = *argv[0];
    int offset;

    switch (version)
    {
        case 24:
        case 25:
            offset = 0x1BD00;
            break;
        case 26:
        case 27:
            offset = 0x1CD00;
            break;
        case 30:
        case 31:
            offset = 0x65D00;
            break;
        case 32:
        case 33:
            offset = 0x66300;
            break;
        default:
            gui_warn("Renewing Wonder Cards not supported\nfor this game");
            return 1;
    }

    int wc_size = 0x108, ofs_renew = 0x52;
    int wc_count = sav_wcx_free_slot();

    for (int i = 0; i < wc_count; i++)
    {
        sav_set_byte(1, offset, i * wc_size + ofs_renew);
    }

    gui_warn("All injected Wonder Cards have been renewed.\nVisit the delivery person in-game\nto reclaim your gift(s).");
    return 0;
}
