/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

void printRuler(int k);

void printPatternRecur(int i, int j, int k);

int main() {
    int userSizeInput, limit;
    scanf("%d", &userSizeInput);

    printRuler(userSizeInput);
    return 0;
}


void printRuler(int k) {
    int i;
    if (k - 1 > 0) {
        printRuler(k - 1);
    }
    for (i= 0; i < k; ++i) {
        printf("-");
    }
    printf("\n");
    if (k - 1 > 0) {
        printRuler(k - 1);
    }

}

void printPatternRecur(int i, int j, int k) {
    if (k == 0) {
        return;
    }
    printPatternRecur(i, (i + j) / 2, k - 1);
    for (int l = 0; l < k; ++l) {
        printf("-");
    }
    printf("\n");
    printPatternRecur((i + j) / 2, j, k - 1);
}