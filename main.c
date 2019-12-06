/** main.c
* ===========================================================
* Name: Charleen Muyot, 25 Nov 19
* Section: T3/T4
* Documentation: C3C Ymani Nesmith helped me with getting the project started by showing me the contents of an
 * initialize function (which is require for all programs with graphics) and what each line does.
 * Referenced a section of code made by petrvolny on Github. Only looked at function "setDirection"
 * as it made me realize that using a switch for the direction input would be easier to code and read compared to
 * using if-else statements.
 * C3C Preston Albury helped me with a problem in my code that stated I had duplicate
 * definitions despite there only being one in the h file. He suggested that instead of having a
 * separate c file for the functions, I should instead just put them all in the bottom of main.c.
 * C3C Lauren Humphreys helped me get rid of global variables in my main.c by informing me that since my functions
 * are already passing the variables, I can just define them in main.
 * Referenced the code of Sheep42 on Github to help with a number of functions. The code helped me understand how
 * to make the snake and food interact when they collide, and having the resulting interaction make not only the
 * food item disappear, but also the snake grow. Previously, I had attempted to use a for-loop to keep checking
 * to see if a collision occurred, adding a segment when a collision did occur.
 * From the same user, I also referenced the code to learn how to draw items on the display as I have no experience in
 * that area. This includes initializing the food and snake's points so that they can be moved. This was vital in me
 * understanding how to create a point and move that same point. Despite these many references, I have made many
 * changes to the original code so that it is tailored for my project.
* ===========================================================  */

#include <memory.h>
#include "snakefuncts.h"

int main(int argc, char *argv[]) {
    int ymax = 0;
    int xmax = 0;
    int moveX = 0;
    int moveY = 0;
    int tailLen = 1;
    int score = 0;
    int inKey; //key inputs

    bool gameOver = false;

    coord *food = (coord *) malloc(sizeof(coord));
    nameStruct *namesOnFile = (nameStruct*) malloc(sizeof(nameStruct));

    initialize();
    snakeInit(tailLen, gameOver, score, xmax, ymax);

    putFood(xmax, ymax, food);

    //get max x and y values for play area
    getmaxyx(stdscr, ymax, xmax);

    while (1) {
            //Snake Controls
            inKey = getch();

            switch(inKey) {
                case KEY_UP:
                    currentDir = UP;
                    break;
                case KEY_DOWN:
                    currentDir = DOWN;
                    break;
                case KEY_RIGHT:
                    currentDir = RIGHT;
                    break;
                case KEY_LEFT:
                    currentDir = LEFT;
                    break;
            }

            //Movement logic, takes the snake controls and converts it into movement
            moveX = sParts[0].x;
            moveY = sParts[0].y;

            if (currentDir == RIGHT) {
                moveX++;
            }

            else if (currentDir == LEFT){
                moveX--;
            }

            else if (currentDir == UP){
                moveY--;
            }

            else if (currentDir == DOWN){
                moveY++;
            }

            //Allows for interaction between snake and food when they collide
            if ((moveX == food->x) && (moveY == food->y)) {
                coord tail;

                tail.x = moveX;
                tail.y = moveY;

                sParts[tailLen] = tail;

                if (tailLen < 100)
                    tailLen++;

                score = score + 1;
                putFood(xmax, ymax, food);
            }
            else {

                //Detects when snake hits self
                for (int i = 0; i < tailLen; i++) {
                    if (moveX == sParts[i].x && moveY == sParts[i].y) {
                        gameOver = true;
                        break;
                    }
                }

                sParts[tailLen - 1].x = moveX;
                sParts[tailLen - 1].y = moveY;
            }

        bodyGrow(tailLen);

            if (gameOver) {
                sleep(2);
                snakeInit(tailLen, gameOver, score, xmax, ymax);
            }

            //Border detection
            if ((moveX >= xmax || moveX < 0) || (moveY >= ymax || moveY < 0)) {
                gameOver = true;
            }

            drawScreen(xmax,ymax, tailLen, score, gameOver, food, *namesOnFile);
        }

        endwin();

        return 0;
    }

//Initializes graphics.
void initialize() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(20);
    curs_set(0);
}

//Initializes snake's attributes.
void snakeInit(int tailLen, bool gameOver, int score, int xmax, int ymax) {

    //initial coordinates of snake
    int j = 0;

    coord currPoint;

    currPoint.x = xmax/2;
    currPoint.y = ymax/2;

    sParts[j] = currPoint;

    refresh();
}

//Random generator for food.
void putFood(int xmax, int ymax, coord *food) {

    food->x = (rand() % (xmax - 15)) + 5;
    food->y = (rand() % (ymax - 15)) + 5;
}

//Tracks snake
void draw(coord *point) {
    mvprintw(point->y, point->x, "*");
}


//Snake body does not stop when it collides with food. Food obtained adds to the snake's body.
void bodyGrow(int tailLen) {
   coord temp = sParts[tailLen - 1];

    for(int i = tailLen - 1; i > 0; i--) {
        sParts[i] = sParts[i-1];
    }

    sParts[0] = temp;
}

//Create simple graphics on the screen
void drawScreen(int xmax, int ymax, int tailLen, int score, bool gameOver, coord *food, nameStruct namesOnFile) {
    clear();


    //Draws more than one section of the snake.
    for(int i = 0; i < tailLen; i++) {
        draw(&sParts[i]);
    }

    draw(food);

    mvprintw(1, 0, "Score: %d", score);

    refresh();

    if(gameOver) {
        //readFile(&namesOnFile); //readFile function supposed to read first and last name on file
        mvprintw(ymax / 2, xmax / 2, "Game Over!");
        //mvprintw(ymax/2 xmax/2 "%s %s ", namesOnFile.first, namesOnFile.last);//print out name

    }

    //Snake speed
    usleep(40000);
}

//Read name off of a file, place values in nameStruct
void readFile(nameStruct namesOnFile[]) {

    int lines = 1;
    int i;

        // Open an input file for reading
        FILE *in = fopen("names.txt", "r");

        if (in == NULL) {
            printf("Error opening data file");
            exit(1);
        }

    for (i = 0; i < lines; ++i) {
            fscanf(in, "%s %s", namesOnFile[i].first , namesOnFile[i].last);
        }

        fclose(in);

}

