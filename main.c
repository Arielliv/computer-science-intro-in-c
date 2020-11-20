/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#define WATER_PRICE 9
#define ORANGE_JUICE_PRICE 8
#define APPLE_JUICE_PRICE 8
#define SPRITE_PRICE 4
#define COLA_PRICE 4

/* get change amount and prints the change amount in coins view*/
void printChangeCoins(int changeAmount);

/*get coins and return amount in number*/
int getTotalCoinsAmount(int oneCoinsAmount, int twoCoinsAmount,
                        int fiveCoinsAmount, int tenCoinsAmount);

/*calc the change amount*/
int getChangeAmount(int currentPrice, int totalAmount);

/* get current bottle price and handles payment process*/
void pay(int currentPrice);

/*This is a drink machine code.*/
/*It prints drink choices and get number as input from user selection.*/
/*It prints the price of the user selection drink and expect to get 4 numbers as amount of user money he pays*/
/*(amount of one coins, amount of two coins, amount of five coins, amount of ten coins).*/
/*returns change*/
/*in case of invalid selection or no enough money throws an error*/
void main() {
    int drinkChoice = 0, currentPrice;
    int amountOfWaterBottles = 10, amountOfOrangeBottles = 10, amountOfAppleBottles = 10, amountOfColaBottles = 10, amountOfSpriteBottles = 10;

    while (drinkChoice != 6) {
        printf("Please choose:\n1. Water.\n2. Orange juice.\n3. Apple juice.\n4. Sprite.\n5. Cola.\n6. exit.\n");
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
                }
                break;
            case 2:
                currentPrice = ORANGE_JUICE_PRICE;
                if (amountOfOrangeBottles == 0) {
                    printf("There are no bottles of orange juice left.\n");
                } else {
                    pay(currentPrice);
                    amountOfOrangeBottles--;
                }
                break;
            case 3:
                currentPrice = APPLE_JUICE_PRICE;
                if (amountOfAppleBottles == 0) {
                    printf("There are no bottles of apple juice left.\n");
                } else {
                    pay(currentPrice);
                    amountOfAppleBottles--;
                }
                break;
            case 4:
                currentPrice = SPRITE_PRICE;
                if (amountOfSpriteBottles == 0) {
                    printf("There are no bottles of sprite left.\n");
                } else {
                    pay(currentPrice);
                    amountOfSpriteBottles--;
                }
                break;
            case 5:
                currentPrice = COLA_PRICE;
                if (amountOfColaBottles == 0) {
                    printf("There are no bottles of cola left.\n");
                } else {
                    pay(currentPrice);
                    amountOfColaBottles--;
                }
                break;
            case 6:
                printf("Good bye.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
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