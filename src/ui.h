/* @author bcsarah@ui.h */

#ifndef UI_H
#define UI_H

void init_ui(void);
void cleanup_ui(void);
int handle_input(void);

void print_formatted_hour(int secs);
void draw_ui(int secs, const char *title, const char *description, const char *hint);
void continue_pomodoro(int time, int work);

#endif
