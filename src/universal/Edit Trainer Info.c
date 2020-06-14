#include <pksm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union trainerID
{
    unsigned int u32;
    unsigned short u16[2];
};

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

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    unsigned int gbo = sav_gbo(), ofsTID = 0, ofsName = 0;
    char *fields[] = {
        "Exit script",
        "Trainer ID",
        "Secret ID",
        "Shiny Value (TSV)",
        "Trainer Name",
        "Trainer ID (internal)",
        "Secret ID (internal)"
    };

    switch (version)
    {
        case 7:  // HG
        case 8:  // SS
        case 10: // D
        case 11: // P
            ofsName = 0x64 + gbo;
            ofsTID = 0x74 + gbo;
            break;
        case 12: // PT
            ofsName = 0x68 + gbo;
            ofsTID = 0x78 + gbo;
            break;
        case 20: // W
        case 21: // B
        case 22: // W2
        case 23: // B2
            ofsName = 0x19404;
            ofsTID = 0x19414;
            break;
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

    unsigned int oldID = 0, newID = 0,
        tsvShift = 3 + (version > 23),
        tsvLimit = 0xFFFF >> tsvShift,
        nameLen16 = 0x10 + (version > 23) * 0xA,
        nameLen8 = nameLen16 + 0x8 + (version > 23) * 0x5,
        failedAlloc = 0;
    union trainerID id;
    id.u32 = sav_get_int(ofsTID, 0);

    char *oldName = malloc(nameLen8), *newName = malloc(nameLen8),
        *otName = malloc(nameLen8),
        *currentData = (char *)sav_get_value(SAV_OT_NAME);

    if (oldName == NULL || newName == NULL || otName == NULL)
    {
        failedAlloc = 1;
    }
    else
    {
        strcpy(otName, currentData);
        memset(oldName, '\0', nameLen8);
        memset(newName, '\0', nameLen8);
    }
    free(currentData);
    currentData = malloc(100);
    if (currentData == NULL)
    {
        gui_warn("An error occurred.\nPlease try running the script again");
        return -1;
    }

    int opts = 5 + 2 * (version > 27),
        changes = 0,
        choice = gui_menu_20x2("Edit which piece of trainer info?", opts, fields);
    while (choice != 0)
    {
        memset(currentData, '\0', 60);
        if (choice < 3 && version < 30)
        {
            choice += 4;
        }
        else if (version > 27 && choice != 4)
        {
            gui_warn("Editing this number may change more than\none of TID, SID, and TSV");
        }

        switch (choice)
        {
            case 1: // Gen 7 TID
                oldID = id.u32 % 1000000;
                id.u32 -= oldID;
                sprintf(currentData, "Enter a new TID (0-999999)\nCurrent G7 TID: %u", oldID);
                gui_warn(currentData);
                gui_numpad(&newID, "TID within range 0-999999", 6);
                sprintf(currentData, "TID set to %i", newID);
                gui_warn(currentData);
                id.u32 += newID;
                break;
            case 2: // Gen 7 SID
                oldID = id.u32 / 1000000;
                id.u32 %= 1000000;
                sprintf(currentData, "Enter a new SID (0-4294)\nCurrent G7 SID: %u", oldID);
                gui_warn(currentData);
                gui_numpad(&newID, "SID within range 0-4294", 4);
                newID %= 4295;
                sprintf(currentData, "TID set to %i", newID);
                gui_warn(currentData);
                id.u32 += newID * 1000000;
                break;
            case 3: // TSV
                oldID = (id.u16[0] ^ id.u16[1]) >> tsvShift;
                id.u16[1] &= (1 << tsvShift) - 1;
                if (version < 24)
                {
                    sprintf(currentData, "Enter a new TSV (0-8191)\nCurrent TSV: %i", oldID);
                    gui_warn(currentData);
                    gui_numpad(&newID, "TSV within range 0-8191", 4);
                }
                else
                {
                    sprintf(currentData, "Enter a new TSV (0-4095)\nCurrent TSV: %i", oldID);
                    gui_warn(currentData);
                    gui_numpad(&newID, "TSV within range 0-4095", 4);
                }
                newID &= tsvLimit;
                sprintf(currentData, "TSV set to %i", newID);
                gui_warn(currentData);
                id.u16[1] |= (newID << tsvShift) ^ id.u16[0];
                break;
            case 4: // OT name
                if (failedAlloc)
                {
                    gui_warn("Cannot change OT name due to script\nloading error. Try running script again");
                }
                else
                {
                    memset(oldName, '\0', nameLen8);
                    strcpy(oldName, otName);
                    sprintf(currentData, "Enter a new OT name\nCurrent OT name: %s", oldName);
                    gui_warn(currentData);
                    memset(newName, '\0', nameLen8);
                    gui_keyboard(newName, "Enter new OT name", nameLen16 / 2);
                    sprintf(currentData, "OT name set to %s", newName);
                    gui_warn(currentData);
                    memset(otName, '\0', nameLen8);
                    strcpy(otName, newName);
                }
                break;
            case 5: // u16 TID
                oldID = id.u16[0];
                id.u16[0] = 0;
                sprintf(currentData, "Enter a new TID (0-65535)\nCurrent TID: %i", oldID);
                gui_warn(currentData);
                gui_numpad(&newID, "TID within range 0-65535", 5);
                newID &= 0xFFFF;
                sprintf(currentData, "TID set to %i", newID);
                gui_warn(currentData);
                id.u16[0] = newID;
                break;
            case 6: // u16 SID
                oldID = id.u16[1];
                id.u16[1] = 0;
                sprintf(currentData, "Enter a new SID (0-65535)\nCurrent SID: %i", oldID);
                gui_warn(currentData);
                gui_numpad(&newID, "SID within range 0-65535", 5);
                newID &= 0xFFFF;
                sprintf(currentData, "SID set to %i", newID);
                gui_warn(currentData);
                id.u16[1] = newID;
                break;
            default:
                gui_warn("Impossible choice!\nPlease report this");
                break;
        }

        if (oldID != newID || strcmp(oldName, newName) != 0)
        {
            changes += 1;
        }
        choice = gui_menu_20x2("Edit which piece of trainer info?", opts, fields);
    }

    if (changes)
    {
        sav_set_int(id.u32, ofsTID, 0);
        if (!failedAlloc)
        {
            sav_set_string(otName, 0, ofsName, nameLen16 / 2);
        }
    }

    if (!failedAlloc)
    {
        free(oldName);
        free(newName);
        free(otName);
    }
    free(currentData);
    return 0;
}
