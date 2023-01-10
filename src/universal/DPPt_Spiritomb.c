#include <pksm.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    int ofsKeystone, ofsGreets, gbo = sav_gbo();
    switch (version)
    {
    case 10:
    case 11:
        ofsGreets = 0xE18;
        ofsKeystone = 0xEB0;
        break;
    case 12:
        ofsKeystone = 0xE28;
        ofsGreets = 0xEC0;
        break;
    default:
        gui_warn("This script only works on DP/Pt.");
        return 0;
    }
    if (sav_get_short(gbo, ofsKeystone) == 0)
    {
        sav_set_short(1, gbo, ofsKeystone);
    }
    if (sav_get_short(gbo, ofsGreets) < 32)
    {
        sav_set_short(32, gbo, ofsGreets);
    }
    gui_warn("Spiritomb can now be encountered\non Route 209.");
    return 0;
}
