/* @author bcsarah@ui.c
 *
 * this file contains the functions that controls
 * the ncurses lib. modifications to ui are
 * made here :)
 */

#include "ui.h"
#include <ncurses.h>


/* == [ UI ] == */
//
void init_ui(void)
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
}

//
void cleanup_ui(void)
{
    endwin();
}

//
int handle_input(void)
{
    int ch;

    while ((ch = getch()) != ERR)
    {
        if (ch == 'q')       return 1; // quit
        else if (ch == 'p')  return 2; // pause 
        else if (ch == 'r')  return 3; // reset
    }
    return 0;
}

//
void print_formatted_hour(int h, int m, int s)
{
    int x_hour_pos = (COLS - 8) / 2;
    int x_min_pos = (COLS - 5) / 2;
    int y = LINES / 2;

    if (h > 0)  mvprintw(y - 2, x_hour_pos, "%02d:%02d:%02d", h, m, s);
    else        mvprintw(y - 2, x_min_pos, "%02d:%02d", m, s);
}

//
void draw_clock(int h, int m, int s)
{
    int x_title_pos = (COLS - 13) / 2;
    int x_hour_pos = (COLS - 8) / 2;
    int x_hint_pos = (COLS - 8) / 2;
    int y = LINES / 2;

    erase();
    mvprintw(y - 4, x_title_pos, "DIGITAL CLOCK");
    mvprintw(y - 2, x_hour_pos, "%02d:%02d:%02d", h, m, s);
    mvprintw(y, x_hint_pos, "[q] Quit");
    refresh();
}

//
void draw_stopwatch(int h, int m, int s)
{
    int x_title_pos = (COLS - 9) / 2;
    int x_hint_pos = (COLS - 32) / 2;
    int y = LINES / 2;

    erase();
    mvprintw(y - 4, x_title_pos, "STOPWATCH");
    print_formatted_hour(h, m, s);
    mvprintw(y, x_hint_pos, "[q] Quit | [p] Pause | [r] Reset");
    refresh();
}

//
void draw_timer(int h, int m, int s)
{
    int x_title_pos = (COLS - 5) / 2;
    int x_hint_pos = (COLS - 32) / 2;
    int y = LINES / 2;

    erase();
    mvprintw(y - 4, x_title_pos, "TIMER");
    print_formatted_hour(h, m, s);
    mvprintw(y, x_hint_pos, "[q] Quit | [p] Pause | [r] Reset");
    refresh();
}
