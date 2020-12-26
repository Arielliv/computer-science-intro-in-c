/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printRuler(int k);

void printLine(int n);

void main() {
    int userSizeInput;
    scanf("%d", &userSizeInput);
    printRuler(userSizeInput);
}


void printRuler(int k) {
    if (k - 1 > 0) {
        printRuler(k - 1);
    }
    printLine(k);
    if (k - 1 > 0) {
        printRuler(k - 1);
    }
    if (k == 0) {
        return;
    }
}

void printLine(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("-");
    }
    printf("\n");
}