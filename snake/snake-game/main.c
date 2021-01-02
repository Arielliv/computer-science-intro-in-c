// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define NUMBER_OF_COLS 75
#define NUMBER_OF_ROWS 25
#define TOTAL_SNAKE_SIZE 25
#define BORD_SIGN '#'
#define EMPTY_SIGN ' '
#define SNAKE_SIGN '@'
#define FOOD_SIGN '$'
#define UP 72  // Up Arrow
#define DOWN 80 // Down Arrow
#define LEFT 75  // Left Arrow
#define RIGHT 77  // Right Arrow
#define ESC 27  // Escape Key

typedef struct _Point {
    int x;
    int y;
} Point;

void gotoxy(int y, int x);

int getKey();

int getUserChoice();

int
playGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point snake[20], int snakeSize, int *eatenFoodCounter);

void intBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point snake[20], int snakeSize);

void setRandomPoint(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point *point);

void setSignInPointInBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point point, char sign);

void printBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols);

void playMove(char *choice, Point *currentPosition);

// (1 - true or 0 - false)
void updateSnake(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point newPosition, int moves);

int checkIfEtan(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point currentPosition);

void printSignOfPointInGameBoard(Point position, char sign);

int checkIfPositionIsSnakeBody(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point currentPosition);

int compareTwoPositions(Point position1, Point position2);

void initSnake(Point snake[TOTAL_SNAKE_SIZE], int snakeSize);

void printGameOver();

void main() {
    char snakeBoard[NUMBER_OF_ROWS][NUMBER_OF_COLS];
    Point snakePositions[TOTAL_SNAKE_SIZE];
    int eatenFoodCounter = 0;
    int userChoice;
    int isWon = 0, isLost = 0;

    // Use current time as seed for random generator
    srand(time(NULL));
    while (isWon == 0) {
        userChoice = getUserChoice();
        if (userChoice == 0) {
            printf("Bye");
        } else {
            system("cls");
            isLost = playGame(snakeBoard, NUMBER_OF_ROWS, NUMBER_OF_COLS, snakePositions, TOTAL_SNAKE_SIZE,
                              &eatenFoodCounter, &isWon);
            system("cls");
            if (isLost == 1) {
                printGameOver();
            }

        }
    }

}

void printGameOver() {
    printf("##################################\n"
           "GAME OVER\n"
           "##################################\n");
}

int getUserChoice() {
    int userChoice;
    printf("*******************************************************\n"
           "* Pick Your Level, to exit press 0\n"
           "* 0 -Exit\n"
           "* 1 - Basic Level\n"
           "* 2 - Intermidiate LEvel\n"
           "* 3 - Advanced Level\n"
           "*******************************************************\n");
    scanf("%d", &userChoice);
    return userChoice;
}

int
playGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point snake[TOTAL_SNAKE_SIZE], int snakeSize,
         int *eatenFoodCounter,
         int *isWon) {
    char choice = RIGHT;
    int shouldGrow = 0;
    int isLost = 0;
    int realSnakeSize = 10;
    int moves = 0;
    Point currentPosition, newFoodLocation;
    currentPosition.x = 12;
    currentPosition.y = 30;
    intBoard(snakeBoard, rows, cols, snake, snakeSize);

    printBoard(snakeBoard, rows, cols);
    while (choice != ESC && isLost == 0 && *isWon == 0) {
        Sleep(500);
        playMove(&choice, &currentPosition);
        if (checkIfPositionIsSnakeBody(snake, snakeSize, currentPosition) == 1) {
            isLost = 1;
        } else {
            moves++;
            if (currentPosition.x >= rows - 1 || currentPosition.y >= cols - 1 || currentPosition.x <= 0 ||
                currentPosition.y <= 0) {
                isLost = 1;
            } else {
                shouldGrow = checkIfEtan(snakeBoard, rows, cols, currentPosition);
                if (shouldGrow == 1) {
                    *eatenFoodCounter += 1;
                    if (*eatenFoodCounter == 10) {
                        *isWon = 1;
                    } else {
                        realSnakeSize += 1;
                        setRandomPoint(snake, snakeSize, &newFoodLocation);
                        printf("rand %d-%d", newFoodLocation.x, newFoodLocation.y);
                        printSignOfPointInGameBoard(newFoodLocation, FOOD_SIGN);
                        setSignInPointInBoard(snakeBoard, rows, cols, currentPosition, EMPTY_SIGN);
                        setSignInPointInBoard(snakeBoard, rows, cols, newFoodLocation, FOOD_SIGN);
                        // reset flag
                        shouldGrow = 0;
                    }
                }
            }
            updateSnake(snake, realSnakeSize, currentPosition, moves);
        }
    }
    return isLost;
}

