/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#define WATER_PRICE 9
#define ORANGE_JUICE_PRICE 8
#define APPLE_JUICE_PRICE 8
#define SPRITE_PRICE 4
#define COLA_PRICE 4


#define WATER_SHAPE_SIGN 'W'
#define ORANGE_JUICE_SHAPE_SIGN 'O'
#define APPLE_JUICE_SHAPE_SIGN 'A'
#define SPRITE_SHAPE_SIGN 'S'
#define COLA_UPPER_CASE_SHAPE_SIGN 'C'
#define COLA_UPPER_LOWER_SHAPE_SIGN 'c'

/* get change amount and prints the change amount in coins view*/
void printChangeCoins(int changeAmount);

/*get coins and return amount in number*/
int getTotalCoinsAmount(int oneCoinsAmount, int twoCoinsAmount,
                        int fiveCoinsAmount, int tenCoinsAmount);

/*calc the change amount*/
int getChangeAmount(int currentPrice, int totalAmount);

/* get current bottle price and handles payment process*/
void pay(int currentPrice);

/*get shape size and prints water drew*/
void printWater(int shapeSize);

/*get shape size and prints orange drew*/
void printOrangeJuice(int shapeSize);

/*get shape size and prints apple drew*/
void printAppleJuice(int shapeSize);

/*get shape size and prints sprite drew*/
void printSprite(int shapeSize);

/*get shape size and prints cola drew*/
void printCola(int shapeSize);

/*get shape size, shape sign and weather should the half pyramid should start at right direction or not - and prints half pyramid drew*/
void printHalfPyramid(int shapeSize, char shapeSign, bool shouldStartAtRight);

/*get shape size, shape sign and prints pyramid drew*/
void printPyramid(int shapeSize, char shapeSign);

/*get shape size, shape sign and prints down side pyramid drew*/
void printDownSidePyramid(int shapeSize, char shapeSign);

