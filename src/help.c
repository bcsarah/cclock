/* @author bcsarah@help.c
 *
 * this is file contains the help functions,
 * such as --help, timer_usage and others
 */

#include "help.h"
#include <stdio.h>


/* == [ HELP ] == */
// --help function
void show_help(void)
{
    printf("USAGE: cclock [func]\n");
}

// show timer function usage
void timer_usage(void)
{
    printf("USAGE: cclock timer [h] [m] [s]\n");
    printf("\tcclock timer 10      -> 00:10\n");
    printf("\tcclock timer 15 10   -> 15:10\n");
    printf("\tcclock timer 1 15 10 -> 01:15:10\n");
}

// show pomodoro function usage
void pomodoro_usage(void)
{
    printf("USAGE: cclock pomodoro [pom] [brk]\n");
    printf("\tcclock pomodoro        -> 25min / 5min\n");
    printf("\tcclock pomodoro 30     -> 30min / 5min\n");
    printf("\tcclock pomodoro 30 10  -> 30min / 10min\n");
}
