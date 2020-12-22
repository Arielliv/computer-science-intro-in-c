/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_NUMBER_OF_MINES 22
#define NUMBER_OF_COLS_OPTION_1 10
#define NUMBER_OF_ROWS_OPTION_1 10
#define NUMBER_OF_MINES_OPTION_1 8

#define NUMBER_OF_COLS_OPTION_2 14
#define NUMBER_OF_ROWS_OPTION_2 14
#define NUMBER_OF_MINES_OPTION_2 12

#define NUMBER_OF_COLS_OPTION_3 17
#define NUMBER_OF_ROWS_OPTION_3 17
#define NUMBER_OF_MINES_OPTION_3 15

#define NUMBER_OF_COLS 24
#define NUMBER_OF_ROWS 24
#define MINE_SIGN 'M'
#define UN_CLICKED_SIGN 'X'
#define FLAG_SIGN 'F'

// get user board choice - prints menu and get user selection ( for first part only 1 and 0 works )
int getUserBoardSizeChoice(int *rows, int *cols, double *numberOfMines);

// check if cell was already revealed, return (1 - true or 0 - false) value
int isCellRevealed(int val);

// check if cell is a mine, return (1 - true or 0 - false) value
int isACellMine(int val);

// initiate min sweeper board with mines and calculated cells
void initMineSweeperBoard(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                          double minePlacesRows, int minePlacesCols);

// prints mine sweeper board view
void printMineSweeperBoardView(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols);

// prints cell inside mine sweeper board view
void printCell(int currentCellValue);

// print header of the mine sweeper board with numbers of positions
void printHeaderOfBoard(int numberOfCells);

// print line of _ according to number of cells
void printLineByCell(int numberOfCells);

// return lowercase char
char toLowerCase(char c);

void openCell(int chosenRow, int chosenCol, int mineSweeperBoard[][NUMBER_OF_COLS],
              int rows, int cols, int minePlaces[][2],
              double minePlacesRows, int minePlacesCols);

// get user input for click
// invoke handleUserClick function with it
// return (1 - true or 0 - false) if selected mine -> then lose
// in case of input -1 (fake turn - return number of fake moves)
int handleUserCellSelection(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                            double minePlacesRows, int minePlacesCols);

// handles click updates in mineSweeperBoard after clicking specific cell
// return (1 - true or 0 - false) if selected mine -> then lose
int handleUserClick(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoardView[][NUMBER_OF_COLS],
                    int rows, int cols,
                    int minePlaces[][2],
                    double minePlacesRows, int minePlacesCols);

// fake user move
// get number of turn to do
// reveals every cells except mines
// return number of turns which have been done
int
userFakeInput(int numberOfMoves, int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
              double minePlacesRows, int minePlacesCols);

// fill array with number of random mines positions (according to passed number of mines)
void fillWithMines(int minePlaces[][2], double rows, int cols);

// calculates number of mines around the cell, if mine returns 9
int calcNumberOfMinesAroundCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition,
                                int colPosition);

// check if won the game - according to number of choices done
int checkIfWonTheGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols);

// check if cell in board suppose to be a mine
int isInsideMineArray(int minePlaces[][2], double minePlacesRows, int minePlacesCols, int currentRow, int currentCol);

// a code of mine sweeper game
int main() {
    int isWin = 0, isLose = 0;
    int boardSizeChoice = -1;
    int rows = 0, cols = 0;
    double numberOfMines = MAX_NUMBER_OF_MINES;

    int mineSweeperBoard[NUMBER_OF_ROWS][NUMBER_OF_COLS];

    int minePlaces[MAX_NUMBER_OF_MINES][2];

    // Use current time as seed for random generator
    srand(time(NULL));

    // in first stage only expect to get 1 or 0
    while (boardSizeChoice < 0 || boardSizeChoice > 4) {
        boardSizeChoice = getUserBoardSizeChoice(&rows, &cols, &numberOfMines);
    }

    if ((boardSizeChoice >= 0 && boardSizeChoice < 5)) {
        if (boardSizeChoice == 0) {
            printf("Bye");
        } else {
            fillWithMines(minePlaces, numberOfMines, 2);
            initMineSweeperBoard(mineSweeperBoard, rows, cols, minePlaces, numberOfMines, 2);

            printMineSweeperBoardView(mineSweeperBoard, rows, cols);

            while (isWin == 0 && isLose != 1) {
                isLose = handleUserCellSelection(mineSweeperBoard, rows, cols,
                                                 minePlaces,
                                                 numberOfMines,
                                                 2);
                isWin = checkIfWonTheGame(mineSweeperBoard, rows, cols);
            }

            if (isLose == 1) {
                printf("You've hit a bomb! Game over!");
            } else if (isWin == 1) {
                printf("You wom!! congratulations! CHAMPION!");
            }
        }
    }
}

