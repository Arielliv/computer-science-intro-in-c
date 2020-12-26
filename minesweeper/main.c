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
#define MINE_SIGN '*'
#define UN_CLICKED_SIGN 'X'
#define FLAG_SIGN 'F'
#define OPEN_INTERACTION 'o'
#define FLAG_INTERACTION 'f'

// search for value in array[][] return (1 - true or 0 - false) if exits
int linearSearch(int array[][2], int rows, int cols, int numX, int numY);

// start the game, print when lose and win
void startGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2], double mineArrayRows,
               int mineArrayCols);

// get user board choice - prints menu and get user selection ( for first part only 1 and 0 works )
int getUserBoardSizeChoice(int *rows, int *cols, double *numberOfMines);

// check if cell was already revealed, return (1 - true or 0 - false) value
int isCellRevealed(int val);

// check if cell is a mine, return (1 - true or 0 - false) value
int isACellMine(int val);

// check if cell is a empty, return (1 - true or 0 - false) value
int isCellEmpty(int val);

// check if cell is a flag, return (1 - true or 0 - false) value
int isCellAFlag(int val);

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

// open all cells (uses after hit a mine)
void openAllCells(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols);

// handles opening a cell ( and all need to be open with it recursively)
void openCell(int chosenRow, int chosenCol, int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols);

// get user input for click
// invoke handleUserClick function with it
// return (1 - true or 0 - false) if selected mine -> then lose
// in case of input -1 (fake turn - return 0)
int handleUserCellSelection(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols);

int handleInteraction(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoard[][NUMBER_OF_COLS],
                      int rows, int cols);

// handles click updates in mineSweeperBoard after clicking specific cell
// return (1 - true or 0 - false) if selected mine -> then lose
int handleUserClick(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoard[][NUMBER_OF_COLS],
                    int rows, int cols);

// fake user move
// get number of turn to do
// reveals every cells except mines
void userFakeInput(int numberOfMoves, int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols);

// fill array with number of random mines positions (according to passed number of mines)
void fillWithMines(int minePlaces[][2], double rows, int cols);

// calculates number of mines around the cell, if mine returns 9
int calcNumberOfMinesAroundCell(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int rowPosition,
                                int colPosition);

// check if won the game - according to number of choices done
int checkIfWonTheGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int numberOfMines);

// a code of mine sweeper game
int main() {
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
        if (boardSizeChoice != 0) {
            startGame(mineSweeperBoard, rows, cols, minePlaces, numberOfMines, 2);

        }
        printf("Hope you have enjoyed playing !!!!!");
    }
}

void startGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int minePlaces[][2], double mineArrayRows,
               int mineArrayCols) {
    int isWon = 0, isLose = 0;
    fillWithMines(minePlaces, mineArrayRows, mineArrayCols);
    initMineSweeperBoard(mineSweeperBoard, rows, cols, minePlaces, mineArrayRows, mineArrayCols);
    printMineSweeperBoardView(mineSweeperBoard, rows, cols);

    while (isWon == 0 && isLose != 1) {
        isLose = handleUserCellSelection(mineSweeperBoard, rows, cols);
        isWon = checkIfWonTheGame(mineSweeperBoard, rows, cols, (int) mineArrayRows);
    }

    if (isLose == 1) {
        printf("You've hit a bomb! Game over!\n");
        openAllCells(mineSweeperBoard, rows, cols);
    } else if (isWon == 1) {
        printf("You wom!! congratulations! CHAMPION!\n");
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
    switch (boardSizeChoice) {
        case 1:
            *rows = NUMBER_OF_ROWS_OPTION_1;
            *cols = NUMBER_OF_COLS_OPTION_1;
            *numberOfMines = NUMBER_OF_MINES_OPTION_1;
            break;
        case 2:
            *rows = NUMBER_OF_ROWS_OPTION_2;
            *cols = NUMBER_OF_COLS_OPTION_2;
            *numberOfMines = NUMBER_OF_MINES_OPTION_2;
            break;
        case 3:
            *rows = NUMBER_OF_ROWS_OPTION_3;
            *cols = NUMBER_OF_COLS_OPTION_3;
            *numberOfMines = NUMBER_OF_MINES_OPTION_3;
            break;
        case 4:
            printf("Please enter the size of the board (Lines <= 22 and Cols <= 22  ):\n");
            scanf("%d %d", &rowsUserInput, &colsUserInput);
            if (rowsUserInput > 0 && rowsUserInput < 23 && colsUserInput > 0 && colsUserInput < 23) {
                *rows = rowsUserInput + 2;
                *cols = colsUserInput + 2;
                *numberOfMines = sqrt(colsUserInput * rowsUserInput);
            }
            break;
        default:
            break;
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
            // 9 represents mine
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
    int i, isMineAlreadyInside = 1;
    int randomX, randomY;
    for (i = 0; i < rows; i++) {
        while (isMineAlreadyInside == 1) {
            randomX = 1 + rand() % ((int) rows - 1);
            randomY = 1 + rand() % ((int) rows - 1);
            //check if already cell was already assign to mine
            isMineAlreadyInside = linearSearch(minePlaces, (int) rows, cols, randomX, randomY);
        }
        minePlaces[i][0] = randomX;
        minePlaces[i][1] = randomY;

        // reset the for next iteration
        isMineAlreadyInside = 1;
    }
}

int checkIfWonTheGame(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols, int numberOfMines) {
    int i, y, counter = 0;
    int isCellWasRevealed, isCellAMine;
    for (i = 1; i < rows - 1; i++) {
        for (y = 1; y < cols - 1; ++y) {

            isCellWasRevealed = isCellRevealed(mineSweeperBoard[i][y]);
            isCellAMine = isACellMine(mineSweeperBoard[i][y]);

            if (isCellWasRevealed == 1 && isCellAMine == 0) {
                counter++;
            }
        }
    }
    // count number of open cells without mines
    if (counter == ((rows - 2) * (cols - 2)) - numberOfMines) {
        return 1;
    } else {
        return 0;
    }
}

int handleUserCellSelection(int mineSweeperBoard[][NUMBER_OF_COLS], int rows, int cols) {
    int chosenRow, chosenCol;
    char chosenInteraction;

    printf("Please enter your move, row and column :");
    scanf("%d %d", &chosenRow, &chosenCol);

    if (chosenRow == -1) {
        userFakeInput(chosenCol, mineSweeperBoard, rows, cols);
        return 0;
    } else {
        scanf(" %c", &chosenInteraction);
        // In  case character is upper case
        chosenInteraction = toLowerCase(chosenInteraction);
        // add 1 to user selection because the board starts at 1 and not 0
        chosenRow += 1;
        chosenCol += 1;

        return handleUserClick(chosenRow, chosenCol, chosenInteraction, mineSweeperBoard, rows, cols);
    }
}

void openCell(int chosenRow, int chosenCol, int mineSweeperBoard[][NUMBER_OF_COLS],
              int rows, int cols) {
    int isRevealed, isEmpty, isCellIsAFlag;
    // check if cell already open
    isRevealed = isCellRevealed(mineSweeperBoard[chosenRow][chosenCol]);

    // if cell is not revealed and in boundaries
    if (chosenRow > 0 && chosenCol > 0 && rows - 2 >= chosenRow && cols - 2 >= chosenCol &&
        isRevealed == 0) {

        isCellIsAFlag = isCellAFlag(mineSweeperBoard[chosenRow][chosenCol]);
        if (isCellIsAFlag == 0) {
            mineSweeperBoard[chosenRow][chosenCol] += 10;
        }
        // check if cell is empty
        isEmpty = isCellEmpty(mineSweeperBoard[chosenRow][chosenCol]);

        //if cell empty and not a flag
        if (isEmpty == 1 && isCellIsAFlag == 0) {

            openCell(chosenRow, chosenCol - 1, mineSweeperBoard, rows, cols);
            openCell(chosenRow, chosenCol + 1, mineSweeperBoard, rows, cols);
            openCell(chosenRow - 1, chosenCol, mineSweeperBoard, rows, cols);
            openCell(chosenRow - 1, chosenCol - 1, mineSweeperBoard, rows, cols);
            openCell(chosenRow - 1, chosenCol + 1, mineSweeperBoard, rows, cols);
            openCell(chosenRow + 1, chosenCol, mineSweeperBoard, rows, cols);
            openCell(chosenRow + 1, chosenCol + 1, mineSweeperBoard, rows, cols);
            openCell(chosenRow + 1, chosenCol - 1, mineSweeperBoard, rows, cols);
        }

    } else {
        return;
    }
}

int handleUserClick(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoard[][NUMBER_OF_COLS],
                    int rows, int cols) {
    int i, y;
    int isRevealed, isCellAMine;

    if (chosenRow >= 0 && chosenCol >= 0 && rows - 2 >= chosenRow && cols - 2 >= chosenCol) {
        for (i = 0; i < rows; i++) {
            for (y = 0; y < cols; y++) {
                if (chosenRow == i && chosenCol == y) {
                    // return if cell was already revealed
                    isRevealed = handleInteraction(chosenRow, chosenCol, chosenInteraction, mineSweeperBoard, rows,
                                                   cols);
                }
            }
        }
        if (isRevealed == 0) {
            printMineSweeperBoardView(mineSweeperBoard, rows, cols);
        } else {
            printf("Already got chosen, please pick other\n");
        }
    } else {
        printf("Please enter a valid choice!\n");
    }

    // checks if interaction wasn't FLAG_INTERACTION and checks if cell was mine
    if (chosenInteraction != FLAG_INTERACTION) {

        isCellAMine = isACellMine(mineSweeperBoard[chosenRow][chosenCol]);
        return isCellAMine;
    } else {
        return 0;
    }
}

int handleInteraction(int chosenRow, int chosenCol, char chosenInteraction, int mineSweeperBoard[][NUMBER_OF_COLS],
                      int rows, int cols) {
    int isCellIsAFlag, isRevealed;
    // check if cell was already revealed
    isRevealed = isCellRevealed(mineSweeperBoard[chosenRow][chosenCol]);
    if (isRevealed == 0) {
        isCellIsAFlag = isCellAFlag(mineSweeperBoard[chosenRow][chosenCol]);
        if (chosenInteraction == OPEN_INTERACTION) {
            if (isCellIsAFlag == 1) {
                // update cell with +10 when open a flag
                mineSweeperBoard[chosenRow][chosenCol] += 10;
            }
            openCell(chosenRow, chosenCol, mineSweeperBoard, rows, cols);
        } else if (chosenInteraction == FLAG_INTERACTION) {
            if (isCellIsAFlag == 0) {
                // update cell with -10 when is flag
                mineSweeperBoard[chosenRow][chosenCol] -= 10;
            }
        }
    }
    return isRevealed;
}

void userFakeInput(int numberOfMoves, int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y, counterMoves = numberOfMoves;
    int isCellWasRevealed, isCellAMine, isCellIsAFlag;

    for (i = 1; i < rows - 1 && counterMoves > 0; i++) {
        for (y = 1; y < cols - 1 && counterMoves > 0; y++) {

            isCellIsAFlag = isCellAFlag(mineSweeperBoardView[i][y]);
            isCellWasRevealed = isCellRevealed(mineSweeperBoardView[i][y]);
            isCellAMine = isACellMine(mineSweeperBoardView[i][y]);
            if (isCellWasRevealed == 0 && isCellAMine == 0 && isCellIsAFlag == 0) {
                // open cell with +10
                mineSweeperBoardView[i][y] += 10;
                counterMoves--;
            }
        }
    }

    printMineSweeperBoardView(mineSweeperBoardView, rows, cols);
}

void openAllCells(int mineSweeperBoardView[][NUMBER_OF_COLS], int rows, int cols) {
    int i, y;
    int isCellWasRevealed, isCellIsAFlag;

    for (i = 1; i < rows - 1; i++) {
        for (y = 1; y < cols - 1; y++) {

            isCellIsAFlag = isCellAFlag(mineSweeperBoardView[i][y]);
            if (isCellIsAFlag == 0) {
                // remove flag
                mineSweeperBoardView[i][y] += 10;
            }

            isCellWasRevealed = isCellRevealed(mineSweeperBoardView[i][y]);
            if (isCellWasRevealed == 0) {
                // open cell with +10
                mineSweeperBoardView[i][y] += 10;
            }
        }
    }

    printMineSweeperBoardView(mineSweeperBoardView, rows, cols);
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

int linearSearch(int array[][2], int rows, int cols, int numX, int numY) {
    int reply;
    //base case
    if (rows == 1) {
        if (array[0][0] == numX && array[0][1] == numY) {
            reply = 1;
        } else {
            reply = 0;
        }
    } else {
        reply = linearSearch(array, rows - 1, cols, numX, numY);
        if (reply == 0 && array[rows - 1][0] == numX && array[rows - 1][1] == numY) {
            reply = 1;
        }
    }
    return reply;
}

int isCellAFlag(int val) {
    if (val < 0)
        return 1;
    else {
        return 0;
    }
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

int isCellEmpty(int val) {
    if (val % 10 == 0)
        return 1;
    else {
        return 0;
    }
}

char toLowerCase(char c) {
    return c |= ' ';
}

