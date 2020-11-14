/*315363366*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define WATER_PRICE 9
#define ORANGE_JUICE_OR_APPLE_JUICE_PRICE 8
#define SPRITE_OR_COLA_PRICE 4

/*This is a drink machine code.*/
/*It prints drink choices and get number as input from user selection.*/
/*It prints the price of the user selection drink and expect to get 4 numbers as amount of user money he pays*/
/*(amount of one coins, amount of two coins, amount of five coins, amount of ten coins).*/
/*returns change*/
/*in case of invalid selection or no enough money throws an error*/
void main() {
    int drinkChoice, currentPrice, changeAmount , totalMount = 0;
    int oneCoinsAmount, twoCoinsAmount, fiveCoinsAmount, tenCoinsAmount = 0;
    bool isValid = true;

    printf("Please choose:\n1. Water.\n2. Orange juice.\n3. Apple juice.\n4. Sprite.\n5. Cola.\n");
    scanf("%d", &drinkChoice);

    /*set current price according to user selection*/
    switch (drinkChoice) {
        case 1:
            currentPrice = WATER_PRICE;
            break;
        case 2:
        case 3:
            currentPrice = ORANGE_JUICE_OR_APPLE_JUICE_PRICE;
            break;
        case 4:
        case 5:
            currentPrice = SPRITE_OR_COLA_PRICE;
            break;
        default:
            isValid = false;
    }

    /*check if valid user input and print error or current price*/
    if (isValid){
        printf("The price is %d nis.\n", currentPrice);
    } else {
        printf("Invalid choice.\n");
        return;
    }

    printf("To pay please enter 4 numbers. The first number is the amount of\n"
           "1 nis coins, the second is the amount of 2 nis coins, then 5 and 10\n"
           "Please enter payment (1, 2, 5, 10):\n");
    scanf("%d %d %d %d", &oneCoinsAmount, &twoCoinsAmount, &fiveCoinsAmount, &tenCoinsAmount);

    /*checks if oneCoinsAmount bigger then 0 and count how many*/
    if(oneCoinsAmount > 0){
        for (int i = 0; i < oneCoinsAmount; ++i) {
            totalMount++;
        }
    }

    /*checks if twoCoinsAmount bigger then 0 and count how many*/
    if(twoCoinsAmount > 0){
        for (int i = 0; i < twoCoinsAmount; ++i) {
            totalMount += 2;
        }
    }

    /*checks if fiveCoinsAmount bigger then 0 and count how many*/
    if(fiveCoinsAmount > 0){
        for (int i = 0; i < fiveCoinsAmount; ++i) {
            totalMount += 5;
        }
    }

    /*checks if tenCoinsAmount bigger then 0 and count how many*/
    if(tenCoinsAmount > 0){
        for (int i = 0; i < tenCoinsAmount; ++i) {
            totalMount += 10;
        }
    }

    changeAmount = totalMount - currentPrice;

    /*check if there change*/
    if(changeAmount >=  0){
        printf("Your change is: %d nis.", changeAmount);
    } else {
        printf("The amount does not suffice!");
    }
}