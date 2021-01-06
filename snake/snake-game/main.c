// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define NUMBER_OF_COLS 75
#define NUMBER_OF_ROWS 25
#define TOTAL_SNAKE_SIZE 20
#define BORD_SIGN '#'
#define EMPTY_SIGN ' '
#define SNAKE_SIGN '@'
#define FOOD_SIGN '$'
#define UP 72  // Up Arrow
#define DOWN 80 // Down Arrow
#define LEFT 75  // Left Arrow
#define RIGHT 77  // Right Arrow
#define ESC 27  // Escape Key

// position object
typedef struct _Position {
    int x;
    int y;
} Position;

// This function moves the cursor to the line y and column x.
// (0,0) is the upper left corner of the screen.
void gotoxy(int x, int y);

// This function gets keyCodes for special keys such as arrows , escape and others
// It returns the Key code such as 72 for arrow up, 27 for Escape...
int getKey();

// get user choice for lvl of the game, or to exit
int getUserChoice();

// get user choice for which king of level in the game
int playGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize,
             int *eatenFoodCounter);

// starts the game according to user choice lvl
int
startGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[20], int snakeSize,
          int *eatenFoodCounter, int *isWon);

// play a move according to user press (left, right, up, down) updates board view and board object - including snake view and object
void playMove(char *choice, Position *currentPosition, char snakeBoard[][NUMBER_OF_COLS], int rows, int cols,
              Position snake[TOTAL_SNAKE_SIZE], int snakeSize,
              int *eatenFoodCounter,
              int *isWon, int *isLost, int *moves, int *realSnakeSize);

// get move direction, updates current position on board
void getMove(char *choice, Position *currentPosition);

// initiate board object , calls for initiation of snake object
void initBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[20], int snakeSize);

// initiate snake and print board
void initGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize);

// initiate the snake - array of positions with defaults for start
void initSnake(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, int boardRows, int boardCols);

// set random position on passed position object
void setRandomPosition(Position *snake, int snakeSize, Position *position);

// update board object according to sign and position
void setSignInPositionInBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position position, char sign);

// print board of the game (boundaries)
void printBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols);

// prints game resolution (win or lose)
void printGameResolution();

// update snake with new position of head, delete last position according to snake size (only after 10 moves of snake in game)
void updateSnake(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, Position newPosition, int moves);

// print sign ob the board according to position
void printSignOfPositionInGameBoard(Position position, char sign);

// check if ate himself (snake) return - (1 - true or 0 - false)
int checkIfPositionIsSnakeBody(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, Position currentPosition);

// check if same position return - (1 - true or 0 - false)
int compareTwoPositions(Position position1, Position position2);

// check if snake ate food return - (1 - true or 0 - false)
int checkIfEtan(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position currentPosition);

void main() {
    char snakeBoard[NUMBER_OF_ROWS][NUMBER_OF_COLS];
    Position snakePositions[TOTAL_SNAKE_SIZE];
    int eatenFoodCounter = 0;

    // Use current time as seed for random generator
    srand(time(NULL));
    playGame(snakeBoard, NUMBER_OF_ROWS, NUMBER_OF_COLS, snakePositions, TOTAL_SNAKE_SIZE,
             &eatenFoodCounter);

}

void printGameResolution(int isWon) {
    printf("##################################\n");
    if (isWon == 1) {
        printf("you win!\n");
    } else {
        printf("GAME OVER\n");
    }
    printf("##################################\n");
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

int playGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize,
             int *eatenFoodCounter) {
    int userChoice;
    int isLost;
    int isWon = 0;

    while (isWon == 0) {
        userChoice = getUserChoice();
        if (userChoice == 0) {
            printf("Bye");
            return 1;
        } else if (userChoice > 0 && userChoice < 4) {
            system("cls");
            isLost = startGame(snakeBoard, NUMBER_OF_ROWS, NUMBER_OF_COLS, snake, TOTAL_SNAKE_SIZE,
                               eatenFoodCounter, &isWon);
            system("cls");
            if (isLost == 1 || isWon == 1) {
                printGameResolution(isWon);
                isLost = 0;
                isWon = 0;
            }
        }
    }
}

int
startGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize,
          int *eatenFoodCounter,
          int *isWon) {
    char choice = ' ';

    int isLost = 0;

    Position currentPosition;
    currentPosition.x = rows / 2;
    currentPosition.y = cols / 2;
    int moves = 0;
    int realSnakeSize = 10;

    initGame(snakeBoard, rows, cols, snake, snakeSize);

    while (choice != UP && choice != DOWN && choice != LEFT && choice != RIGHT && choice != ESC) {
        choice = getKey();
    }

    while (choice != ESC && isLost == 0 && *isWon == 0) {
        playMove(&choice, &currentPosition, snakeBoard, rows, cols, snake, snakeSize, eatenFoodCounter, isWon,
                 &isLost, &moves, &realSnakeSize);
    }

    return isLost;
}

void initGame(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize) {
    initBoard(snakeBoard, rows, cols, snake, snakeSize);
    printBoard(snakeBoard, rows, cols);
}

