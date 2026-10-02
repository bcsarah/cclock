/* @author bcsarah@clock.c
 *
 * it coitains the clock functions,
 * such as pomodoro, timer and
 * a stopwatch.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "aux.c"

/* formula
int i;
int h = i / 3600;
int m = (i % 3600) / 60;
int s = i % 60;
*/


/* ==[ CLOCK FUNCTIONS ]== */

// view the damn hours
void digital_clock(void)
{
    // this code is stealed from Bro Code, using this video as reference:
    // https://www.youtube.com/watch?v=s3QMbp7TlFg
    // i s2 u bro code (marry w me)
    time_t rawtime = 0; // UNIX epoch (Jan 1 1970)
    struct tm *p_time = NULL;

    // show the damm hours
    while (1)
    {
        time(&rawtime);
        p_time = localtime(&rawtime);

        clear_line();

        printf("\r%02d:%02d:%02d", p_time->tm_hour, p_time->tm_min, p_time->tm_sec);
        fflush(stdout);

        sleep(1);
    }
}

// start a stopwatch with initial time feature
void stopwatch(int min, int seg)
{
    int i = min * 60 + seg;

    while (1)
    {
        int h = i / 3600;
        int m = (i % 3600) / 60;
        int s = i % 60;

        print_formatted_hour(h, m, s); i++;
    }
}

// start an timer for hour, min and seg
void timer(int hour, int min, int seg)
{
    int i = hour * 3600 + min * 60 + seg;

    while (i > 0)
    {
        int h = i / 3600;
        int m = (i % 3600) / 60;
        int s = i % 60;

        print_formatted_hour(h, m, s);
        i--;
    }

    clear_line();
    printf("\r00:00");
    sound_alert(3);
    printf("\n");
}

// run a pomodoro
void pomodoro(int pom, int brk)
{
    // verify if the user want to start the pomodoro rn
    continue_pomodoro(0);

    int i = 1;

    while (1)
    {
        printf("[ LOOP %d ]\n", i);


        printf("starting %dmin pomodoro...\n", pom);
        timer(0, pom, 0);
        continue_pomodoro(1);

        printf("starting %dmin break...\n", brk);
        timer(0, brk, 0);
        continue_pomodoro(1);

        printf("\n");
        i++;
    }
}
