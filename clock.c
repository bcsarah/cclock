#include <stdio.h>
#include <unistd.h>
#include "clock.h"
#include "aux.h"

/* formulas
int i;
int h = i / 3600;
int m = (i % 3600) / 60;
int s = i % 60;
*/


/* ==[ FUNCTIONS ]== (literally) */
int stopwatch()
{
    int i = 0, h = 0, m = 0, s = 0;

    while (1)
    {
        s = i % 60;
        m = (i % 3600) / 60;
        h = i / 3600;

        clearLine();
        if (h > 0)
            printf("\r%d:%02d:%02d", h, m, s);
        else
            printf("\r%02d:%02d", m, s);

        fflush(stdout);
        sleep(1);
        i++;
    }

    return 0;
}

// timer
int timer(int hour, int min, int seg)
{
    int i = hour * 3600 + min * 60 + seg;
    int h, m, s;

    while (i > 0)
    {
        s = i % 60;
        m = (i % 3600) / 60;
        h = i / 3600;

        clearLine();
        if (h > 0)
            printf("%d:%02d:%02d", h, m, s);
        else
            printf("%02d:%02d", m, s);

        fflush(stdout);
        sleep(1);
        i--;
    }

    clearLine();
    printf("\r00:00\n");
    return 0;
}

// pomodoro
int pomodoro(int pom, int brk)
{
    int i = 1;

    while (1)
    {
        printf("[ LOOP %d ]\n", i);
        printf("starting %dmin pomodoro...\n", pom);
        timer(0, pom, 0);
        printf("starting %dmin break...\n", brk);
        timer(0, brk, 0);
        printf("\n");
        i++;
    }
    return 0;
}
