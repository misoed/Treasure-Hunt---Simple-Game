#define BLANK ' '

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>


//hitboxes
char player[3][5] = {{    
                         '<',
                         '-',
                         '-',
                         '-',
                         '>',
                     },
                     {
                         '<',
                         '-',
                         '-',
                         '-',
                         '>',
                     },
                     {
                         '<',
                         '-',
                         '-',
                         '-',
                         '>',
                     }

};

//if player hits V
bool colision_check(const int rows, char field[][rows], char undiscovered[][rows])
{
    const int cols = 24;
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            if (field[y][x] == '<' || field[y][x] == '>' || field[y][x] == '-') //next level
            {
                if (undiscovered[y][x] == 'V')
                {
                    return true;
                }
            }
        }
    }
    return false;
}
int colision_x(const int rows, char field[][rows], char undiscovered[][rows])
{
    const int cols = 24;
    int counter = 20;
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            if (undiscovered[y][x] == '.') //if hit by X
            {
                counter --;
            }
        }
    }
    return counter;
}
//user input 
void arrow_up(const int rows, char field[][rows], char undiscovered[][rows], int y_axis, int x_axis)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X') //if player hits X
            {
                
                if (undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X')
                {
                    undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = '.';
                }
            }

            field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = player[i][j]; //set new position

            do // !!!!!!!!!!!!!!!!!!!!!!!!!!!!! vykonat len raz
            {
                field[21 - (y_axis - 1) + i][(45 / 2) + x_axis - 2 + j] = ' '; //remove previous position
            } while (y_axis > 999);

            refresh();
        }
    }
}
void arrow_down(const int rows, char field[][rows], char undiscovered[][rows], int y_axis, int x_axis)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X') //if player hits X
            {
                

                if (undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X')
                {
                    undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = '.';
                }
            }

            field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = player[i][j]; //set new position

            do // !!!!!!!!!!!!!!!!!!!!!!!!!!!!! vykonat len raz
            {
                field[21 - (y_axis + 1)][(45 / 2) + x_axis - 2] = ' '; //remove previous position
            } while (y_axis > 999);

            refresh();
        }
    }
}
void arrow_left(const int rows, char field[][rows], char undiscovered[][rows], int y_axis, int x_axis)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X') //if player hits X
            {


                if (undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X')
                {
                    undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = '.';
                }
            }

            field[21 - y_axis + i][(45 / 2) - 2 + x_axis + j] = player[i][j]; //set new position

            do // !!!!!!!!!!!!!!!!!!!!!!!!!!!!! vykonat len raz
            {
                field[21 - (y_axis) + i][(45 / 2) + x_axis + 1 - 2 + j] = ' '; //remove previous position
            } while (x_axis > 999);

            refresh();
        }
    }
}
void arrow_right(const int rows, char field[][rows], char undiscovered[][rows], int y_axis, int x_axis)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X') //if player hits X
            {
                

                if (undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] == 'X')
                {
                    undiscovered[21 - y_axis + i][(45 / 2) + x_axis - 2 + j] = '.';
                }
            }

            field[21 - y_axis + i][(45 / 2) - 2 + x_axis + j] = player[i][j]; //set new position

            do // !!!!!!!!!!!!!!!!!!!!!!!!!!!!! vykonat len raz
            {
                field[21 - (y_axis) + i][(45 / 2) + x_axis - 1 - 2] = ' '; //remove previous position
            } while (x_axis > 999);

            refresh();
        }
    }
}

void behind_fog(const int rows, char undiscovered[][rows], char field[][rows])
{
    const int cols = 24;
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            if (field[y][x] == BLANK)
            {
                field[y][x] = undiscovered[y][x];
            }
            refresh();
        }
    }
}