/*This is a drink machine code.*/
/*It prints drink choices and get number as input from user selection.*/
/*It prints the price of the user selection drink and expect to get 4 numbers as amount of user money he pays*/
/*(amount of one coins, amount of two coins, amount of five coins, amount of ten coins).*/
/*returns change*/
/*in case of invalid selection or no enough money throws an error*/
/*in case of invalid drew size - finish the code run */
void main() {
    int drinkChoice = 0, drawSizeChoice = 0, currentPrice;
    int amountOfWaterBottles = 10, amountOfOrangeBottles = 10, amountOfAppleBottles = 10, amountOfColaBottles = 10, amountOfSpriteBottles = 10;

    printf("Please enter drawing's size:");
    scanf("%d", &drawSizeChoice);

    /*checks if drawSizeChoice has valid number*/
    if (drawSizeChoice > 0) {
        while (drinkChoice != 6) {
            printf("********************\n* Please choose:   *\n* 1. Water.        *\n* 2. Orange juice. *\n* 3. Apple juice.  *\n* 4. Sprite.       *\n* 5. Cola.         *\n* 6. exit.         *\n********************\n");
            scanf("%d", &drinkChoice);

            /*set current price and current bottle according to user selection*/
            switch (drinkChoice) {
                case 1:
                    currentPrice = WATER_PRICE;
                    if (amountOfWaterBottles == 0) {
                        printf("There are no bottles of water left.\n");
                    } else {
                        pay(currentPrice);
                        amountOfWaterBottles--;
                        printWater(drawSizeChoice);
                    }
                    break;
                case 2:
                    currentPrice = ORANGE_JUICE_PRICE;
                    if (amountOfOrangeBottles == 0) {
                        printf("There are no bottles of orange juice left.\n");
                    } else {
                        pay(currentPrice);
                        amountOfOrangeBottles--;
                        printOrangeJuice(drawSizeChoice);
                    }
                    break;
                case 3:
                    currentPrice = APPLE_JUICE_PRICE;
                    if (amountOfAppleBottles == 0) {
                        printf("There are no bottles of apple juice left.\n");
                    } else {
                        pay(currentPrice);
                        amountOfAppleBottles--;
                        printAppleJuice(drawSizeChoice);
                    }
                    break;
                case 4:
                    currentPrice = SPRITE_PRICE;
                    if (amountOfSpriteBottles == 0) {
                        printf("There are no bottles of sprite left.\n");
                    } else {
                        pay(currentPrice);
                        amountOfSpriteBottles--;
                        printSprite(drawSizeChoice);
                    }
                    break;
                case 5:
                    currentPrice = COLA_PRICE;
                    if (amountOfColaBottles == 0) {
                        printf("There are no bottles of cola left.\n");
                    } else {
                        pay(currentPrice);
                        amountOfColaBottles--;
                        printCola(drawSizeChoice);
                    }
                    break;
                case 6:
                    printf("Good bye.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
            }
        }
    } else {
        printf("Invalid size.");
        return;
    }

}

void printChangeCoins(int changeAmount) {
    int oneCoinsAmount = 0, twoCoinsAmount = 0, fiveCoinsAmount = 0, tenCoinsAmount = 0;
    int sum = 0;

    if (changeAmount == 0) {
        printf("Thank you for buying!\n");
    } else {
        while (sum < changeAmount) {
            if (sum + 10 <= changeAmount) {
                tenCoinsAmount++;
                sum += 10;
            } else if (sum + 5 <= changeAmount) {
                fiveCoinsAmount++;
                sum += 5;
            } else if (sum + 2 <= changeAmount) {
                twoCoinsAmount++;
                sum += 2;
            } else if (sum + 1 <= changeAmount) {
                oneCoinsAmount++;
                sum += 1;
            }
        }
        printf("You get back (1, 2, 5, 10): %d %d %d %d\nThank you for buying!\n", oneCoinsAmount, twoCoinsAmount,
               fiveCoinsAmount, tenCoinsAmount);
    }
}

int getTotalCoinsAmount(int oneCoinsAmount, int twoCoinsAmount,
                        int fiveCoinsAmount, int tenCoinsAmount) {
    int totalAmount = 0;
    /*checks if oneCoinsAmount bigger then 0 and count how many*/
    if (oneCoinsAmount > 0) {
        totalAmount += oneCoinsAmount * 1;
    }

    /*checks if twoCoinsAmount bigger then 0 and count how many*/
    if (twoCoinsAmount > 0) {
        totalAmount += twoCoinsAmount * 2;
    }

    /*checks if fiveCoinsAmount bigger then 0 and count how many*/
    if (fiveCoinsAmount > 0) {
        totalAmount += fiveCoinsAmount * 5;
    }

    /*checks if tenCoinsAmount bigger then 0 and count how many*/
    if (tenCoinsAmount > 0) {
        totalAmount += tenCoinsAmount * 10;
    }

    return totalAmount;
}

int getChangeAmount(int currentPrice, int totalAmount) {
    return (totalAmount - currentPrice);
}

void pay(int currentPrice) {
    int oneCoinsAmount = 0, twoCoinsAmount = 0, fiveCoinsAmount = 0, tenCoinsAmount = 0, totalAmount = 0;
    bool isPaymentProcessFinished = false;

    int changeAmount;

    printf("The price is %d nis.\n", currentPrice);
    while (!isPaymentProcessFinished) {
        printf("To pay please enter 4 numbers. The first number is the amount of\n"
               "1 nis coins, the second is the amount of 2 nis coins, then 5 and 10\n"
               "Please enter payment (1, 2, 5, 10):\n");
        scanf("%d %d %d %d", &oneCoinsAmount, &twoCoinsAmount, &fiveCoinsAmount, &tenCoinsAmount);

        totalAmount += getTotalCoinsAmount(oneCoinsAmount, twoCoinsAmount,
                                           fiveCoinsAmount, tenCoinsAmount);
        changeAmount = getChangeAmount(currentPrice, totalAmount);

        /*check if there change*/
        if (changeAmount > 0) {
            isPaymentProcessFinished = true;
            printf("Your change is: %d nis.\n", changeAmount);
            printChangeCoins(changeAmount);
        } else if (changeAmount == 0) {
            isPaymentProcessFinished = true;
            printChangeCoins(changeAmount);
        } else {
            printf("The amount does not suffice! Please enter %d more nis.\n", -changeAmount);
        }
    }
}


void printWater(int number) {
    int i, j;
    for (i = 0; i < number * 2; ++i) {
        for (j = 0; j < number; ++j) {
            if ((i == number - 1 || i == number) && number != 1) {
                if (j == 0) {
                    printf("%c ", WATER_SHAPE_SIGN);
                } else if (j == number - 1) {
                    printf(" %c", WATER_SHAPE_SIGN);
                } else {
                    printf("  ");
                }
            } else {
                printf("%c%c", WATER_SHAPE_SIGN, WATER_SHAPE_SIGN);
            }
        }
        printf("\n");
    }
}

void printOrangeJuice(int shapeSize) {
    printHalfPyramid(shapeSize, ORANGE_JUICE_SHAPE_SIGN, false);
}


void printAppleJuice(int shapeSize) {
    printHalfPyramid(shapeSize, APPLE_JUICE_SHAPE_SIGN, true);
}

void printSprite(int shapeSize) {
    printPyramid(shapeSize, SPRITE_SHAPE_SIGN);
}

void printCola(int shapeSize) {
    printDownSidePyramid(shapeSize, COLA_UPPER_CASE_SHAPE_SIGN);
    printPyramid(shapeSize, COLA_UPPER_LOWER_SHAPE_SIGN);
}

void printHalfPyramid(int shapeSize, char shapeSign, bool shouldStartAtRight) {
    int i, j;
    for (i = 0; i <= shapeSize; ++i) {
        for (j = 0; j < shapeSize; ++j) {
            if (shouldStartAtRight) {
                if (j >= shapeSize - i) {
                    printf("%c", shapeSign);
                } else {
                    printf(" ");
                }
            } else {
                if (j <= i - 1) {
                    printf("%c", shapeSign);
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void printPyramid(int shapeSize, char shapeSign) {
    for (int i = 1; i <= shapeSize; i++) {
        for (int space = 1; space <= shapeSize - i; space++) {
            printf(" ");
        }
        for (int symbol = 1; symbol <= (i * 2 - 1); symbol++) {
            printf("%c", shapeSign);
        }
        printf("\n");
    }
}

void printDownSidePyramid(int shapeSize, char shapeSign) {
    int i, j;
    for (i = shapeSize; i > 0; i--) {
        for (j = shapeSize; j > i; j--) {
            printf(" ");
        }
        for (j = 1; j < i * 2; j++) {
            printf("%c", shapeSign);
        }
        printf("\n");
    }
}