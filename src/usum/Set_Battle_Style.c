#include <pksm.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *labels[] = {
        "Exit Script",
        "Normal", "Elegant", "Girlish",
        "Reverent", "Smug", "Left-Handed",
        "Passionate", "Idol", "Nihilist"
    };
    int style = sav_get_byte(0, 0x147A);
    char msg[50] = {'\0'};
    sprintf(msg, "Choose a Battle Style\n\nCurrent: %s", labels[style + 1]);
    style = gui_menu_20x2(msg, 10, labels);
    if (style)
    {
        sav_set_byte(style - 1, 0, 0x147A);
        sprintf(msg, "Battle Style set to %s", labels[style]);
        gui_warn(msg);
    }
    return 0;
}
