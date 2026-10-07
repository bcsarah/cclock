/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include "aux.h"
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


/* == AUXILIARY == */
//
int is_opt(char *arg, char *a, char *b)
{
    return strcmp(arg, a) == 0 || strcmp(arg, b) == 0;
}

// 
void update_time(int *secs, time_t *last, int direction, int paused)
{
    time_t now = time(NULL);

    if (paused)
    {
        *last = now;
        return;
    }

    if (now > *last)
    {
        int ticks = (int)(now - *last);

        if (direction)  *secs += ticks;
        else            *secs -= ticks;

        *last += ticks;
    }
}

//
void sound_alert(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\a");
        fflush(stdout);
        sleep(1);
    }
}
