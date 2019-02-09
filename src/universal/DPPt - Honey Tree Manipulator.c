#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int gbo = sav_gbo();
    int TID, SID;
    int species[8] = {415, 412, 420, 265, 190, 214, 446, 446};
    char *treePokes[] = {
        "Combee", "Burmy", "Cherubi", "Wurmple",
        "Aipom", "Heracross", "Munchlax", "Munchlax"
    };
    unsigned short treeOffset = 0x72E4;
    int optNum = 8;
    int res[4];
    char* trees[] = {
        "Route 205 (Near Floaroma Town)", "Route 205 (Near Eterna City)", "Route 206 (Under Bike Path)",
        "Route 207", "Route 208 (Near Hearthome City)", "Route 209 (Near Hallowed Tower)", "Route 210 South (Near Café Cabin)",
        "Route 210 North (Near Wilma's House)", "Route 211 (Near Celestic Town)", "Route 212 (Near Hearthome City)",
        "Route 212 (Near Pastoria City)", "Route 213 (Near Pastoria City)", "Route 214 (Near Valor Lakefront)", "Route 215 (Near Café Cabin)",
        "Route 218 (Near Canalave City)", "Route 221 (Near Pal Park)", "Route 222 (Near Sunyshore City)", "Valley Windworks",
        "Eterna Forest (Exterior)", "Fuego Ironworks", "Floaroma Meadow (Near Honey Man)"
    };
    struct pkx pokes[8];
    int posdp[8] = {20, 21, 22, 25, 15, 24, 11, 35}, pospt[8] = {22, 12, 13, 11, 15, 25, 35, 0};

    switch (version)
    {
        case 10:
        case 11:
            TID = *(unsigned short*)(saveData + gbo + 0x74);
            SID = *(unsigned short*)(saveData + gbo + 0x76);
            struct pkx pokeDP[2];
            char *gameDP[] = {"Diamond", "Pearl"};
            pokeDP[0].species = 266; pokeDP[1].species = 268;
            pokeDP[0].form = 0; pokeDP[1].form = 0;
            int pokeGame = gui_menu_6x5("Which game are you using?", 2, &gameDP[0], &pokeDP[0], GEN_FOUR);
            if (pokeGame == 0) {
                species[6] = 266; treePokes[6] = "Silcoon";
            } else if (pokeGame == 1) {
                species[6] = 268; treePokes[6] = "Cascoon";
            }
            break;
        case 12:
            TID = *(unsigned short*)(saveData + gbo + 0x78);
            SID = *(unsigned short*)(saveData + gbo + 0x7A);
            treeOffset = 0x7F38;
            optNum--;
            break;
        default:
            gui_warn("This script is only meant for", "the Sinnoh games (DPPt)");
            return 1;
    }
    res[0] = (SID % 256) % 21; res[1] = (SID / 256) % 21; res[2] = (TID % 256) % 21; res[3] = (TID / 256) % 21;
    if (res[0] == res[1]) {res[1] = (res[1] + 1) % 21;}
    if (res[0] == res[2]) {res[2] = (res[2] + 1) % 21;}
    if (res[1] == res[2]) {res[2] = (res[2] + 1) % 21;}
    if (res[0] == res[3]) {res[3] = (res[3] + 1) % 21;}
    if (res[1] == res[3]) {res[3] = (res[3] + 1) % 21;}
    if (res[2] == res[3]) {res[3] = (res[3] + 1) % 21;}

    int treeChoice = gui_menu_20x2("Which Honey Tree to you \nwish to edit?", 21, &trees);
    if ((treeChoice != res[0]) && (treeChoice != res[1]) && (treeChoice != res[2]) && (treeChoice != res[3])) {
        optNum--;
    }
    unsigned short worktree = treeOffset + (8 * treeChoice);

    for (int i = 0; i < optNum; i++) {
        pokes[i].species = species[i];
        pokes[i].form = 0;
    }
    int pokePick = gui_menu_6x5("Choose Honey Tree Pokémon", optNum, &treePokes[0], &pokes[0], GEN_FOUR);
    char slot, group;
    switch (version) {
        case 10:
        case 11:
            group = posdp[pokePick] / 10;
            slot = posdp[pokePick] % 10;
            break;
        case 12:
            group = pospt[pokePick] / 10;
            slot = pospt[pokePick] % 10;
            break;
    }

    *(int *)(saveData + gbo + worktree) = 1080; saveData[gbo + worktree + 4] = slot; saveData[gbo + worktree + 5] = (group - 1);
    saveData[gbo + worktree + 6] = group; saveData[gbo + worktree + 7] = 3;

    char msg[35] = {'\0'};
    sprintf(&msg, "Your %s will be available", treePokes[pokePick]);
    gui_warn(msg, "for the next 12 hours");
    return 0;
}
