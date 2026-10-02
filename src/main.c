/* @author bcsarah@main.c
 *
 * this is the main of the application.
 * pls view the --help u dumb
 * or man it (it doesnt has a man page)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clock.c"


/* == [ USAGE FUNCTIONS ] == */
void show_help(void)
{
    // TODO make a good --help
    printf("USAGE: cclock [func]\n");
}

// show stopwatch function help
void stopwatch_usage(void)
{
    printf("USAGE: cclock stopwatch [initial_m] [initial_s]\n");
    printf("\tcclock stopwatch        -> 00:00\n");
    printf("\tcclock stopwatch 30     -> 00:30\n");
    printf("\tcclock stopwatch 30 10  -> 30:10\n");
}

// show timer function help
void timer_usage(void)
{
    printf("USAGE: cclock timer [h] [m] [s]\n");
    printf("\tcclock timer 10      -> 00:10\n");
    printf("\tcclock timer 15 10   -> 15:10\n");
    printf("\tcclock timer 1 15 10 -> 01:15:10\n");
}

// show pomodoro function help
void pomodoro_usage(void)
{
    printf("USAGE: cclock pomodoro [pom] [brk]\n");
    printf("\tcclock pomodoro        -> 25min / 5min\n");
    printf("\tcclock pomodoro 30     -> 30min / 5min\n");
    printf("\tcclock pomodoro 30 10  -> 30min / 10min\n");
}


/* ===[ MAIN ]=== */
int main(int argc, char *argv[])
{
    if (argc < 2) // if no option, doesnt run
    {
        show_help();
        return 1;
    }

    char *opt = argv[1];

    // show help
    if (strcmp(opt, "--help") == 0 || strcmp(opt, "-h") == 0)
        show_help();

    // clock
    else if (strcmp(opt, "c") == 0 || strcmp(opt, "clock")  == 0)
        digital_clock();

    // stopwatch
    else if (strcmp(opt, "s") == 0 || strcmp(opt, "stopwatch") == 0)
    {
        int m, s;
        
        // verify args quantity again
        if (argc > 4)
        {
            stopwatch_usage();
            return 1;
        }
        
        // starts with default stating time
        if (argc == 2)
        {
            stopwatch(0, 0); // default
            return 0;
        }

        // asign seconds, minutes and hours by position (s, m, h)
        if (argc >= 3) // last = seconds
            s = atoi(argv[argc - 1]);
        if (argc >= 4) // penultimate = minutes 
            m = atoi(argv[argc - 2]);
        
        // verify if time is below 0
        if (m < 0 || s < 0)
        {
            printf("ERROR: time must be above or equals 0\n");
            return 0;
        }

        stopwatch(m, s);
    }

    // timer
    else if (strcmp(opt, "t") == 0 || strcmp(opt, "timer") == 0)
    {
        int h, m, s;

        // verify args quantity again
        if (argc > 5)
        {
            timer_usage();
            return 1;
        }

        // starts with default time if no time is given
        if (argc == 2)
        {
            timer(0, 5, 0); // default (5 minutes timer)
            return 0;
        }
        
        // asign seconds, minutes and hours by position (s, m, h)
        if (argc >= 3) // last = seconds
            s = atoi(argv[argc - 1]);
        if (argc >= 4) // penultimate = minutes 
            m = atoi(argv[argc - 2]);
        if (argc >= 5) // antepenultimate = hours 
            h = atoi(argv[argc - 3]);

        // verify if time is below 0
        if ((h < 0 || m < 0 || s < 0) || (h == 0 && m == 0 && s == 0))
        {
            printf("ERROR: time must be above 0\n");
            return 1;
        }

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
        {
            pomodoro_usage();
            return 1;
        }
    }

    return 0;
}
