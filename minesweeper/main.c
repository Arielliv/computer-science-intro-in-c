/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_MINES 8
#define NUMBER_OF_COLS 10
#define NUMBER_OF_ROWS 10
#define MINE_SIGN 'M'
#define UN_CLICKED_SIGN 'X'

// get user board choice - prints menu and get user selection ( for first part only 1 works )
int getUserBoardSizeChoice();

// initiate min sweeper board with boolean value (is clicked = false)
void initMineSweeperBoard(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int boardStatusRows, int boardStatusCols);

// initiate min sweeper board view all the related signs ( 'M', 'X' , blank space and numbers)
void initMineSweeperBoardView(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols, int minePlaces[][2],
                              int minePlacesRows, int minePlacesCols);

// update specific cell and prints mine sweeper board view after
void printMineSweeperBoardView(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
                           bool mineSweeperBoardStatus[][NUMBER_OF_COLS],
                           int scoreRows, int scoreCols);

// print header of the mine sweeper board with numbers of positions
void printHeaderOfBoard(int numberOfCells);

// print line of _ according to number of cells
void printLineByCell(int numberOfCells);

// handles click updates in mineSweeperBoardStatus and mineSweeperBoardView after clicking specific cell
// get user input for click
// return boolean if selected mine -> then lost
bool handleClickOnBoard(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int scoreRows, int scoreCols,
                        char mineSweeperBoardView[][NUMBER_OF_COLS], int viewRows, int viewCols, int minePlaces[][2],
                        int minePlacesRows, int minePlacesCols);

// fill array with number of random mines positions (according to passed number of mines)
void fillWithMines(int minePlaces[][2], int rows, int cols);

// calculates number of mines around the cell, if mine returns -1
int calcNumberOfMinesAroundCell(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols, int rowPosition,
                                 int colPosition);

// check if won the game - if all non mines cell got reviled
bool checkIfWonTheGame(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int boardStatusRows, int boardStatusCols);

// check if cell in board is a mine
bool isInsideMineArray(int minePlaces[][2], int minePlacesRows, int minePlacesCols, int currentRow, int currentCol);

