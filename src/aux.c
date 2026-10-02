/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include <stdio.h>
#include <stdlib.h>


/* == AUXILIARY == */
// just clean a line xd
void clear_line(void)
{
    printf("\r\033[K"); // clear all the line with ANSI
    fflush(stdout);
}

// print formatted hour. if no hour, doesnt print it
// it also sleep and clear the line
void print_formatted_hour(int h, int m, int s)
{
    clear_line();

    if (h > 0)
        printf("%02d:%02d:%02d", h, m, s);
    else
        printf("%02d:%02d", m, s);

    fflush(stdout);
    sleep(1);
}

// make a sound alert a certain amount of beeps
void sound_alert(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\a");
        fflush(stdout);
        sleep(1);
    }
}

// function to continue pomodoro
void continue_pomodoro(void)
{
    char input;

    while (1)
    {
        printf("do you wish to continue? (y/n) ");
        scanf(" %c", &input);

        // input validation
        if (input == 'y')
            printf("\n");
        else if (input == 'n')
            exit(0);
        else
            continue;
        break;
    }
}
