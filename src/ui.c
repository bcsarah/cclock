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
// init ncurses ui
void init_ui(void)
{
    initscr();
    cbreak();
    noecho(); // inputs dont show in the screen
    nodelay(stdscr, TRUE); // sets getch to dont have delay, only a fast verify
    curs_set(0); // hide cursor
}

// clean ncurses ui
void cleanup_ui(void)
{
    clear();
    endwin();
}

// handle ncurses input. return 1 to quit, 2 to pause, etc. view the comments below
int handle_input(void)
{
    int ch;

    while ((ch = getch()) != ERR) // this clear buffer too
    {
        if (ch == 'q')       return 1; // q - quit
        else if (ch == 'p')  return 2; // p - pause 
        else if (ch == 'r')  return 3; // r - reset
        else if (ch == 's')  return 4; // s - skip. only used in pomodoro
    }

    return 0;
}

// print the hour, formatting it if has hour or not.
void print_formatted_hour(int secs)
{
    // convert secs to hours, mins and secs
    int h = secs / 3600;
    int m = (secs % 3600) / 60;
    int s = secs % 60;

    // create a pattern to where print the hours in screen
    int x_hour_pos = (COLS - 8) / 2;
    int x_min_pos = (COLS - 5) / 2;
    int y = LINES / 2;

    // verify if has hours, printing it if it has
    if (h > 0)  mvprintw(y - 2, x_hour_pos, "%02d:%02d:%02d", h, m, s);
    else        mvprintw(y - 2, x_min_pos, "%02d:%02d", m, s);
}

// draw the program ui, with a title, description, hint etc
void draw_ui(int secs, const char *title, const char *description, const char *hint)
{
    int y = LINES / 2;

    // verify if it has description. return 1 to true, 0 to false
    int has_description = description != NULL && description[0] != '\0';

    cleanup_ui();

    // create a pattern to where show things in the screen
    int title_y = has_description ? y - 5 : y - 4;
    int title_x = (COLS - (int)strlen(title)) / 2;
    int hint_x = (COLS - (int)strlen(hint)) / 2;

    // print the title
    mvprintw(title_y, title_x, "%s", title);

    // print the description, if it has
    if (has_description) {
        int description_x = (COLS - (int)strlen(description)) / 2;
        mvprintw(y - 4, description_x, "%s", description);
    }

    // print the hours
    print_formatted_hour(secs);
    mvprintw(y, hint_x, "%s", hint);

    refresh();
}

// create a basic ui for pomodoro to break interval, handling y/n inputs
void continue_pomodoro(int time, int work)
{
    while (1)
    {
        // creates the text that will print and verify the mode of the operation
        const char *text = "do you wish to continue to %dmin %s? (y/n)";
        const char *mode = work ? "work" : "break";

        // create a pattern to where show things in the screen
        int x = (COLS - (int)strlen(text)) / 2;
        int y = (LINES - 2) / 2;
        
        // show the things in the screen
        cleanup_ui();
        mvprintw(y - 2, x, "do you wish to continue to %dmin %s? (y/n)", time, mode);
        refresh();

        // get the input, seting nodelay to false so it doesnt interrupt
        nodelay(stdscr, FALSE);
        char input = getch();
        nodelay(stdscr, TRUE);

        // continue if y, exit program if n
        if      (input == 'y' || input == 'Y')  break;
        else if (input == 'n' || input == 'N')  { endwin(); exit(0); }
    }
}