//field of view
void field_of_view(const int rows, char field[][rows], int y_axis, int x_axis)
{
    for (int i = 1; i < 4; i++) //left-right
    {
        for (int j = 1; j < 4; j++)
        {
            long int up = 0;
            up = (45 / 2) + x_axis - 2 - j;
            if (up < 0 || up >= 37) //to correct movement outsice of field
            {
                if (up < 0)
                {
                    field[21 - y_axis - 1 + i][(45 / 2) + x_axis + 6 - j] = BLANK; //Fov Right
                }
                else
                {
                    field[21 - y_axis - 1 + i][(45 / 2) + x_axis - 2 - j] = BLANK; //FoV left
                }
            }
            else if (up >= 0 && up < 37) //basic main movement
            {
                field[21 - y_axis - 1 + i][(45 / 2) + x_axis - 2 - j] = BLANK; //FoV left
                field[21 - y_axis - 1 + i][(45 / 2) + x_axis + 6 - j] = BLANK; //Fov Right
            }
            refresh();
        }
    }
    for (int i = 1; i < 3; i++) //up-down
    {
        for (int j = 1; j < 6; j++)
        {
            field[21 - y_axis - 3 + i][(45 / 2) + x_axis + 3 - j] = BLANK; //FoV top
            field[21 - y_axis + 2 + i][(45 / 2) + x_axis + 3 - j] = BLANK; //FoV down
            refresh();
        }
    }
}
//draw enemy + enemy functions
void discover_enemy(const int rows, char field[][rows], char undiscovered[][rows])
{
    const int cols = 24;
    int counter = 0;

    while (counter < 5)
    {
        if (colision_check(rows, field, undiscovered) == true)
        {
            return;
        }

        for (int y = 0; y < cols; y++) //from down-left
        {
            for (int x = 0; x < rows; x++)
            {

                if (field[y][x] == 'V')
                {
                    if (undiscovered[y][x + 1] == 'V')
                    {
                        field[y][x + 1] = undiscovered[y][x + 1];
                        if (undiscovered[y - 1][x] == 'V')
                        {
                            field[y - 1][x] = undiscovered[y - 1][x];
                        }
                        else if (undiscovered[y + 1][x] == 'V')
                        {
                            field[y + 1][x] = undiscovered[y + 1][x];
                        }
                    }
                    if (undiscovered[y][x - 1] == 'V')
                    {
                        field[y][x - 1] = undiscovered[y][x - 1];
                        if (undiscovered[y - 1][x] == 'V')
                        {
                            field[y - 1][x] = undiscovered[y - 1][x];
                        }
                        else if (undiscovered[y + 1][x] == 'V')
                        {
                            field[y + 1][x] = undiscovered[y + 1][x];
                        }
                    }
                    if (undiscovered[y - 1][x] == 'V')
                    {
                        field[y - 1][x] = undiscovered[y - 1][x];
                        if (undiscovered[y - 1][x] == 'V')
                        {
                            field[y - 1][x] = undiscovered[y - 1][x];
                        }
                        else if (undiscovered[y + 1][x] == 'V')
                        {
                            field[y + 1][x] = undiscovered[y + 1][x];
                        }
                    }
                    if (undiscovered[y + 1][x] == 'V')
                    {
                        field[y + 1][x] = undiscovered[y + 1][x];
                        if (undiscovered[y - 1][x] == 'V')
                        {
                            field[y - 1][x] = undiscovered[y - 1][x];
                        }
                        else if (undiscovered[y + 1][x] == 'V')
                        {
                            field[y + 1][x] = undiscovered[y + 1][x];
                        }
                    }
                }
                if (field[y][x] == 'V')
                {
                    if (undiscovered[y][x + 1] == BLANK || undiscovered[y][x + 1] == '*') //block right path
                    {
                        if (field[y][x + 1] != BLANK)
                        {
                            for (int i = 1; i < 6; i++)
                            {
                                if (x + i >= 0 && x + i <= 44)
                                {

                                    if (undiscovered[y][x + i] != 'V' && field[y][x + i] == '?')
                                    {
                                        undiscovered[y][x + i] = 'X';
                                    }
                                    if (field[y][x + i] == '?')
                                    {
                                        field[y][x + i] = undiscovered[y][x + i];
                                    }
                                }
                            }
                        }
                    }
                    if (undiscovered[y][x - 1] == BLANK || undiscovered[y][x + 1] == '*') //block left path
                    {
                        if (field[y][x - 1] != BLANK)
                        {

                            for (int i = 1; i < 6; i++)
                            {
                                if (x - i >= 0 && x + i <= 44)
                                {

                                    if (undiscovered[y][x - i] != 'V' && field[y][x - i] == '?')
                                    {
                                        undiscovered[y][x - i] = 'X';
                                    }
                                    if (field[y][x - i] == '?')
                                    {
                                        field[y][x - i] = undiscovered[y][x - i];
                                    }
                                }
                            }
                        }
                    }
                    if (undiscovered[y + 1][x] == BLANK || undiscovered[y][x + 1] == '*') //block up path
                    {
                        if (field[y + 1][x] != BLANK)
                        {

                            for (int i = 1; i < 4; i++)
                            {

                                if (undiscovered[y + i][x] != 'V' && field[y + i][x] == '?')
                                {

                                    undiscovered[y + i][x] = 'X';
                                }
                                if (field[y + i][x] == '?')
                                {
                                    field[y + i][x] = undiscovered[y + i][x];
                                }
                            }
                        }
                    }
                    if (undiscovered[y - 1][x] == BLANK || undiscovered[y][x + 1] == '*') //block down path
                    {
                        if (field[y - 1][x] != BLANK)
                        {

                            for (int i = 1; i < 4; i++)
                            {

                                if (undiscovered[y - i][x] != 'V' && field[y - i][x] == '?')
                                {
                                    undiscovered[y - i][x] = 'X';
                                }
                                if (field[y - i][x] == '?')
                                {
                                    field[y - i][x] = undiscovered[y - i][x];
                                }
                            }
                        }
                    }
                }
            }
        }
        behind_fog(rows, undiscovered, field);
        counter++;
    }
}
//draw map
void draw(const int rows, char field[][rows], char undiscovered[][rows])
{
    if (colision_check(rows, field, undiscovered) == true)
    {
        return;
    }

    discover_enemy(rows, field, undiscovered);
    behind_fog(rows, undiscovered, field);
    const int cols = 24;

    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            mvprintw(y + LINES / 2 - 12, x + COLS / 2 - 22, "%c", field[y][x]);
            if (field[y][x] == 'X')
            {
                attron(COLOR_PAIR(2));
                mvprintw(y + LINES / 2 - 12, x + COLS / 2 - 22, "%c", field[y][x]);
                attroff(COLOR_PAIR(2));
            }
            if (field[y][x] == '.')
            {
                attron(COLOR_PAIR(2));
                mvprintw(y + LINES / 2 - 12, x + COLS / 2 - 22, "%c", field[y][x]);
                attroff(COLOR_PAIR(2));
            }
            if (field[y][x] == 'V')
            {
                attron(COLOR_PAIR(1));
                mvprintw(y + LINES / 2 - 12, x + COLS / 2 - 22, "%c", field[y][x]);
                attroff(COLOR_PAIR(1));
            }
            if (field[y][x] == '?')
            {
                attron(COLOR_PAIR(4));
                mvprintw(y + LINES / 2 - 12, x + COLS / 2 - 22, "%c", field[y][x]);
               
                attroff(COLOR_PAIR(4));
            }
            
            
            
            refresh();
        }
    }
}

