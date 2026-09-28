#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"


/* ===[ MAIN ]=== */
int main(int argc, char *argv[])
{
    if (argc < 2) // if no option, doesnt run
    {
        printf("USAGE: cclock [func]\n");
        return 1;
    }
    char *opt = argv[1];


    // stopwatch
    if (strcmp(opt, "-s") == 0 || strcmp(opt, "--stopwatch") == 0)
        stopwatch();

    // timer
    else if (strcmp(opt, "-t") == 0 || strcmp(opt, "--timer") == 0)
    {
        int n = argc - 2;   // how many numbers
        int h = 0, m = 0, s = 0;

        if (n < 1 || n > 3)
        {
            printf("USAGE: cclock -t [h] [m] [s]\n");
            printf("\tcclock -t 10      -> 10s\n");
            printf("\tcclock -t 15 10   -> 15m, 10s\n");
            printf("\tcclock -t 1 15 10 -> 1h, 15m 10s\n");
            return 1;
        }

        // preenche da direita pra esquerda: s, depois m, depois h
        if (n >= 1) // último  = segundos
            s = atoi(argv[argc - 1]);
        if (n >= 2) // penúltimo = minutos
            m = atoi(argv[argc - 2]);
        if (n >= 3) // antepenúltimo = horas
            h = atoi(argv[argc - 3]);

        if (h < 0 || m < 0 || s < 0)
        {
            printf("Erro: valores negativos não são permitidos\n");
            return 1;
        }

        if (h == 0 && m == 0 && s == 0)
        {
            printf("Erro: o tempo deve ser maior que zero\n");
            return 1;
        }

        timer(h, m, s);
    }

    // pomodoro
    else if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--pomodoro") == 0)
    {
        int n = argc - 2; // how many args

        if (n == 0)
            pomodoro(25, 5);

        else if (n == 1)
            pomodoro(atoi(argv[2]), 5);

        else if (n == 2)
            pomodoro(atoi(argv[2]), atoi(argv[3]));

        else
        {
            printf("USAGE: cclock -p [pom] [brk]\n");
            printf("\tcclock -p         -> 25min / 5min\n");
            printf("\tcclock -p 30      -> 30min / 5min\n");
            printf("\tcclock -p 30 10   -> 30min / 10min\n");
            return 1;
        }
    }

    return 0;
}
