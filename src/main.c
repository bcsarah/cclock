#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clock.c"


/* ===[ MAIN ]=== */
int main(int argc, char *argv[])
{
    if (argc < 2) // if no option, doesnt run
    {
        printf("USAGE: cclock [func]\n");
        return 1;
    }
    char *opt = argv[1];


    // stopwatch
    if (strcmp(opt, "s") == 0 || strcmp(opt, "stopwatch") == 0)
    {
        // TODO add the fucking start time configuration
        stopwatch(0);
    }

    // timer
    else if (strcmp(opt, "t") == 0 || strcmp(opt, "timer") == 0)
    {
        int h = 0, m = 0, s = 0;

        if (argc > 5)
            timer_help(); return 1;

        // asign seconds, minutes and hours by position (s, m, h)
        if (argc >= 2) // default (5 minutes timer)
            timer(0, 5, 0); return 0;
        if (argc >= 3) // last = seconds
            s = atoi(argv[argc - 1]);
        if (argc >= 4) // penultimate = minutes 
            m = atoi(argv[argc - 2]);
        if (argc >= 5) // antepenultimate = hours 
            h = atoi(argv[argc - 3]);

        // verify if time is below 0
        if ((h < 0 || m < 0 || s < 0) || (h == 0 && m == 0 && s == 0))
            printf("ERROR: time must be above 0\n"); return 1;

        timer(h, m, s);
    }

    // pomodoro
    else if (strcmp(argv[1], "p") == 0 || strcmp(argv[1], "pomodoro") == 0)
    {
        if (argc == 2)
            pomodoro(25, 5);
        else if (argc == 3)
            pomodoro(atoi(argv[2]), 5);
        else if (argc == 4)
            pomodoro(atoi(argv[2]), atoi(argv[3]));
        else
            pomodoro_help(); return 1;
    }

    return 0;
}
