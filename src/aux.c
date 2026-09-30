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
void print_formatted_hour(int s, int m, int h)
{
    if (h > 0)
        printf("%d:%02d:%02d", h, m, s);
    else
        printf("%02d:%02d", m, s);
}
