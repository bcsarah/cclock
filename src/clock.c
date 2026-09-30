/* @author bcsarah@clock.c
 *
 * it coitains the clock functions,
 * such as pomodoro, timer and
 * a stopwatch.
 */

#include <stdio.h>
#include <unistd.h>
#include "aux.c"

/* formula
int i;
int h = i / 3600;
int m = (i % 3600) / 60;
int s = i % 60;
*/


/* ==[ CLOCK FUNCTIONS ]== */

// start a stopwatch by 0
int stopwatch(int s_time)
{
    while (1)
    {
        int s = s_time % 60;
        int m = (s_time % 3600) / 60;
        int h = s_time / 3600;

        clear_line();
        print_formatted_hour(s, m, h);

        fflush(stdout);
        sleep(1);
        s_time++;
    }

    return 0;
}

// start an timer for hour, min and seg
int timer(int hour, int min, int seg)
{
    int i = hour * 3600 + min * 60 + seg;

    while (i > 0)
    {
        int s = i % 60;
        int m = (i % 3600) / 60;
        int h = i / 3600;

        clear_line();
        print_formatted_hour(s, m, h);

        fflush(stdout);
        sleep(1);
        i--;
    }

    clear_line();
    printf("\r00:00\n");
    return 0;
}

// show timer function help
void timer_help(void)
{
    printf("USAGE: cclock timer [h] [m] [s]\n");
    printf("\tcclock timer 10      -> 10s\n");
    printf("\tcclock timer 15 10   -> 15m, 10s\n");
    printf("\tcclock timer 1 15 10 -> 1h, 15m 10s\n");
}

// run a pomodoro
int pomodoro(int pom, int brk)
{
    int i = 1;

    while (1)
    {
        printf("[ LOOP %d ]\n", i);
        printf("starting %dmin pomodoro...\n", pom);
        timer(0, pom, 0);
        printf("starting %dmin break...\n", brk);
        timer(0, brk, 0);
        printf("\n");
        i++;
    }
    return 0;
}

void pomodoro_help(void)
{
    printf("USAGE: cclock pomodoro [pom] [brk]\n");
    printf("\tcclock pomodoro         -> 25min / 5min\n");
    printf("\tcclock pomodoro 30      -> 30min / 5min\n");
    printf("\tcclock pomodoro 30 10   -> 30min / 10min\n");
}
