#include <pksm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** checkOnlineID(version, saveData)
 * Online IDs
 *
 * XY/ORAS
 *  GameSync
 *      offset: 0x14008
 *      bytes: 8
 *
 * SM
 *  GameSync
 *      offset: 0x1210
 *      bytes: 8
 *  NexUniqueID
 *      offset: 0x1218
 *      bytes: 16
 *  FestaID
 *      offset: 0x1228
 *      bytes: 4
 *
 * USUM
 *  GameSync
 *      offset: 0x1410
 *      bytes: 8
 *  NexUniqueID
 *      offset: 0x1418
 *      bytes: 16
 *  FestaID
 *      id[0:4]
 *          offset: 0x1428
 *          bytes: 4
 *      id[5:11]
 *          offset: 0x1418
 *          bytes: 8
 */
int checkOnlineID(int version)
{
    int ofsSyncID = 0, sizeSyncID = 0, i;
    switch (version)
    {
        case 24:
        case 25:
        case 26:
        case 27:
            ofsSyncID = 0x14008;
            sizeSyncID = 8;
            break;
        case 30:
        case 31:
            ofsSyncID = 0x1210;
            sizeSyncID = 8;
            break;
        case 32:
        case 33:
            ofsSyncID = 0x1410;
            sizeSyncID = 8;
            break;
        default:
            return 0;
    }

    // ???: (Gen 7) check NexUniqueID and/or FestaID?
    for (i = 0; i < sizeSyncID; i++)
    {
        if (sav_get_byte(ofsSyncID, i) != 0)
        {
            return 1;
        }
    }
    return 0;
}

void clearSyncID(int version)
{
    int ofsSyncID = 0, i;
    switch (version)
    {
        case 24:
        case 25:
        case 26:
        case 27:
            ofsSyncID = 0x14008;
            break;
        case 30:
        case 31:
            ofsSyncID = 0x1210;
            break;
        case 32:
        case 33:
            ofsSyncID = 0x1410;
            break;
        default:
            return;
    }

    for (i = 0; i < 8; i++)
    {
        sav_set_byte(0, ofsSyncID, i);
    }
}

void generateSyncID(int version)
{
    int ofsSyncID = 0, i;
    switch (version)
    {
        case 24:
        case 25:
        case 26:
        case 27:
            ofsSyncID = 0x14008;
            break;
        case 30:
        case 31:
            ofsSyncID = 0x1210;
            break;
        case 32:
        case 33:
            ofsSyncID = 0x1410;
            break;
        default:
            return;
    }
    for (i = 0; i < 8; i++)
    {
        sav_set_byte(rand()%255, ofsSyncID, i);
    }
}


int main(int argc, char **argv)
{
    // Seed the RNG
    srand(time(0))
    unsigned char version = *argv[0];
    unsigned int gbo = sav_gbo(), ofsTID = 0, ofsName = 0;

    switch (version)
    {
        case 24: // X
        case 25: // Y
        case 26: // AS
        case 27: // OR
            ofsName = 0x14048; // trainer nickname: 0x14062
            ofsTID = 0x14000;
            break;
        case 30: // S
        case 31: // M
            ofsName = 0x1238;
            ofsTID = 0x1200;
            break;
        case 32: // US
        case 33: // UM
            ofsName = 0x1438;
            ofsTID = 0x1400;
            break;
        default:
            gui_warn("This script doesn't work\non this game.");
            return 1;
    }

    // check for (and possibly remove) GameSync ID
    if (checkOnlineID(version))
    {
        gui_warn("GameSync ID found.\nEditing trainer info may get you banned.");
        if (gui_choice("Exit script without editing (A)\nor remove GameSync ID and continue (B)"))
        {
            return 1;
        }
        /* remove GameSync ID */
        clearSyncID(version);
        gui_warn("Beware: GameSync ID may not be the\nonly thing looked at by online checks");
    }
    else {
        gui_warn("No GameSync ID Found.");
        if (gui_choice("Exit script without editing (A)\nor generate GameSync ID and continue (B)"))
        {
            return 1;
        }
        
    }

    return 0;
}
