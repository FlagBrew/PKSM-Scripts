#include <pksm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union trainerID
{
    int u32;
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
int checkOnlineID(int version, unsigned char* saveData)
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
        if (saveData[ofsSyncID + i] != 0)
        {
            return 1;
        }
    }
    return 0;
}

void clearSyncID(int version, unsigned char* saveData)
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
        saveData[ofsSyncID + i] = 0;
    }
}

int main(int argc, char **argv)
{
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    unsigned int gbo = sav_gbo(), ofsTID = 0, ofsName = 0;
    char *fields[] = {
        "Exit script",
        "Trainer ID",
        "Secret ID",
        "Shiny Value (TSV)",
        "Trainer Name",
        "Trainer ID (internal)"
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
            gui_warn("This script doesn't work", "on this game.");
            return 1;
    }

    // check for (and possibly remove) GameSync ID
    if (checkOnlineID(version, saveData))
    {
        gui_warn("GameSync ID found.", "Editing trainer info may get you banned.");
        if (gui_choice("Exit script without editing (A)", "or remove GameSync ID and continue (B)"))
        {
            return 1;
        }
        /* remove GameSync ID */
        clearSyncID(version, saveData);
    }

    int oldID = 0, newID = 0,
        tsvShift = 3 + (version > 23),
        tsvLimit = 0xFFFF >> tsvShift,
        nameLen = (0x10 + (version > 23) * 0xA) * 1.5;
    union trainerID id;
    id.u32 = *(int *)(saveData + ofsTID);

    // TODO: properly declare string variables
    char *oldName = malloc(nameLen), *newName = malloc(nameLen),
    //     *otName = malloc(nameLen),
        currentData[100] = {'\0'}; // FIXME: use a more appropriate size
    // strcpy(otName, (char *)sav_get_value(SAV_OT_NAME));
    // memset(oldName, '\0', nameLen);
    // memset(newName, '\0', nameLen);

    //TODO: make sure strings allocated successfully

    int opts = 5 + (version > 27),
        changes = 0,
        choice = gui_menu_20x2("Edit which piece of trainer info?", opts, fields);
    while (choice != 0)
    {
        // memset(currentData, '\0', 100);
        if (choice == 1 && version < 30)
        {
            choice += 4;
        }
        else if (version > 27 && choice != 4)
        {
            gui_warn("Editing this number may change more than", "one of TID, SID, and TSV");
        }

        switch (choice)
        {
            case 1: // 6 digit TID
                oldID = id.u32 % 1000000;
                id.u32 -= oldID;
                sprintf(&currentData, "Current TID: %i", oldID);
                gui_warn("Enter a new TID (0-999999)", currentData);
                gui_numpad(&newID, "TID within range 0-999999", 6);
                sprintf(&currentData, "%i", newID);
                gui_warn("TID set to", currentData);
                id.u32 += newID;
                break;
            case 2: // SID
                oldID = id.u16[1];
                id.u16[1] = 0;
                sprintf(&currentData, "Current SID: %i", oldID);
                gui_warn("Enter a new SID (0-65535)", currentData);
                gui_numpad(&newID, "SID within range 0-65535", 5);
                newID &= 0xFFFF;
                sprintf(&currentData, "%i", newID);
                gui_warn("SID set to", currentData);
                id.u16[1] = newID;
                break;
            case 3: // TSV
                oldID = (id.u16[0] ^ id.u16[1]) >> tsvShift;
                id.u16[1] &= (1 << tsvShift) - 1;
                sprintf(&currentData, "Current TSV: %i", oldID);
                if (version < 24)
                {
                    gui_warn("Enter a new TSV (0-8191)", currentData);
                    gui_numpad(&newID, "TSV within range 0-8191", 4);
                }
                else
                {
                    gui_warn("Enter a new TSV (0-4095)", currentData);
                    gui_numpad(&newID, "TSV within range 0-4095", 4);
                }
                newID &= tsvLimit;
                sprintf(&currentData, "%i", newID);
                gui_warn("TSV set to", currentData);
                id.u16[1] |= (newID << tsvShift) ^ id.u16[0];
                break;
            case 4: // OT name
                gui_warn("Editing trainer name", "is not supported yet.");
                // memset(oldName, '\0', nameLen);
                // strcpy(oldName, otName);
                // sprintf(&currentData, "Current OT name: %c", oldName);
                // gui_warn("Enter a new OT name", currentData);
                // memset(newName, '\0', nameLen);
                // gui_keyboard(newName, "", nameLen);
                // gui_warn("OT name set to", newName);
                // memset(otName, '\0', nameLen);
                // strcpy(otName, newName);
                break;
            case 5: // u16 TID
                oldID = id.u16[0];
                id.u16[0] = 0;
                sprintf(&currentData, "Current TID: %i", oldID);
                gui_warn("Enter a new TID (0-65535)", currentData);
                gui_numpad(&newID, "TID within range 0-65535", 5);
                newID &= 0xFFFF;
                sprintf(&currentData, "%i", newID);
                gui_warn("TID set to", currentData);
                id.u16[0] = newID;
                break;
            default:
                gui_warn("Impossible choice!", "Please report this");
                break;
        }

        if (oldID != newID /*|| strcmp(oldName, newName) != 0*/ )
        {
            changes += 1;
        }
        choice = gui_menu_20x2("Edit which piece of trainer info?", opts, fields);
    }

    if (changes)
    {
        *(unsigned int *)(saveData + ofsTID) = id.u32;
        // sav_set_string(otName, ofsName, nameLen);
    }

    free(oldName);
    free(newName);
    // free(otName);
    return 0;
}
