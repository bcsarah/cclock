/* @author bcsarah@clock.h */

#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>


void update_time(int *secs, time_t *last, int direction, int paused);
void digital_clock(void);
void stopwatch(void);
void timer(int secs);
void pomodoro(int pom, int brk);
void pomodoro(int pom, int brk);
void clock_alarm(int h, int m);

#endif
