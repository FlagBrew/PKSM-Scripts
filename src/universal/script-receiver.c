#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (gui_choice("This will lock your console!", net_ip()))
    {
        char data[4];
        int received;
        net_tcp_recv(data, 4, &received);
        if (received != 4)
        {
            gui_warn("Receiving size failed!", "");
        }
        else
        {
            // The data sent must be little-endian
            int size = ((int)data[0]) | (((int)data[1]) << 8) | (((int)data[2]) << 16) | (((int)data[3]) << 24);
            char buf[28] = {0};
            sprintf(buf, "Receive %i bytes?", size);
            buf[27] = '\0';
            if (gui_choice(buf, ""))
            {
                char* recvData = malloc(size);
                if (recvData != NULL)
                {
                    net_tcp_recv(recvData, size, &received);
                    if (received != size)
                    {
                        gui_warn("Receiving data failed!", "");
                    }
                    FILE* script = fopen("/3ds/PKSM/scripts/universal/recvScript.c", "w");
                    if (script != NULL)
                    {
                        fwrite(recvData, 1, size, script);
                        fclose(script);
                    }
                    else
                    {
                        gui_warn("Opening file failed", "");
                    }
                }
                else
                {
                    gui_warn("Allocation failed", "Nothing was written");
                }
            }
        }
    }

    return 0;
}