int getUserBoardSizeChoice(int *rows, int *cols, double *numberOfMines) {
    int boardSizeChoice;
    int rowsUserInput = 0, colsUserInput = 0;
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
    if (boardSizeChoice == 1) {
        *rows = NUMBER_OF_ROWS_OPTION_1;
        *cols = NUMBER_OF_COLS_OPTION_1;
        *numberOfMines = NUMBER_OF_MINES_OPTION_1;
    }
    if (boardSizeChoice == 2) {
        *rows = NUMBER_OF_ROWS_OPTION_2;
        *cols = NUMBER_OF_COLS_OPTION_2;
        *numberOfMines = NUMBER_OF_MINES_OPTION_2;
    }
    if (boardSizeChoice == 3) {
        *rows = NUMBER_OF_ROWS_OPTION_3;
        *cols = NUMBER_OF_COLS_OPTION_3;
        *numberOfMines = NUMBER_OF_MINES_OPTION_3;
    }
    if (boardSizeChoice == 4) {
        printf("Please enter the size of the board (Lines <= 22 and Cols <= 22  ):\n");
        scanf("%d %d", &rowsUserInput, &colsUserInput);
        if (rowsUserInput > 0 && rowsUserInput < 23 && colsUserInput > 0 && colsUserInput < 23) {
            *rows = rowsUserInput + 2;
            *cols = colsUserInput + 2;
            *numberOfMines = sqrt(colsUserInput * rowsUserInput);
        }
    }
    return boardSizeChoice;
}

