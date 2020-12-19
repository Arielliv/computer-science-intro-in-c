/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printRuler(int k);

void main() {
    int userSizeInput, limit;
    scanf("%d", &userSizeInput);
    printRuler(userSizeInput);
}


void printRuler(int k) {
    int i;
    if (k - 1 > 0) {
        printRuler(k - 1);
    }
    for (i = 0; i < k; ++i) {
        printf("-");
    }
    printf("\n");
    if (k - 1 > 0) {
        printRuler(k - 1);
    }

}