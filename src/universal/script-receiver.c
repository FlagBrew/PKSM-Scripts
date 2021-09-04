#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char scriptName[64] = {0};
    // Instead of asking the user for the script name, we'll get it from the TCP
    gui_warn("We need to receive the script name!");
    char message[50] = {'\0'};
    sprintf(message, "This will lock your console!\n%s", net_ip());
    if (gui_choice(message))
    {
        char data[4];
        int received;
        net_tcp_recv(data, 4, &received);
        if (received != 4)
        {
            gui_warn("Receiving size failed!");
            return 1;
        } else
        {
            // The data sent must be little-endian
            int size = ((int)data[0]) | (((int)data[1]) << 8) | (((int)data[2]) << 16) | (((int)data[3]) << 24);
            char buf[28] = {0};
            sprintf(buf, "Receive %i bytes?", size);
            buf[27] = '\0';
            if (gui_choice(buf))
            {
                char* recvData = malloc(size);
                if (recvData != NULL)
                {
                    net_tcp_recv(recvData, size, &received);
                    if (received != size)
                    {
                        gui_warn("Receiving name failed!");
                        return 1;
                    }
                    strncat(scriptName, recvData, size);
                }
                else
                {
                    gui_warn("Allocation failed\nName couldn't be got");
                    return 1;
                }
            }
        }
    } else {
        return 0;
    }
    char path[92] = {0};
    if(gui_choice("Is this a universal script?\nThis means will it run on any game."))
    {
        sprintf(path, "/3ds/PKSM/scripts/universal/%s", scriptName);
    } else
    {
        switch (*argv[0]) {
            case 1:
            case 2:
                sprintf(path, "/3ds/PKSM/scripts/rs/%s", scriptName);
                break;
            case 3:
                sprintf(path, "/3ds/PKSM/scripts/e/%s", scriptName);
                break;
            case 4:
            case 5:
                sprintf(path, "/3ds/PKSM/scripts/frlg/%s", scriptName);
                break;
            case 7:
            case 8:
                sprintf(path, "/3ds/PKSM/scripts/hgss/%s", scriptName);
                break;
            case 10:
            case 11:
                sprintf(path, "/3ds/PKSM/scripts/dp/%s", scriptName);
                break;
            case 12:
                sprintf(path, "/3ds/PKSM/scripts/pt/%s", scriptName);
                break;
            case 21:
            case 20:
                sprintf(path, "/3ds/PKSM/scripts/bw/%s", scriptName);
                break;
            case 23:
            case 22:
                sprintf(path, "/3ds/PKSM/scripts/b2w2/%s", scriptName);
                break;
            case 24:
            case 25:
                sprintf(path, "/3ds/PKSM/scripts/xy/%s", scriptName);
                break;
            case 27:
            case 26:
                sprintf(path, "/3ds/PKSM/scripts/oras/%s", scriptName);
                break;
            case 30:
            case 31:
                sprintf(path, "/3ds/PKSM/scripts/sm/%s", scriptName);
                break;
            case 32:
            case 33:
                sprintf(path, "/3ds/PKSM/scripts/usum/%s", scriptName);
                break;
            case 42:
            case 43:
                sprintf(path, "/3ds/PKSM/scripts/lgpe/%s", scriptName);
                break;

        }
    }
    path[91] = '\0';
    if (gui_choice(message))
    {
        char data[4];
        int received;
        net_tcp_recv(data, 4, &received);
        if (received != 4)
        {
            gui_warn("Receiving size failed!");
        }
        else
        {
            // The data sent must be little-endian
            int size = ((int)data[0]) | (((int)data[1]) << 8) | (((int)data[2]) << 16) | (((int)data[3]) << 24);
            char buf[28] = {0};
            sprintf(buf, "Receive %i bytes?", size);
            buf[27] = '\0';
            if (gui_choice(buf))
            {
                char* recvData = malloc(size);
                if (recvData != NULL)
                {
                    net_tcp_recv(recvData, size, &received);
                    if (received != size)
                    {
                        gui_warn("Receiving data failed!");
                    }
                    FILE* script = fopen(path, "w");
                    if (script != NULL)
                    {
                        fwrite(recvData, 1, size, script);
                        fclose(script);
                    }
                    else
                    {
                        gui_warn("Opening file failed");
                    }
                }
                else
                {
                    gui_warn("Allocation failed\nNothing was written");
                }
            }
        }
    }

    return 0;
}
