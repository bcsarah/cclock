/* @author bcsarah@clock.c
 *
 * it coitains the clock functions,
 * such as pomodoro, timer and
 * a stopwatch.
 */

#include "clock.h"
#include "aux.h"
#include "ui.h"
#include <stdlib.h>
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
        int secs = p_time->tm_hour * 3600 + p_time->tm_min * 60 + p_time->tm_sec;

        draw_ui(secs, "DIGITAL CLOCK", "", "[q] Quit");

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
        draw_ui(secs, "STOPWATCH", "", "[q] Quit | [p] Pause | [r] Restart");

        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        if (input == 2)  { pause = !pause; last = time(NULL); }
        if (input == 3)  { secs = initial_sec; last = time(NULL); }

        update_time(&secs, &last, 1, pause);
        usleep(50000);
    }
}

//
void timer(int secs)
{
    init_ui();

    int initial_sec = secs;
    time_t last = time(NULL);
    int pause = 0;

    while (secs > 0)
    {
        draw_ui(secs, "TIMER", "", "[q] Quit | [p] Pause | [r] Restart");

        int input = handle_input();

        if (input == 1)         { cleanup_ui(); exit(0); }
        if (input == 2)         { pause = !pause; last = time(NULL); }
        if (input == 3)         { secs = initial_sec; last = time(NULL); }

        update_time(&secs, &last, 0, pause);
        usleep(50000);
    }

    draw_ui(0, "TIMER", "", "[q] Quit | [p] Pause | [r] Restart");
    sound_alert(3);
    cleanup_ui();
}

//
void timer_pomodoro(int secs, int loop, int work)
{
    int initial_sec = secs;
    int pause = 0;
    time_t last = time(NULL);

    char description[64];

    snprintf(description, sizeof(description), "Loop %d - %s time!", loop, work ? "Work" : "Break");

    while (secs > 0)
    {
        draw_ui(secs, "POMODORO", description, "[q] Quit | [p] Pause | [r] Restart | [s] Skip");

        int input = handle_input();
        if (input == 1) { cleanup_ui(); exit(0); }
        if (input == 2) { pause = !pause; last = time(NULL); }
        if (input == 3) { secs = initial_sec; last = time(NULL); }
        if (input == 4) { break; }

        update_time(&secs, &last, 0, pause);
        usleep(50000);
    }

    draw_ui(0, "POMODORO", description, "[q] Quit | [p] Pause | [r] Restart | [s] Skip");
    sound_alert(3);
    cleanup_ui();
}

//
void pomodoro(int pom, int brk)
{
    int loop = 1;

    init_ui();

    while (1)
    {
        timer_pomodoro(pom * 60, loop, 1);
        continue_pomodoro(brk, 0);

        timer_pomodoro(brk * 60, loop, 0);
        continue_pomodoro(pom, 1);

        loop++;
    }

    cleanup_ui();
}
