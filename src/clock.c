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
int stopwatch(void)
{
    int i;

    while (1)
    {
        int s = i % 60;
        int m = (i % 3600) / 60;
        int h = i / 3600;

        print_formatted_hour(s, m, h);
        i++;
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

        print_formatted_hour(s, m, h);
        i--;
    }

    clear_line();
    printf("\r00:00");
    sound_alert(5);
    printf("\n");
    return 0;
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