int checkIfEtan(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point currentPosition) {
    if (snakeBoard[currentPosition.x][currentPosition.y] == FOOD_SIGN) {
        return 1;
    } else {
        return 0;
    }
}

int compareTwoPositions(Point position1, Point position2) {
    if (position1.x == position2.x && position1.y == position2.y) {
        return 1;
    } else { return 0; }
}

int checkIfPositionIsSnakeBody(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point currentPosition) {
    int i;
    int isInside = 0;
    for (i = 0; i < snakeSize - 1 && isInside == 0; i++) {
        if (compareTwoPositions(snake[i], currentPosition) == 1) {
            isInside = 1;
        }
    }
    return isInside;
}

void initSnake(Point snake[TOTAL_SNAKE_SIZE], int snakeSize) {
    int i;
    Point initPosition;
    initPosition.x = 0;
    initPosition.y = 0;
    for (i = 0; i < snakeSize - 1; i++) {
        snake[i] = initPosition;
    }
}

void intBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point snake[TOTAL_SNAKE_SIZE], int snakeSize) {
    int i, j;
    Point foodLocation, currentPoint;

    initSnake(snake, snakeSize);

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            currentPoint.x = i;
            currentPoint.y = j;
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                setSignInPointInBoard(snakeBoard, rows, cols, currentPoint, BORD_SIGN);
            } else {
                setSignInPointInBoard(snakeBoard, rows, cols, currentPoint, EMPTY_SIGN);
            }
        }
    }

    setRandomPoint(snake, snakeSize, &foodLocation);
    setSignInPointInBoard(snakeBoard, rows, cols, foodLocation, FOOD_SIGN);
}

void setRandomPoint(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point *point) {
    Point randomPosition;
    randomPosition.x = 0;
    randomPosition.y = 0;
    while (checkIfPositionIsSnakeBody(snake, snakeSize, randomPosition) == 1) {
        printf("random %d-%d", randomPosition.x, randomPosition.y);
        randomPosition.x = 1 + rand() % ((int) NUMBER_OF_ROWS - 2);
        randomPosition.y = 1 + rand() % ((int) NUMBER_OF_COLS - 2);
    }
    point->x = randomPosition.x;
    point->y = randomPosition.y;
}

void setSignInPointInBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Point position, char sign) {
    snakeBoard[position.x][position.y] = sign;
}

void printSignOfPointInGameBoard(Point position, char sign) {
    gotoxy(position.x, position.y);
    printf("%c", sign);
    gotoxy(26, 81);
}

void printBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%c", snakeBoard[i][j]);
        }
        printf("\n");
    }
}

void playMove(char *choice, Point *currentPosition) {
    // only if a key was hit we read what key code it was
    if (_kbhit()) // if any key was hit
        *choice = getKey();  // change direction
    // make a move in current direction if no change
    switch (*choice) {
        case RIGHT:
            currentPosition->y++;
            break;
        case DOWN:
            currentPosition->x++;
            break;
        case LEFT:
            currentPosition->y--;
            break;
        case UP:
            currentPosition->x--;
            break;
    }
    printSignOfPointInGameBoard(*currentPosition, SNAKE_SIGN);
    printf("current %d-%d", currentPosition->x, currentPosition->y);
}

void updateSnake(Point snake[TOTAL_SNAKE_SIZE], int snakeSize, Point newPosition, int moves) {
    int i;
    Point lastPosition = snake[snakeSize - 1];
    for (i = snakeSize - 2; i >= 0; i--) {
        snake[i + 1] = snake[i];
    }
    // first should be updated with new position
    snake[0] = newPosition;
    if (moves > 10) {
        printSignOfPointInGameBoard(lastPosition, EMPTY_SIGN);
    }
}

// This function moves the cursor to the line y and column x.
// (0,0) is the upper left corner of the screen.
void gotoxy(int x, int y) {
    printf("\x1b[%d;%df", x + 1, y + 1);
}

// This function gets keyCodes for special keys such as arrows , escape and others
// It returns the Key code such as 72 for arrow up, 27 for Escape...
int getKey() {
    char KeyStroke = _getch();
    if (KeyStroke == 0 || KeyStroke == -32)
        KeyStroke = _getch();
    return (KeyStroke);
}