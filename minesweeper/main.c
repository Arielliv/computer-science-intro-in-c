/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_MINES 8
#define NUMBER_OF_COLS 10
#define NUMBER_OF_ROWS 10
#define MINE_SIGN 'M'
#define UN_CLICKED_SIGN 'X'

// get user board choice - prints menu and get user selection ( for first part only 1 and 0 works )
int getUserBoardSizeChoice();

// check if cell was already revealed, return (1 - true or 0 - false) value
int isCellRevealed(int val);

// check if cell is a mine, return (1 - true or 0 - false) value
int isACellMine(int val);

// initiate min sweeper board with mines and calculated cells
void initMineSweeperBoard(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                          int minePlacesRows, int minePlacesCols);

// prints mine sweeper board view
void printMineSweeperBoardView(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols);

// prints cell inside mine sweeper board view
void printCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition, int colPosition);

// print header of the mine sweeper board with numbers of positions
void printHeaderOfBoard(int numberOfCells);

// print line of _ according to number of cells
void printLineByCell(int numberOfCells);

// handles click updates in mineSweeperBoard after clicking specific cell
// get user input for click
// return (1 - true or 0 - false) if selected mine -> then lose
int handleClickOnBoard(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                       int minePlacesRows, int minePlacesCols);

// fill array with number of random mines positions (according to passed number of mines)
void fillWithMines(int minePlaces[][2], int rows, int cols);

// calculates number of mines around the cell, if mine returns 9
int calcNumberOfMinesAroundCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition,
                                int colPosition);

// check if won the game - according to number of choices done
int checkIfWonTheGame(int numberOfTurns, int rows, int cols, int numberOfMines);

// check if cell in board suppose to be a mine
int isInsideMineArray(int minePlaces[][2], int minePlacesRows, int minePlacesCols, int currentRow, int currentCol);

// a code of mine sweeper game
int main() {
    int isWin = 0, isLose = 0, turnNumber = 0;
    int boardSizeChoice = -1;

    // will be filled by user choice next version
    int rows = NUMBER_OF_ROWS, cols = NUMBER_OF_COLS;
    int mineSweeperBoard[NUMBER_OF_ROWS][NUMBER_OF_COLS];

    int minePlaces[NUMBER_OF_MINES][2];
    // Use current time as seed for random generator
    srand(time(NULL));

    // in first stage only expect to get 1 or 0
    while (boardSizeChoice != 1 && boardSizeChoice != 0) {
        boardSizeChoice = getUserBoardSizeChoice();
    }

    if ((boardSizeChoice >= 0 && boardSizeChoice < 5)) {
        if (boardSizeChoice == 0) {
            printf("Bye");
        } else {
            fillWithMines(minePlaces, NUMBER_OF_MINES, 2);
            initMineSweeperBoard(mineSweeperBoard, rows, cols, minePlaces, NUMBER_OF_MINES, 2);

            printMineSweeperBoardView(mineSweeperBoard, rows, cols);

            while (isWin == 0 && isLose == 0) {
                isLose = handleClickOnBoard(mineSweeperBoard, rows, cols,
                                            minePlaces,
                                            NUMBER_OF_MINES,
                                            2);
                turnNumber++;
                isWin = checkIfWonTheGame(turnNumber, rows - 2, cols - 2, NUMBER_OF_MINES);
            }

            if (isLose == 1) {
                printf("You've hit a bomb! Game over!");
            } else if (isWin == 1) {
                printf("You wom!! congratulations! CHAMPION!");
            }
        }
    }
}

int getUserBoardSizeChoice() {
    int boardSizeChoice;
    printf("Welcome to Minesweeper!\n"
           "\n"
           "Please choose one of the following options and enter it's number:\n"
           "\n"
           "1 - for size 8X8\n"
           "\n"
           "2 - for size 12X12\n"
           "\n"
           "3 - for size 15X15\n"
           "\n"
           "4 - for custom size\n"
           "\n"
           "0 - Exit");

    scanf("%d", &boardSizeChoice);
    return boardSizeChoice;
}

void initMineSweeperBoard(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols,
                          int minePlaces[][2],
                          int minePlacesRows, int minePlacesCols) {
    int i, y;
    for (i = 0; i < rows; i++) {
        for (y = 0; y < cols; y++) {
            if (isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, i, y) == 1) {
                mineSweeperBoardView[i][y] = 9;
            }
        }
    }
    for (i = 0; i < rows; i++) {
        for (y = 0; y < cols; y++) {

            // get cell score -  how many mines around it
            int cellScore = calcNumberOfMinesAroundCell(mineSweeperBoardView, rows, cols, i, y);
            if (cellScore != 9) {
                mineSweeperBoardView[i][y] = cellScore;
            }
        }
    }
}

void printCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition, int colPosition) {
    if (isCellRevealed(mineSweeperBoard[rowPosition][colPosition]) == 1) {
        // if no mines around cell - print blank else print cell score
        if (mineSweeperBoard[rowPosition][colPosition] % 10 == 9) {
            printf("%c | ", MINE_SIGN);
        } else if (mineSweeperBoard[rowPosition][colPosition] % 10 == 0) {
            printf("  | ");
        } else {
            printf("%d | ", mineSweeperBoard[rowPosition][colPosition] % 10);
        }
    } else {
        printf("%c | ", UN_CLICKED_SIGN);
    }
}

void printMineSweeperBoardView(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y;

    printHeaderOfBoard(rows - 2);
    for (i = 1; i < rows - 1; i++) {
        for (y = 0; y < cols - 1; y++) {
            if (y == 0) {
                printf(" %d | ", i - 1);
            } else {
                printCell(mineSweeperBoard, rows, cols, i, y);
            }
        }
        printf("\n");
    }
    printLineByCell(cols - 2);
}

void printLineByCell(int numberOfCells) {
    int i;
    for (i = 0; i < numberOfCells + 1; i++) {
        printf("____");
    }
    printf("\n");
}

void printHeaderOfBoard(int numberOfCells) {
    int i;

    printf("     ");
    for (i = 0; i < numberOfCells; i++) {
        printf("%d   ", i);
    }
    printf("\n");
    printLineByCell(numberOfCells);
}

void fillWithMines(int minePlaces[][2], int rows, int cols) {
    int i;
    for (i = 0; i < NUMBER_OF_MINES; i++) {
        minePlaces[i][0] = 1 + rand() % (NUMBER_OF_MINES);
        minePlaces[i][1] = 1 + rand() % (NUMBER_OF_MINES);
    }
}

int checkIfWonTheGame(int numberOfTurns, int rows, int cols, int numberOfMines) {
    int numberOfTotalTurns = (rows * cols) - numberOfMines;
    if (numberOfTurns == numberOfTotalTurns) {
        return 1;
    } else {
        return 0;
    }
}

int isInsideMineArray(int minePlaces[][2], int minePlacesRows, int minePlacesCols, int currentRow, int currentCol) {
    int i = 0, isInside = 0;

    while (i < minePlacesRows) {
        if (minePlaces[i][0] == currentRow && minePlaces[i][1] == currentCol) {
            isInside = 1;
        }
        i++;
    }
    return isInside;
}

int isCellRevealed(int val) {
    if (val / 10 >= 1)
        return 1;
    else {
        return 0;
    }
}

int isACellMine(int val) {
    if (val % 10 == 9 || val == 9) {
        return 1;
    } else {
        return 0;
    }
}

int handleClickOnBoard(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                       int minePlacesRows, int minePlacesCols) {
    int chosenRow, chosenCol;
    int i, y, isChosenAlready = 0;

    printf("Please enter your move, row and column :");
    scanf("%d %d", &chosenRow, &chosenCol);
    // add 1 to user selection because the board starts at 1 and not 0
    chosenRow += 1;
    chosenCol += 1;

    if (chosenRow >= 0 && chosenCol >= 0 && rows - 2 >= chosenRow && cols - 2 >= chosenCol) {
        for (i = 0; i < rows; i++) {
            for (y = 0; y < cols; y++) {
                if (chosenRow == i && chosenCol == y) {
                    if (isCellRevealed(mineSweeperBoardView[i][y]) == 1) {
                        isChosenAlready = 1;
                    } else {
                        mineSweeperBoardView[i][y] += 10;
                    }
                }
            }
        }
        if (isChosenAlready == 0) {
            printMineSweeperBoardView(mineSweeperBoardView, rows, cols);
        } else {
            printf("Already got chosen, please pick other\n");
        }
    } else {
        printf("Please enter a valid choice!\n");
    }

    return isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, chosenRow, chosenCol);
}

int calcNumberOfMinesAroundCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition,
                                int colPosition) {
    int counter = 0;
    if (isACellMine(mineSweeperBoard[rowPosition][colPosition]) == 1) {
        return 9;
    }
    if (isACellMine(mineSweeperBoard[rowPosition - 1][colPosition]) == 1) {
        counter++;
    }
    if (colPosition >= 1) {
        if (isACellMine(mineSweeperBoard[rowPosition - 1][colPosition - 1]) == 1) {
            counter++;
        }
    }
    if (isACellMine(mineSweeperBoard[rowPosition - 1][colPosition + 1]) == 1) {
        counter++;
    }

    if (isACellMine(mineSweeperBoard[rowPosition + 1][colPosition]) == 1) {
        counter++;
    }

    if (isACellMine(mineSweeperBoard[rowPosition + 1][colPosition - 1]) == 1) {
        counter++;
    }
    if (isACellMine(mineSweeperBoard[rowPosition + 1][colPosition + 1]) == 1) {
        counter++;
    }
    if (isACellMine(mineSweeperBoard[rowPosition][colPosition - 1]) == 1) {
        counter++;
    }
    if (isACellMine(mineSweeperBoard[rowPosition][colPosition + 1]) == 1) {
        counter++;
    }
    return counter;
}

