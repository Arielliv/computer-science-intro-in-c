/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_MINES 8
#define NUMBER_OF_COLS 10
#define NUMBER_OF_ROWS 10

void initMineSweeperBoard(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int rows, int cols);

void initMineSweeperBoardView(char mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                              int minePlacesRows, int minePlacesCols);

void
printMineSweeperBoard(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
                      bool mineSweeperBoardScore[][NUMBER_OF_COLS],
                      int scoreRows, int scoreCols);

void printHeaderOfBoard(int numberOfCells);

void printLineByCell(int numberOfCells);

bool handleClickOnBoard(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int scoreRows, int scoreCols,
                        char mineSweeperBoardView[][NUMBER_OF_COLS], int viewRows, int viewCols, int minePlaces[][2],
                        int minePlacesRows, int minePlacesCols);

void fillWithMines(int minePlaces[][2], int rows, int cols);

int checkNumberOfMinesAround(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols, int rowPosition,
                             int colPosition);

bool checkIfWonTheGame(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int rows, int cols);

bool isInsideMineArray(int minePlaces[][2], int minePlacesRows, int minePlacesCols, int currentRow, int currentCol);

int main() {
    bool isWin = false;
    bool isLose = false;
    int boardSizeChoice = 0;
    // will be filled by user choice next version
    int rows = NUMBER_OF_ROWS, cols = NUMBER_OF_COLS;
    char mineSweeperBoard[rows][cols];
    bool mineSweeperBoardScore[rows][cols];
    int minePlaces[NUMBER_OF_MINES][2];

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

    if ((boardSizeChoice >= 0 && boardSizeChoice < 5)) {
        if (boardSizeChoice == 0) {
            printf("Bye");
        } else {
            fillWithMines(minePlaces, NUMBER_OF_MINES, 2);
            initMineSweeperBoardView(mineSweeperBoard, rows, cols, minePlaces, NUMBER_OF_MINES, 2);
            initMineSweeperBoard(mineSweeperBoardScore, rows, cols);
            printMineSweeperBoard(mineSweeperBoard, rows, cols, mineSweeperBoardScore, rows, cols);

            while (isWin == false && isLose == false) {
                isLose = handleClickOnBoard(mineSweeperBoardScore, rows, cols, mineSweeperBoard, rows, cols, minePlaces,
                                            NUMBER_OF_MINES,
                                            2);
                isWin = checkIfWonTheGame(mineSweeperBoardScore, rows, cols);
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

void initMineSweeperBoard(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y;
    for (i = 0; i < rows; i++) {
        for (y = 0; y < cols; y++) {
            mineSweeperBoardScore[i][y] = false;
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
                mineSweeperBoardView[i][y] = 'M';
            } else {
                mineSweeperBoardView[i][y] = 'X';
            }
        }
    }
    for (i = 0; i < viewRows; i++) {
        for (y = 0; y < viewCols; y++) {
            int score = checkNumberOfMinesAround(mineSweeperBoardView, viewRows, viewCols, i, y);
            if (score != -1) {
                mineSweeperBoardView[i][y] = score + '0';
            }
        }
    }
}

void printCell(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
               bool mineSweeperBoardScore[][NUMBER_OF_COLS],
               int scoreRows, int scoreCols, int rowPosition, int colPosition) {
    if (mineSweeperBoardScore[rowPosition][colPosition] == true) {
        if (mineSweeperBoard[rowPosition][colPosition] == '0') {
            printf("  | ");
        } else {
            printf("%c | ", mineSweeperBoard[rowPosition][colPosition]);
        }
    } else {
//        printf("%d | ", checkNumberOfMinesAround(mineSweeperBoard, viewRows, viewCols, rowPosition, colPosition));
        printf("%c | ", 'X');
    }
}

void
printMineSweeperBoard(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols,
                      bool mineSweeperBoardScore[][NUMBER_OF_COLS],
                      int scoreRows, int scoreCols) {
    int i, y;
    printHeaderOfBoard(viewRows - 2);
    for (i = 1; i < viewRows - 1; i++) {
        for (y = 0; y < viewCols - 1; y++) {
            if (y == 0) {
                printf(" %d | ", i - 1);
            } else {
                printCell(mineSweeperBoard, viewRows, viewCols, mineSweeperBoardScore, scoreRows, scoreCols, i, y);
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

bool checkIfWonTheGame(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int rows, int cols) {
    bool isWon = true;
    for (int i = 1; i < rows - 1; i++) {
        for (int y = 1; y < cols - 1; ++y) {
            if (mineSweeperBoardScore[i][y] == false) {
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

bool handleClickOnBoard(bool mineSweeperBoardScore[][NUMBER_OF_COLS], int scoreRows, int scoreCols,
                        char mineSweeperBoardView[][NUMBER_OF_COLS], int viewRows, int viewCols, int minePlaces[][2],
                        int minePlacesRows, int minePlacesCols) {
    int chosenRow, chosenCol;
    int i, y;
    printf("Please enter your move, row and column :");
    scanf("%d%d", &chosenRow, &chosenCol);
    chosenRow += 1;
    chosenCol += 1;
    if (chosenRow >= 0 && chosenCol >= 0) {
        for (i = 0; i < scoreRows; i++) {
            for (y = 0; y < scoreCols; y++) {
                if (chosenRow == i && chosenCol == y) {
                    mineSweeperBoardScore[i][y] = true;
                }
            }
        }
        printMineSweeperBoard(mineSweeperBoardView, viewRows, viewCols, mineSweeperBoardScore, scoreRows, scoreCols);
    } else {
        printf("Please enter a valid choice!");
    }

    return isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, chosenRow, chosenCol);
}

int checkNumberOfMinesAround(char mineSweeperBoard[][NUMBER_OF_COLS], int viewRows, int viewCols, int rowPosition,
                             int colPosition) {
    int counter = 0;
    if (mineSweeperBoard[rowPosition][colPosition] == 'M') {
        return -1;
    }
    if (mineSweeperBoard[rowPosition - 1][colPosition] == 'M') {
        counter++;
    }
    if (colPosition >= 1) {
        if (mineSweeperBoard[rowPosition - 1][colPosition - 1] == 'M') {
            counter++;
        }
    }
    if (mineSweeperBoard[rowPosition - 1][colPosition + 1] == 'M') {
        counter++;
    }

    if (mineSweeperBoard[rowPosition + 1][colPosition] == 'M') {
        counter++;
    }

    if (mineSweeperBoard[rowPosition + 1][colPosition - 1] == 'M') {
        counter++;
    }
    if (mineSweeperBoard[rowPosition + 1][colPosition + 1] == 'M') {
        counter++;
    }
    if (mineSweeperBoard[rowPosition][colPosition - 1] == 'M') {
        counter++;
    }
    if (mineSweeperBoard[rowPosition][colPosition + 1] == 'M') {
        counter++;
    }
    return counter;
}

