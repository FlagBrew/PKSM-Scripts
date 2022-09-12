#include <pksm.h>
#include <stdlib.h>
#include <stdio.h>


unsigned int limit_num(int min, int max, int max_digits)
{
    unsigned int num;
    char hint[35] = {'\0'};
    sprintf(hint, "Enter a number from %d to %d", min, max);
    while (1)
    {
        gui_warn(hint);
        gui_numpad(&num, hint, max_digits);
        if (num >= min && num <= max)
        {
            break;
        }
        gui_warn("Invalid input\nPlease try again.");
    }
    return num;
}


int main(int argc, char **argv)
{
    int version = *argv[0];
    if (version > 3)
    {
        gui_warn("This script doesn't work\non this game.");
        return 1;
    }

    char initial[8];
    char elapsed[8];
    sav_get_data(initial, 8, 0, 0x98);
    sav_get_data(elapsed, 8, 0, 0xA0);

    int clock, time;
    unsigned int input = 0, day = 0, hour = 0, minute = 0, second = 0;
    char *clocks[] = {
        "Exit script",
        "Initial",
        "Elapsed"
    };
    char *times[] = {
        "Previous menu",
        "Day",
        "Hour",
        "Minute",
        "Second"
    };
    char changed[31];
    char clock_question[61] = {0};

    while (1)
    {
        clock = gui_menu_20x2("Which RTC time do you want\nto change?", 3, clocks);
        if (!clock)
        {
            break;
        }

        while (1)
        {
            if (clock == 1)
            {
                day = *(unsigned short *)(&initial[0]);
                hour = initial[2];
                minute = initial[3];
                second = initial[4];
            }
            else
            {
                day = *(unsigned short *)(&elapsed[0]);
                hour = elapsed[2];
                minute = elapsed[3];
                second = elapsed[4];
            }
            sprintf(clock_question, "Which portion do you\nwant to edit?\n\n%s RTC:\n%u:%02u:%02u:%02u", clocks[clock], day, hour, minute, second);
            time = gui_menu_20x2(clock_question, 5, times);
            if (!time)
            {
                break;
            }

            switch (time)
            {
                case 1:
                    input = limit_num(0, 999, 3);
                    break;
                case 2:
                    input = limit_num(0, 23, 2);
                    break;
                case 3:
                case 4:
                    input = limit_num(0, 59, 2);
                    break;
                default:
                    break;
            }

            if (clock == 1)
            {
                if (time == 1)
                {
                    *(short *)(&initial[0]) = (short)input;
                }
                else
                {
                    initial[time] = (char)input;
                }
            }
            else
            {
                if (time == 1)
                {
                    *(short *)(&elapsed[0]) = (short)input;
                }
                else
                {
                    elapsed[time] = (char)input;
                }
            }
            sprintf(changed, "%s RTC's %s set to %d", clocks[clock], times[time], time == 1 ? (short)input : (char)input);
            gui_warn(changed);
        }
    }

    sav_set_data(initial, 8, 0, 0x98);
    sav_set_data(elapsed, 8, 0, 0xA0);
    sav_set_short(*(short *)(&elapsed[0]), 2, (version == 3 ? 0x41c : 0x3c0) + (0x4040 * 2));

    return 0;
}
