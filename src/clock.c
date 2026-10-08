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
// update the time elapsed since last check
void update_time(int *secs, time_t *last, int direction, int paused)
{
    // verify the current time
    time_t now = time(NULL);

    // if timer is paused, the last verification will be the current
    // it happens to dont elapse time if its paused
    if (paused)
    {
        *last = now;
        return;
    }

    // verify if the current time is greater than the last verified time
    if (now > *last)
    {
        // verify how many time has elapsed since last verification
        int ticks = (int)(now - *last);

        // verify the direction. usually, timer has the direction set to 0, that decrases ticks.
        if (direction)  *secs += ticks;
        else            *secs -= ticks;

        // incrase last by elapsed time, to avoid future incorrect verification
        *last += ticks;
    }
}

// creates a digital clock, viewing the current hours
void digital_clock(void)
{
    init_ui();

    // verify the time since unix epoch and create p_time scruct
    time_t rawtime = 0; // UNIX epoch (Jan 1 1970)
    struct tm *p_time = NULL;

    while (1)
    {
        // format the time to show the current time, using the localtime reference
        time(&rawtime);
        p_time = localtime(&rawtime);
        int secs = p_time->tm_hour * 3600 + p_time->tm_min * 60 + p_time->tm_sec;

        // draw the ui
        draw_ui(secs, "DIGITAL CLOCK", "", "[q] Quit");

        // handle the user input to exit
        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        
        usleep(50000);
    }
}

// create a stopwatch, that starts in 0 and its time is updating
void stopwatch(void)
{
    init_ui();

    // starts the initial variables, such as last verified time
    int secs = 0;
    int initial_sec = secs;
    time_t last = time(NULL);
    int pause = 0;

    while (1)
    {
        // draw the ui
        draw_ui(secs, "STOPWATCH", "", "[q] Quit | [p] Pause | [r] Restart");

        // handle user input, possibling the exit, pausing and restarting the stopwatch
        int input = handle_input();
        if (input == 1)  { cleanup_ui(); exit(0); }
        if (input == 2)  { pause = !pause; last = time(NULL); }
        if (input == 3)  { secs = initial_sec; last = time(NULL); }

        // update the time, increasing secs value
        update_time(&secs, &last, 1, pause);
        usleep(50000);
    }
}

// creates a timer, that goes to input time to 0
void timer(int secs)
{
    init_ui();

    // start the initial variables state
    int initial_sec = secs;
    time_t last = time(NULL);
    int pause = 0;

    // main loop, if has seconds to decrease
    while (secs > 0)
    {
        // draw the ui
        draw_ui(secs, "TIMER", "", "[q] Quit | [p] Pause | [r] Restart");

        // check the user input for quit, pause or restart
        int input = handle_input();
        if (input == 1)         { cleanup_ui(); exit(0); }
        if (input == 2)         { pause = !pause; last = time(NULL); }
        if (input == 3)         { secs = initial_sec; last = time(NULL); }

        // update the secs value, decreasing it
        update_time(&secs, &last, 0, pause);
        usleep(50000);
    }

    // draw the ui if it is 0 seconds and make a sound alert
    draw_ui(0, "TIMER", "", "[q] Quit | [p] Pause | [r] Restart");
    sound_alert(3);
    cleanup_ui();
}

// start a pomodoro timer, that can be a work mode or a break mode
void timer_pomodoro(int secs, int loop, int work)
{
    // initial variables states
    int initial_sec = secs;
    int pause = 0;
    time_t last = time(NULL);

    // creates the formatted description with loop and hours
    char description[64];
    snprintf(description, sizeof(description), "Loop %d - %s time!", loop, work ? "Work" : "Break");

    // timer loop
    while (secs > 0)
    {
        draw_ui(secs, "POMODORO", description, "[q] Quit | [p] Pause | [r] Restart | [s] Skip");

        // handle user input, that can skip the session with s
        int input = handle_input();
        if (input == 1) { cleanup_ui(); exit(0); }
        if (input == 2) { pause = !pause; last = time(NULL); }
        if (input == 3) { secs = initial_sec; last = time(NULL); }
        if (input == 4) { break; }

        // decrease the secs value
        update_time(&secs, &last, 0, pause);
        usleep(50000);
    }

    // draw the end ui, for secs in 0
    draw_ui(0, "POMODORO", description, "[q] Quit | [p] Pause | [r] Restart | [s] Skip");
    sound_alert(3);
    cleanup_ui();
}

// starts a pomodoro loop, with the work time and the break time
void pomodoro(int pom, int brk)
{
    // set the initial loop to 0
    int loop = 1;

    init_ui();

    // main loop
    while (1)
    {
        // run the work mode and check if you want to continue
        timer_pomodoro(pom * 60, loop, 1);
        continue_pomodoro(brk, 0);

        // run the break mode and check if you want to continue
        timer_pomodoro(brk * 60, loop, 0);
        continue_pomodoro(pom, 1);

        // increase loop by 1
        loop++;
    }

    cleanup_ui();
}

// alarm function, that triggers if it reaches a certain hour and minute (ex: 18h30)
// this function dont handle alarming for other days, only the current day
void clock_alarm(int h, int m)
{
    init_ui();

    // starts the initial variables, such as rawtime and scruct now
    time_t rawtime;
    struct tm *now;

    // creates the formatted desc
    char desc[64];
    snprintf(desc, sizeof(desc), "Set to %02d:%02d", h, m);

    // main loop
    while (1)
    {
        // verify the current time and calculates the total secs with it
        rawtime = time(NULL);
        now = localtime(&rawtime);
        int secs = now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec;

        // draw the ui
        draw_ui(secs, "ALARM", desc, "[q] Quit");

        // verify if the hours is current time is above or equals to the goal time
        if (now->tm_hour > h || (now->tm_hour == h && now->tm_min >= m))
        {
            // stops only if you stop it
            while (1)  { sound_alert(5); sleep(3); }
            break;
        }

        // handle user input, alowing to quit
        int input = handle_input();
        if (input == 1) { cleanup_ui(); return; }

        usleep(50000);
    }

    cleanup_ui();
}