int main() {
    bool isWin = false;
    bool isLose = false;
    int boardSizeChoice;

    // will be filled by user choice next version
    int rows = NUMBER_OF_ROWS, cols = NUMBER_OF_COLS;
    char mineSweeperBoard[rows][cols];
    bool mineSweeperBoardStatus[rows][cols];
    int minePlaces[NUMBER_OF_MINES][2];

    boardSizeChoice = getUserBoardSizeChoice();

    if ((boardSizeChoice >= 0 && boardSizeChoice < 5)) {
        if (boardSizeChoice == 0) {
            printf("Bye");
        } else {
            fillWithMines(minePlaces, NUMBER_OF_MINES, 2);
            initMineSweeperBoardView(mineSweeperBoard, rows, cols, minePlaces, NUMBER_OF_MINES, 2);
            initMineSweeperBoard(mineSweeperBoardStatus, rows, cols);
            printMineSweeperBoardView(mineSweeperBoard, rows, cols, mineSweeperBoardStatus, rows, cols);

            while (isWin == false && isLose == false) {
                isLose = handleClickOnBoard(mineSweeperBoardStatus, rows, cols, mineSweeperBoard, rows, cols,
                                            minePlaces,
                                            NUMBER_OF_MINES,
                                            2);
                isWin = checkIfWonTheGame(mineSweeperBoardStatus, rows, cols);
            }

            if (isLose) {
                printf("you lost");
            }
            if (isWin) {
                printf("you won");
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

void initMineSweeperBoard(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int boardStatusRows, int boardStatusCols) {
    int i, y;
    for (i = 0; i < boardStatusRows; i++) {
        for (y = 0; y < boardStatusCols; y++) {
            mineSweeperBoardStatus[i][y] = false;
        }
    }
}

void initMineSweeperBoardView(char mineSweeperBoardView[][NUMBER_OF_COLS], int viewRows, int viewCols,
                              int minePlaces[][2],
                              int minePlacesRows, int minePlacesCols) {
    int i, y;
    for (i = 0; i < viewRows; i++) {
        for (y = 0; y < viewCols; y++) {
            if (isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, i, y)) {
                mineSweeperBoardView[i][y] = MINE_SIGN;
            } else {
                mineSweeperBoardView[i][y] = UN_CLICKED_SIGN;
            }
        }
    }
    for (i = 0; i < viewRows; i++) {
        for (y = 0; y < viewCols; y++) {

            // get cell score -  how many mines around it
            int cellScore = calcNumberOfMinesAroundCell(mineSweeperBoardView, viewRows, viewCols, i, y);
            if (cellScore != -1) {
                // cast int to char with + 0
                mineSweeperBoardView[i][y] = cellScore + '0';
            }
        }
    }
}

void printCell(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
               bool mineSweeperBoardStatus[][NUMBER_OF_COLS],
               int scoreRows, int scoreCols, int rowPosition, int colPosition) {
    if (mineSweeperBoardStatus[rowPosition][colPosition] == true) {
        // if no mines around cell - print blank else print cell score
        if (mineSweeperBoard[rowPosition][colPosition] == '0') {
            printf("  | ");
        } else {
            printf("%c | ", mineSweeperBoard[rowPosition][colPosition]);
        }
    } else {
//        printf("%d | ", calcNumberOfMinesAroundCell(mineSweeperBoard, viewRows, viewCols, rowPosition, colPosition));
        printf("%c | ", UN_CLICKED_SIGN);
    }
}

void printMineSweeperBoardView(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
                           bool mineSweeperBoardStatus[][NUMBER_OF_COLS],
                           int scoreRows, int scoreCols) {
    int i, y;
    printHeaderOfBoard(viewRows - 2);
    for (i = 1; i < viewRows - 1; i++) {
        for (y = 0; y < viewCols - 1; y++) {
            if (y == 0) {
                printf(" %d | ", i - 1);
            } else {
                printCell(mineSweeperBoard, viewRows, viewCols, mineSweeperBoardStatus, scoreRows, scoreCols, i, y);
            }
        }
        printf("\n");
    }
    printLineByCell(viewCols - 2);
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

bool checkIfWonTheGame(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int boardStatusRows, int boardStatusCols) {
    bool isWon = true;
    int i, y;
    for (i = 1; i < boardStatusRows - 1; i++) {
        for (y = 1; y < boardStatusCols - 1; ++y) {
            if (mineSweeperBoardStatus[i][y] == false) {
                isWon = false;
            }
        }
    }
    return isWon;
}

bool isInsideMineArray(int minePlaces[][2], int minePlacesRows, int minePlacesCols, int currentRow, int currentCol) {
    int i = 0;
    bool isInside = false;

    while (i < minePlacesRows) {
        if (minePlaces[i][0] == currentRow && minePlaces[i][1] == currentCol) {
            isInside = true;
        }
        i++;
    }
    return isInside;
}

bool handleClickOnBoard(bool mineSweeperBoardStatus[][NUMBER_OF_COLS], int scoreRows, int scoreCols,
                        char mineSweeperBoardView[][NUMBER_OF_COLS], int viewRows, int viewCols, int minePlaces[][2],
                        int minePlacesRows, int minePlacesCols) {
    int chosenRow, chosenCol;
    int i, y;

    printf("Please enter your move, row and column :");
    scanf("%d %d", &chosenRow, &chosenCol);
    // add 1 to user selection because the board starts at 1 and not 0
    chosenRow += 1;
    chosenCol += 1;

    if (chosenRow >= 0 && chosenCol >= 0) {
        for (i = 0; i < scoreRows; i++) {
            for (y = 0; y < scoreCols; y++) {
                if (chosenRow == i && chosenCol == y) {
                    mineSweeperBoardStatus[i][y] = true;
                }
            }
        }
        printMineSweeperBoardView(mineSweeperBoardView, viewRows, viewCols, mineSweeperBoardStatus, scoreRows, scoreCols);
    } else {
        printf("Please enter a valid choice!");
    }

    return isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, chosenRow, chosenCol);
}

int calcNumberOfMinesAroundCell(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols, int rowPosition,
                                 int colPosition) {
    int counter = 0;
    if (mineSweeperBoard[rowPosition][colPosition] == MINE_SIGN) {
        return -1;
    }
    if (mineSweeperBoard[rowPosition - 1][colPosition] == MINE_SIGN) {
        counter++;
    }
    if (colPosition >= 1) {
        if (mineSweeperBoard[rowPosition - 1][colPosition - 1] == MINE_SIGN) {
            counter++;
        }
    }
    if (mineSweeperBoard[rowPosition - 1][colPosition + 1] == MINE_SIGN) {
        counter++;
    }

    if (mineSweeperBoard[rowPosition + 1][colPosition] == MINE_SIGN) {
        counter++;
    }

    if (mineSweeperBoard[rowPosition + 1][colPosition - 1] == MINE_SIGN) {
        counter++;
    }
    if (mineSweeperBoard[rowPosition + 1][colPosition + 1] == MINE_SIGN) {
        counter++;
    }
    if (mineSweeperBoard[rowPosition][colPosition - 1] == MINE_SIGN) {
        counter++;
    }
    if (mineSweeperBoard[rowPosition][colPosition + 1] == MINE_SIGN) {
        counter++;
    }
    return counter;
}

