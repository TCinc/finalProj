/** snakefuncts.h
* ===========================================================
* Name: Charleen Muyot, 25 Nov 19
* Section: T3/T4
* Documentation:
* ===========================================================  */

#ifndef SNAKE2_SNAKEFUNCTS_H
#define SNAKE2_SNAKEFUNCTS_H

#endif //SNAKE2_SNAKEFUNCTS_H

#include <time.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct coord {
    int x;
    int y;
} coord;

typedef struct nameStruct{
    char first[20];
    char last [30];
}nameStruct;

typedef enum{
    RIGHT,
    LEFT,
    UP,
    DOWN
} direction;

direction currentDir = RIGHT;
coord sParts[100] = {};

void initialize();
void snakeInit(int tailLen, bool gameOver, int score, int xmax, int ymax);
void putFood(int xmax, int ymax, coord *food);
void draw(coord* point);
void bodyGrow(int tailLen);
void drawScreen(int xmax, int ymax, int tailLen, int score, bool gameOver, coord *food,nameStruct namesOnFile );
void readFile(nameStruct namesOnFile[]);
