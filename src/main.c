/* @author bcsarah@main.c
 *
 * this is the main of the application.
 * pls view the --help u dumb
 */

#include "clock.h"
#include "aux.h"
#include "help.h"
#include <stdlib.h>

/* === [ MAIN ] === */
int main(int argc, char *argv[])
{
    // if no option, use the default clock feature
    if (argc < 2)  { digital_clock(); return 0; }

    char *opt = argv[1];

    // show help
    if (is_opt(opt, "-h", "--help"))
        show_help();

    // clock
    else if (is_opt(opt, "c", "clock"))
        digital_clock();

    // stopwatch
    else if (is_opt(opt, "s", "stopwatch"))
        stopwatch();

    // timer
    else if (is_opt(opt, "t", "timer"))
    {
        int h = 0, m = 0, s = 0;

        // verify args quantity
        if (argc > 5)  { timer_usage(); return 1; }

        // asign seconds, minutes and hours by position (s, m, h)
        if (argc == 2)  m = 5;
        if (argc >= 3)  s = atoi(argv[argc - 1]);
        if (argc >= 4)  m = atoi(argv[argc - 2]);
        if (argc >= 5)  h = atoi(argv[argc - 3]);

        timer(h, m, s);
    }

    // pomodoro
    else if (is_opt(opt, "p", "pomodoro"))
    {
        int pom = 25, brk = 5;

        // verify args quantity
        if (argc > 4)  { pomodoro_usage(); return 1; }

        // asign time if arguments are given
        if (argc >= 3)  pom = atoi(argv[2]);
        if (argc >= 4)  brk = atoi(argv[3]);

        pomodoro(pom, brk);
    }

    // if args dont match
    else
        show_help();

    return 0;
}
