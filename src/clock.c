/* @author bcsarah@clock.c
 *
 * it coitains the clock functions,
 * such as pomodoro, timer and
 * a stopwatch.
 */

#include "clock.h"
#include "aux.h"
#include "ui.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>


/* ==[ CLOCK FUNCTIONS ]== */
//
void digital_clock(void)
{
    init_ui();

    time_t rawtime = 0; // UNIX epoch (Jan 1 1970)
    struct tm *p_time = NULL;

    while (1)
    {
        time(&rawtime);
        p_time = localtime(&rawtime);

        draw_clock(p_time->tm_hour, p_time->tm_min, p_time->tm_sec);
        usleep(50000);
    }
}

//
void stopwatch(void)
{
    init_ui();

    int secs = 0;
    time_t last = time(NULL);

    while (1)
    {
        int h = secs / 3600;
        int m = (secs % 3600) / 60;
        int s = secs % 60;

        draw_stopwatch(h, m, s);

        update_time(&secs, &last, 1);
        usleep(50000);
    }
}

//
void timer(int hour, int min, int sec)
{
    init_ui();

    int secs = hour * 3600 + min * 60 + sec;
    time_t last = time(NULL);

    while (secs > 0)
    {
        int h = secs / 3600;
        int m = (secs % 3600) / 60;
        int s = secs % 60;

        draw_timer(h, m, s);
        update_time(&secs, &last, 0);
        usleep(50000);
    }

    sound_alert(3);
}

//
void pomodoro(int pom, int brk)
{
    init_ui();
    continue_pomodoro(1);

    int i = 1;

    while (1) 
    {
        printf("[ LOOP %d ]\n", i);

        printf("starting %dmin pomodoro...\n", pom);
        timer(0, pom, 0);
        continue_pomodoro(0);

        printf("starting %dmin break...\n", brk);
        timer(0, brk, 0);
        continue_pomodoro(0);

        printf("\n");
        i++;
    }
}
