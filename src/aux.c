/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include <stdio.h>


/* == AUXILIARY == */
// just clean a line xd
void clear_line(void)
{
    printf("\r               \r");
}

// print formatted hour. if no hour, doesnt print it
// it also sleep and clear the line
void print_formatted_hour(int s, int m, int h)
{
    clear_line();

    if (h > 0)
        printf("%d:%02d:%02d", h, m, s);
    else
        printf("%02d:%02d", m, s);

    fflush(stdout);
    sleep(1);
}

void sound_alert(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\a");
        fflush(stdout);
        sleep(1);
    }
}
