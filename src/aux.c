/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include "aux.h"
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>


/* == AUXILIARY == */
// check if a arg (usually opt, that stands for option)
// if valid or not. return 1 if is option, 0 if isn't
int is_opt(char *arg, char *a, char *b)
{
    return strcmp(arg, a) == 0 || strcmp(arg, b) == 0;
}

// send a sound_alert n times with \a
void sound_alert(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\a");
        fflush(stdout);
        sleep(1);
    }
}
