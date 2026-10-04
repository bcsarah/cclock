/* @author bcsarah@aux.c
 *
 * this file is for the auxiliary functions
 * (not the clock functions) used in the software,
 * such as clear a line, print the formatted hour, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* == AUXILIARY == */
// just clean a line xd
void clear_line(void) {
  printf("\r\033[K"); // clear all the line with ANSI
  fflush(stdout);
}

// wait a second duuh
void update_time(int *secs, time_t *last, int direction) {
  time_t now = time(NULL);
  if (now != *last) {
    if (direction) {
      *secs += (int)(now - *last);
    } else {
      *secs -= (int)(now - *last);
    }
    *last = now;
  }
}

// print formatted hour. if no hour, doesnt print it
// it also sleep and clear the line
void print_formatted_hour(int h, int m, int s) {
  clear_line();

  if (h > 0)
    printf("%02d:%02d:%02d", h, m, s);
  else
    printf("%02d:%02d", m, s);

  fflush(stdout);
}

// make a sound alert a certain amount of beeps
void sound_alert(int count) {
  for (int i = 0; i < count; i++) {
    printf("\a");
    fflush(stdout);
    if (!(i == count - 1))
      sleep(1);
  }
}

// function to continue pomodoro
void continue_pomodoro(int start) {
  char input;

  while (1) {
    // verify if is the start pomodor or not
    if (start == 1)
      printf("do you wish to start pomodoro? (y/n) ");
    else
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
