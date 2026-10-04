/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include "aux.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
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
void update_time(int *secs, time_t *last, int direction)
{
    time_t now = time(NULL);

    if (now != *last)
    {
        if (direction)  *secs += (int)(now - *last);
        else            *secs -= (int)(now - *last);

        *last = now;
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

// 
void continue_pomodoro(int start)
{
    char input;

    while (1)
    {
        if (start == 1)  printf("do you wish to start pomodoro? (y/n) ");
        else             printf("do you wish to continue? (y/n) ");

        scanf(" %c", &input);

        if (input == 'y')       printf("\n");
        else if (input == 'n')  exit(0);
        else                    continue;
        break;
    }
}