void initMineSweeperBoard(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols,
                          int minePlaces[][2],
                          double minePlacesRows, int minePlacesCols) {
    int i, y;
    for (i = 0; i < minePlacesRows; i++) {
        mineSweeperBoardView[minePlaces[i][0]][minePlaces[i][1]] = 9;
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

void printCell(int currentCellValue) {
    if (isCellRevealed(currentCellValue) == 1) {
        // if no mines around cell - print blank else print cell score
        if (currentCellValue % 10 == 9) {
            printf("%c | ", MINE_SIGN);
        } else if (currentCellValue % 10 == 0) {
            printf("  | ");
        } else {
            printf("%d | ", currentCellValue % 10);
        }
    } else {
        if (currentCellValue < 0) {
            printf("%c | ", FLAG_SIGN);
        } else {
            printf("%c | ", UN_CLICKED_SIGN);
        }

    }
}

void printMineSweeperBoardView(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y;

    printHeaderOfBoard(cols - 2);
    for (i = 1; i < rows - 1; i++) {
        for (y = 0; y < cols - 1; y++) {
            if (y == 0) {
                printf(" %2d | ", i - 1);
            } else {
                printCell(mineSweeperBoard[i][y]);
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
        printf("%2d  ", i);
    }
    printf("\n");
    printLineByCell(numberOfCells);
}

void fillWithMines(int minePlaces[][2], double rows, int cols) {
    int i;
    for (i = 0; i < rows; i++) {
        minePlaces[i][0] = 1 + rand() % ((int) rows);
        minePlaces[i][1] = 1 + rand() % ((int) rows);
    }
}

int checkIfWonTheGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y, isWon = 1;
    for (i = 1; i < rows - 1; i++) {
        for (y = 1; y < cols - 1; ++y) {
            if (mineSweeperBoard[i][y] == 19 || mineSweeperBoard[i][y] == 9) {
                isWon = 0;
            }
        }
    }
    return isWon;
}

int isInsideMineArray(int minePlaces[][2], double minePlacesRows, int minePlacesCols, int currentRow, int currentCol) {
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
    if (val >= 0 && (val % 10 == 9 || val == 9)) {
        return 1;
    } else {
        return 0;
    }
}

char toLowerCase(char c) {
    return c |= ' ';
};

int handleUserCellSelection(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
                            double minePlacesRows, int minePlacesCols) {
    int chosenRow, chosenCol;
    char chosenInteraction;

    printf("Please enter your move, row and column :");
    scanf("%d %d %c", &chosenRow, &chosenCol, &chosenInteraction);
    chosenInteraction = toLowerCase(chosenInteraction);

    if (chosenRow == -1) {
        return userFakeInput(chosenCol, mineSweeperBoardView, rows, cols, minePlaces, minePlacesRows,
                             minePlacesCols);
    } else {
        // add 1 to user selection because the board starts at 1 and not 0
        chosenRow += 1;
        chosenCol += 1;

        return handleUserClick(chosenRow, chosenCol, chosenInteraction, mineSweeperBoardView, rows, cols, minePlaces,
                               minePlacesRows,
                               minePlacesCols);
    }
}

void openCell(int chosenRow, int chosenCol, int mineSweeperBoard[][NUMBER_OF_COLS],
              int rows, int cols, int minePlaces[][2],
              double minePlacesRows, int minePlacesCols) {

    int isRevealed = isCellRevealed(mineSweeperBoard[chosenRow][chosenCol]);
    if (chosenRow > 0 && chosenCol > 0 && rows - 2 >= chosenRow && cols - 2 >= chosenCol &&
        isRevealed == 0) {
        int isEmpty = mineSweeperBoard[chosenRow][chosenCol] % 10 == 0 ? 1 : 0;
        if (mineSweeperBoard[chosenRow][chosenCol] >= 0) {
            mineSweeperBoard[chosenRow][chosenCol] += 10;
        }
        if (isEmpty == 1 && mineSweeperBoard[chosenRow][chosenCol] >= 0 &&
            mineSweeperBoard[chosenRow][chosenCol] < 20) {

            openCell(chosenRow, chosenCol - 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow, chosenCol + 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow - 1, chosenCol, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow - 1, chosenCol - 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow - 1, chosenCol + 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow + 1, chosenCol, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow + 1, chosenCol + 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
            openCell(chosenRow + 1, chosenCol - 1, mineSweeperBoard, rows, cols, minePlaces, minePlacesRows,
                     minePlacesCols);
        }

    } else {
        return;
    }
}

int handleUserClick(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoardView[][NUMBER_OF_COLS],
                    int rows, int cols,
                    int minePlaces[][2],
                    double minePlacesRows, int minePlacesCols) {
    int i, y, isChosenAlready = 0;

    if (chosenRow >= 0 && chosenCol >= 0 && rows - 2 >= chosenRow && cols - 2 >= chosenCol) {
        for (i = 0; i < rows; i++) {
            for (y = 0; y < cols; y++) {
                if (chosenRow == i && chosenCol == y) {
                    if (isCellRevealed(mineSweeperBoardView[i][y]) == 1) {
                        isChosenAlready = 1;
                    } else {
                        if (chosenInteraction == 'o') {
                            if (mineSweeperBoardView[i][y] < 0) {
                                mineSweeperBoardView[i][y] += 10;
                            }
                            openCell(chosenRow, chosenCol, mineSweeperBoardView, rows, cols, minePlaces, minePlacesRows,
                                     minePlacesCols);
                        } else if (chosenInteraction == 'f') {
                            if (mineSweeperBoardView[i][y] >= 0) {
                                mineSweeperBoardView[i][y] -= 10;
                            }
                            if (mineSweeperBoardView[i][y] >= 10) {
                                mineSweeperBoardView[i][y] -= 20;
                            }
                        }

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
    return chosenInteraction != 'f' ? isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, chosenRow,
                                                        chosenCol) : 0;
}

int
userFakeInput(int numberOfMoves, int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2],
              double minePlacesRows, int minePlacesCols) {
    int i, y, counter = numberOfMoves;

    for (i = 1; i < rows - 1 && numberOfMoves > 0; i++) {
        for (y = 1; y < cols - 1 && numberOfMoves > 0; y++) {
            if (isCellRevealed(mineSweeperBoardView[i][y]) == 0 &&
                isInsideMineArray(minePlaces, minePlacesRows, minePlacesCols, i, y) == 0) {
                mineSweeperBoardView[i][y] += 10;
                counter--;
            }
        }
    }

    printMineSweeperBoardView(mineSweeperBoardView, rows, cols);
    return numberOfMoves;
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

