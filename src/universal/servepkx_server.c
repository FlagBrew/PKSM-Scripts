#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned char version = *argv[2];

    int fromStorage;
    int box;
    int slot;
    int size;
    enum Generation gen;

    switch (version)
    {
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
            size = 136;
            gen = GEN_FOUR;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            size = 136;
            gen = GEN_FIVE;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            size = 232;
            gen = GEN_SIX;
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            size = 232;
            gen = GEN_SEVEN;
            break;
        case 42:
        case 43:
            size = 260;
            gen = GEN_LGPE;
            break;
        default:
            gui_warn("Invalid generation for this save.", "");
            return -1;
    }

    if (gui_boxes(&fromStorage, &box, &slot, 1) == 0)
    {
        char* pkm = malloc(size);
        int received = 0;
        char message[64];
        snprintf(message, 64, "Server starting at %s", net_ip());
        gui_warn(message, "Send a pkx via servepkx.");
        if (net_tcp_recv(pkm, size, &received) == 0)
        {
            if (received == size)
            {
                if (fromStorage)
                {
                    bank_inject_pkx(pkm, gen, box, slot);
                }
                else
                {
                    // TODO: optimize
                    sav_box_decrypt();
                    sav_inject_pkx(pkm, gen, box, slot, 0);
                    sav_box_encrypt();
                }
            }
            else
            {
                gui_warn("Failed to receive correct data amount.", "");
            }
        }
        else
        {
            gui_warn("Data failed to receive.", "");            
        }
        free(pkm);
    }

    return 0;
}