void initSnake(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, int boardRows, int boardCols) {
    int i;
    Position initPosition;
    initPosition.x = boardRows / 2;
    initPosition.y = boardCols / 2;
    for (i = 0; i < snakeSize - 1; i++) {
        snake[i] = initPosition;
    }
}

void initBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position snake[TOTAL_SNAKE_SIZE], int snakeSize) {
    int i, j;
    Position foodLocation, currentPosition;

    initSnake(snake, snakeSize, rows, cols);

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            currentPosition.x = i;
            currentPosition.y = j;
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                setSignInPositionInBoard(snakeBoard, rows, cols, currentPosition, BORD_SIGN);
            } else {
                setSignInPositionInBoard(snakeBoard, rows, cols, currentPosition, EMPTY_SIGN);
            }
        }
    }

    setRandomPosition(snake, snakeSize, &foodLocation);
    setSignInPositionInBoard(snakeBoard, rows, cols, foodLocation, FOOD_SIGN);
}

void setRandomPosition(Position *snake, int snakeSize, Position *position) {
    Position randomPosition;
    randomPosition.x = randomPosition.x = 1 + rand() % ((int) NUMBER_OF_ROWS - 2);
    randomPosition.y = randomPosition.y = 1 + rand() % ((int) NUMBER_OF_COLS - 2);
    while (checkIfPositionIsSnakeBody(snake, snakeSize, randomPosition) == 1) {

        randomPosition.x = 1 + rand() % ((int) NUMBER_OF_ROWS - 2);
        randomPosition.y = 1 + rand() % ((int) NUMBER_OF_COLS - 2);
    }
    position->x = randomPosition.x;
    position->y = randomPosition.y;
}

void setSignInPositionInBoard(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position position, char sign) {
    snakeBoard[position.x][position.y] = sign;
}

void printSignOfPositionInGameBoard(Position position, char sign) {
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

void playMove(char *choice, Position *currentPosition, char snakeBoard[][NUMBER_OF_COLS], int rows, int cols,
              Position snake[TOTAL_SNAKE_SIZE], int snakeSize,
              int *eatenFoodCounter,
              int *isWon, int *isLost, int *moves, int *realSnakeSize) {

    int shouldGrow = 0;
    Position newFoodLocation;

    Sleep(1000);
    getMove(choice, currentPosition);
    if (checkIfPositionIsSnakeBody(snake, snakeSize, *currentPosition) == 1 || currentPosition->x >= rows - 1 ||
        currentPosition->y >= cols - 1 || currentPosition->x <= 0 ||
        currentPosition->y <= 0) {
        *isLost = 1;
    } else {
        *moves += 1;
        shouldGrow = checkIfEtan(snakeBoard, rows, cols, *currentPosition);
        if (shouldGrow == 1) {
            *eatenFoodCounter += 1;
            if (*eatenFoodCounter == 10) {
                *isWon = 1;
            } else {
                *realSnakeSize += 1;
                setRandomPosition(snake, snakeSize, &newFoodLocation);
                printSignOfPositionInGameBoard(newFoodLocation, FOOD_SIGN);
                setSignInPositionInBoard(snakeBoard, rows, cols, *currentPosition, EMPTY_SIGN);
                setSignInPositionInBoard(snakeBoard, rows, cols, newFoodLocation, FOOD_SIGN);
                // reset flag
                shouldGrow = 0;
            }
        }
        updateSnake(snake, *realSnakeSize, *currentPosition, *moves);
    }
}

void getMove(char *choice, Position *currentPosition) {
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
    printSignOfPositionInGameBoard(*currentPosition, SNAKE_SIGN);
}

void updateSnake(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, Position newPosition, int moves) {
    int i;
    Position lastPosition = snake[snakeSize - 1];
    for (i = snakeSize - 2; i >= 0; i--) {
        snake[i + 1] = snake[i];
    }
    // first should be updated with new position
    snake[0] = newPosition;
    if (moves > 10) {
        printSignOfPositionInGameBoard(lastPosition, EMPTY_SIGN);
    }
}

void gotoxy(int x, int y) {
    printf("\x1b[%d;%df", x + 1, y + 1);
}

int getKey() {
    char KeyStroke = _getch();
    if (KeyStroke == 0 || KeyStroke == -32)
        KeyStroke = _getch();
    return (KeyStroke);
}

int checkIfEtan(char snakeBoard[][NUMBER_OF_COLS], int rows, int cols, Position currentPosition) {
    if (snakeBoard[currentPosition.x][currentPosition.y] == FOOD_SIGN) {
        return 1;
    } else {
        return 0;
    }
}

int compareTwoPositions(Position position1, Position position2) {
    if (position1.x == position2.x && position1.y == position2.y) {
        return 1;
    } else {
        return 0;
    }
}

int checkIfPositionIsSnakeBody(Position snake[TOTAL_SNAKE_SIZE], int snakeSize, Position currentPosition) {
    int i;
    int isInside = 0;
    for (i = 0; i < snakeSize - 1 && isInside == 0; i++) {
        if (compareTwoPositions(snake[i], currentPosition) == 1) {
            isInside = 1;
        }
    }
    return isInside;
}
