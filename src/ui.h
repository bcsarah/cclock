/* @author bcsarah@ui.h */

#ifndef UI_H
#define UI_H

void init_ui(void);
void cleanup_ui(void);
int handle_input(void);

void print_formatted_hour(int h, int m, int s);
void draw_clock(int h, int m, int s);
void draw_stopwatch(int h, int m, int s);
void draw_timer(int h, int m, int s);

#endif
