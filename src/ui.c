/* @author bcsarah@ui.c
 *
 * this file contains the functions that controls
 * the ncurses lib. modifications to ui are
 * made here :)
 */

#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


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
    clear();
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
        else if (ch == 's')  return 4; // skip 
    }
    return 0;
}

//
void print_formatted_hour(int secs)
{
    int h = secs / 3600;
    int m = (secs % 3600) / 60;
    int s = secs % 60;

    int x_hour_pos = (COLS - 8) / 2;
    int x_min_pos = (COLS - 5) / 2;
    int y = LINES / 2;

    if (h > 0)  mvprintw(y - 2, x_hour_pos, "%02d:%02d:%02d", h, m, s);
    else        mvprintw(y - 2, x_min_pos, "%02d:%02d", m, s);
}

//
void draw_ui(int secs, const char *title, const char *description, const char *hint)
{
    int y = LINES / 2;

    int title_x = (COLS - (int)strlen(title)) / 2;
    int description_x = (COLS - (int)strlen(description)) / 2;
    int hint_x = (COLS - (int)strlen(hint)) / 2;

    erase();

    mvprintw(y - 5, title_x, "%s", title);
    mvprintw(y - 4, description_x, "%s", description);

    print_formatted_hour(secs);

    mvprintw(y, hint_x, "%s", hint);

    refresh();
}

// 
void continue_pomodoro(int time, int work)
{
    while (1)
    {
        int x = (COLS - 26) / 2;
        int y = (LINES - 2) / 2;
        const char *mode = work ? "work" : "break";
        
        cleanup_ui();
        mvprintw(y - 2, x, "do you wish to continue to %dmin %s? (y/n)", time, mode);

        nodelay(stdscr, FALSE);
        char input = getch();
        nodelay(stdscr, TRUE);

        if (input == 'y' || input == 'Y')      break;
        else if (input == 'n' || input == 'N') { endwin(); exit(0); }
    }
}
