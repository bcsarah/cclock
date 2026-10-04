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
#include <stdlib.h>
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

        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        
        usleep(50000);
    }
}

//
void stopwatch(void)
{
    init_ui();

    int secs = 0;
    int initial_sec = secs;
    time_t last = time(NULL);
    int pause = 0;

    while (1)
    {
        int h = secs / 3600;
        int m = (secs % 3600) / 60;
        int s = secs % 60;

        draw_stopwatch(h, m, s);

        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        if (input == 2)  { pause = !pause; last = time(NULL); }
        if (input == 3)  { secs = initial_sec; }

        update_time(&secs, &last, 1, pause);
        usleep(50000);
    }
}

//
void timer(int hour, int min, int sec)
{
    init_ui();

    int secs = hour * 3600 + min * 60 + sec;
    int initial_sec = secs;
    time_t last = time(NULL);
    int pause = 0;

    while (secs > 0)
    {
        int h = secs / 3600;
        int m = (secs % 3600) / 60;
        int s = secs % 60;

        draw_timer(h, m, s);

        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        if (input == 2)  { pause = !pause; last = time(NULL); }
        if (input == 3)  { secs = initial_sec; }

        update_time(&secs, &last, 0, pause);
        usleep(50000);
    }

    draw_timer(0, 0, 0);
    sound_alert(3);
    cleanup_ui();
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
