/* @author bcsarah@aux.h */
#ifndef AUX_H
#define AUX_H

#include <time.h>

int is_opt(char *arg, char *a, char *b);
void update_time(int *secs, time_t *last, int direction, int paused);
void sound_alert(int count);

#endif