//if player touches * = next level
bool level_reach(const int rows, char field[][rows], char undiscovered[][rows])
{
    const int cols = 24;
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            if (undiscovered[y][x] == '*') //next level
            {
                if (field[y][x] == '<' || field[y][x] == '>' || field[y][x] == '-')
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//player movement
void movement(const int rows, char field[][rows], int y_axis, int x_axis, int c, char undiscovered[][rows])
{
    do
    {
        mvprintw(45,80,"You have %d lives left!", colision_x(rows,field,undiscovered));
        refresh();
        if (colision_x(rows,field,undiscovered) <=0)
        {
            return;
        }
        
        if ((colision_check(rows, field, undiscovered) == true))
        {
            return;
        }

        c = getch();

        switch (c)
        {

        case KEY_LEFT:

            if (x_axis < 21 && x_axis > -21)
            {
                if (x_axis == -20)
                {
                    x_axis = -19;
                }

                x_axis -= 1;
                arrow_left(rows, field, undiscovered, y_axis, x_axis);
                field_of_view(rows, field, y_axis, x_axis);
                draw(rows, field, undiscovered);
                break;
            }
        case KEY_RIGHT:

            if (x_axis < 21 && x_axis > -21)
            {
                if (x_axis == 20)
                {
                    x_axis -= 1;
                }

                x_axis += 1;

                arrow_right(rows, field, undiscovered, y_axis, x_axis);
                field_of_view(rows, field, y_axis, x_axis);
                draw(rows, field, undiscovered);
                break;
            }
        case KEY_UP:

            if (y_axis < 22 && y_axis >= 0)
            {
                if (y_axis == 21)
                {
                    y_axis -= 1;
                }

                y_axis += 1;
                arrow_up(rows, field, undiscovered, y_axis, x_axis);
                field_of_view(rows, field, y_axis, x_axis);
                draw(rows, field, undiscovered);
                break;
            }
        case KEY_DOWN:

            if (y_axis < 22 && y_axis > 0)
            {
                y_axis -= 1;

                arrow_down(rows, field, undiscovered, y_axis, x_axis);
                field_of_view(rows, field, y_axis, x_axis);
                draw(rows, field, undiscovered);
                break;
            }
        default:
            continue;
            break;
        }
        refresh();
    } while (level_reach(rows, field, undiscovered) == false);
}

void map(const int rows, char undiscovered[][rows], char field[][rows], int level)
{
    const int cols = 24;
    //generate BLANK field
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            undiscovered[y][x] = field[y][x];
        }
    }

    //randomise placement of enemies
    int enemies = 0;
    while (enemies < 5+level)
    {
        int random_x = (rand() % rows);
        int random_y = (rand() % cols);
        ///////////////////////////////////////////////
        if (undiscovered[random_y][random_x] == '?' && (undiscovered[random_y + 3][random_x + 5] == '?') && (undiscovered[random_y + 3][random_x] == '?') && (undiscovered[random_y][random_x + 5] == '?') && random_x < 41 && random_y < 21)
        {

            for (int y = random_y; y < random_y + 3; y++)
            {
                for (int x = random_x; x < random_x + 5; x++)
                {
                    undiscovered[y][x] = 'V';
                }
            }
            enemies++;
        }
    }
    //generate next level
    int treasure = 0;
    while (treasure < 1)
    {
        int random_x = (rand() % rows);
        int random_y = (rand() % cols);
        ///////////////////////////////////////////////
        if (undiscovered[random_y][random_x] == '?' && (undiscovered[random_y + 3][random_x + 5] == '?') && (undiscovered[random_y + 3][random_x] == '?') && (undiscovered[random_y][random_x + 5] == '?') && random_x < 41 && random_y < 21)
        {

            for (int y = random_y; y < random_y + 3; y++)
            {
                for (int x = random_x; x < random_x + 5; x++)
                {
                    undiscovered[y][x] = '*';
                }
            }
            treasure++;
        }
    }
    //remove fog and player from map
    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            if (undiscovered[y][x] == '?' || undiscovered[y][x] == '-' || undiscovered[y][x] == '<' || undiscovered[y][x] == '>')
            {
                undiscovered[y][x] = BLANK;
            }
        }
    }
}
//player spawn
void spawn_player(const int rows, char field[][rows], char undiscovered[][rows])
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            field[21 + i][(44 / 2) - 2 + j] = player[i][j];

        }
    }
}
