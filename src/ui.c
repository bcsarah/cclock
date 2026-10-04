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
        else if (ch == 'r')  return 2; // reset
    }
    return 0;
}

//
void print_formatted_hour(int h, int m, int s)
{
    if (h > 0)  mvprintw(7, 10, "%02d:%02d:%02d", h, m, s);
    else        mvprintw(7, 10, "%02d:%02d", m, s);
}

//
void draw_clock(int h, int m, int s)
{
    erase();
    mvprintw(5, 10, "CLOCK");

    mvprintw(7, 10, "%02d:%02d:%02d", h, m, s);

    mvprintw(9, 10, "[q] Sair");
    refresh();
}

//
void draw_stopwatch(int h, int m, int s)
{
    erase();
    mvprintw(5, 10, "STOPWATCH");

    print_formatted_hour(h, m, s);

    mvprintw(9, 10, "[q] Sair");
    refresh();
}

//
void draw_timer(int h, int m, int s)
{
    erase();
    mvprintw(5, 10, "TIMER");

    print_formatted_hour(h, m, s);

    mvprintw(9, 10, "[q] Sair");
    refresh();
}
