#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    unsigned short tid, sid;
    char m[4] = {0}, opts = 8, game;
    int ofsHoney = sav_gbo(),
        specNums[8] = {415, 412, 420, 265, 190, 214, 446, 446},
        pos[2][4][6] = {
            {{0, 0, 0, 0, 0, 0},
             {265, 266, 415, 412, 420, 190},
             {415, 412, 420, 190, 214, 265},
             {446, 446, 446, 446, 446, 446}},
            {{0, 0, 0, 0, 0, 0},
             {415, 265, 412, 420, 190, 190},
             {412, 420, 415, 190, 190, 214},
             {446, 446, 446, 446, 446, 446}}};
    char *treeNames[] = {
        " Route 205\n(Floaroma)", " Route 205\n(Eterna)", " Route 206", " Route 207",
        " Route 208", " Route 209", " Route 210\n(Solaceon)", " Route 210\n(Celestic)",
        " Route 211", " Route 212\n(Hearthome)", " Route 212\n(Pastoria)", " Route 213",
        " Route 214", " Route 215", " Route 218", " Route 221", " Route 222",
        " Valley\nWindworks", " Eterna Forest\n(Exterior)", " Fuego\nIronworks",
        " Floaroma\nMeadow", "Exit script"};

    switch (version)
    {
    case 10:
    case 11:
        tid = sav_get_short(ofsHoney, 0x74);
        sid = sav_get_short(ofsHoney, 0x76);
        ofsHoney += 0x72E4;
        specNums[6] = 266;
        game = 0;
        break;
    case 12:
        tid = sav_get_short(ofsHoney, 0x78);
        sid = sav_get_short(ofsHoney, 0x7A);
        ofsHoney += 0x7F38;
        opts = 7;
        game = 1;
        break;
    default:
        gui_warn("This script is only meant for\nthe Sinnoh games (DPPt)");
        return 1;
    }

    struct pkx treePkm[22];
    struct pkx pkmPkxs[8];
    char *optNames[8];
    int tree, pkm = 0, ofsTree, edit = 0, group, slot;

    /* determine Munchlax trees */
    m[0] = (sid % 256) % 21; m[1] = (sid / 256) % 21; m[2] = (tid % 256) % 21; m[3] = (tid / 256) % 21;
    if (m[0] == m[1]) { m[1] = (m[1] + 1) % 21; }
    if (m[0] == m[2]) { m[2] = (m[2] + 1) % 21; }
    if (m[0] == m[3]) { m[3] = (m[3] + 1) % 21; }
    if (m[1] == m[2]) { m[2] = (m[2] + 1) % 21; }
    if (m[1] == m[3]) { m[3] = (m[3] + 1) % 21; }
    if (m[2] == m[3]) { m[3] = (m[3] + 1) % 21; }
    for (tree = 0; tree < 4; tree++)
    {
        treeNames[m[tree]][0] = '*';
    }

    for (tree = 0; tree < 21; tree++)
    {
        ofsTree = ofsHoney + 8 * tree;
        treePkm[tree].species = pos[game][sav_get_byte(ofsTree, 6)][sav_get_byte(ofsTree, 4)];
        treePkm[tree].form = 0;
    }
    treePkm[21].species = 0;
    treePkm[21].form = 0;
    for (pkm = 0; pkm < opts; pkm++)
    {
        pkmPkxs[pkm].species = specNums[pkm];
        pkmPkxs[pkm].form = 0;
        if (specNums[pkm] == 266)
        {
            char temp[30];
            sprintf(temp, "%s (D)\n%s (P)", i18n_species(266), i18n_species(268));
            optNames[pkm] = temp;
        }
        else
        {
            optNames[pkm] = i18n_species(specNums[pkm]);
        }
    }

    tree = gui_menu_6x5("Edit which Honey Tree?\n* = Munchlax tree", 22, treeNames, treePkm, GEN_FOUR);
    while (tree < 21)
    {
        edit++;
        pkm = gui_menu_6x5("Choose Honey Tree Pokémon", opts - (treeNames[tree][0] != '*'), optNames, pkmPkxs, GEN_FOUR);
        treePkm[tree].species = specNums[pkm];

        ofsTree = ofsHoney + 8 * tree;
        sav_set_int(1080, ofsTree, 0);
        sav_set_byte(3, ofsTree, 7); // shake
        for (group = 1; group < 4; group++)
        {
            for (slot = 0; slot < 6; slot++)
            {
                if (pos[game][group][slot] == specNums[pkm])
                {
                    sav_set_byte(slot, ofsTree, 4); // slot (within group)
                    sav_set_byte(group - 1, ofsTree, 5); // subtable (always == group - 1)
                    sav_set_byte(group, ofsTree, 6); // group
                    break;
                }
            }
        }

        tree = gui_menu_6x5("Edit which Honey Tree?\n* = Munchlax tree", 22, treeNames, treePkm, GEN_FOUR);
    }
    if (edit > 0)
    {
        gui_warn("All edits made will last for\n18 hours from time of last save");
    }

    return 0;
}
