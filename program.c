#define _POSIX_C_SOURCE 200201L
#define _DEFAULT_SOURCE
#define BLANK ' '

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "program.h"
#include "map.h"
#include <math.h>

void game_field();
void fog(const int rows, char field[][rows], char undiscovered[][rows]);
void game(const int rows, char field[][rows], char undiscovered[][rows]);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    // initialize the library
    initscr();
    start_color();
    use_default_colors();
    // set implicit modes
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(0);
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    //code goes here
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_MAGENTA, -1);
    init_pair(3, COLOR_WHITE, -1);
    init_pair(4, COLOR_YELLOW, -1);
    game_field(); // HERNA PLOCHA
    const int rows = 45;
    char field[24][rows];
    char undiscovered[24][rows];
    //  char enemy_lot[24][rows];

    game(rows, field, undiscovered);

    getchar();

    // end curses
    endwin();
    return EXIT_SUCCESS;
}

void game_field() //5*3 HRAC hitbox 45+2y 27+2x 9x9
{
    for (int y = COLS / 2 - 23; y < COLS / 2 + 24; y++)
    {
        for (int x = LINES / 2 - 13; x < LINES / 2 + 13; x++)
        {
            if (y == COLS / 2 - 23 || y == COLS / 2 + 23)
            {
                //field[x][y] = '|';
                attron(COLOR_PAIR(1));
                mvprintw(x, y, "|");
                attroff(COLOR_PAIR(1));
                refresh();
            }
            else if (x == LINES / 2 - 13 || x == LINES / 2 + 12)
            {
                //field[x][y] = '-';
                attron(COLOR_PAIR(1));
                mvprintw(x, y, "-");
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
    }
}
void fog(const int rows, char field[][rows], char undiscovered[][rows])
{
    const int cols = 24;
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            field[y][x] = '?';
        }
    }
    spawn_player(rows, field, undiscovered);

    draw(rows, field, undiscovered);
}
void game(const int rows, char field[][rows], char undiscovered[][rows])
{
    int level = 1;
    fog(rows, field, undiscovered);
    map(rows, undiscovered, field, level);

    refresh();
    int y_axis = 0;
    int x_axis = 0;

    while (level < 4)

    {
        mvprintw(42, 80, "Your level: %d", level);

        //user input.

        int c = getch(); //input
        movement(rows, field, y_axis, x_axis, c, undiscovered);
        if (level_reach(rows, field, undiscovered) == true)
        {
            level++;
            fog(rows, field, undiscovered);
            map(rows, undiscovered, field, level);
            refresh();
        }
        if (colision_check(rows, field, undiscovered) == true)
        {
            break;
        }
        if (colision_x(rows, field, undiscovered) <= 0)
        {
            break;
        }

        field_of_view(rows, field, y_axis, x_axis);
        draw(rows, field, undiscovered);
        refresh();
    }
    if (colision_check(rows, field, undiscovered) == true || colision_x(rows, field, undiscovered) <= 0)
    {
        mvprintw(47, 80, "Game over, You lost! Press any key to exit.");
        refresh();
        return;
    }

    mvprintw(47, 80, "Congratulations! You won! Press any key to exit");
    refresh();
}

