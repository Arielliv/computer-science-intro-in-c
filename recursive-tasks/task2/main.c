/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printAsteriskRow(int n);

void printOppositeTriangles(int n);

void main() {
    int userSizeInput;
    scanf("%d", &userSizeInput);
    printOppositeTriangles(userSizeInput);
}


void printOppositeTriangles(int n) {
    if (n < 1) {
        return;
    }
    printAsteriskRow(n);
    printOppositeTriangles(n - 1);
    printAsteriskRow(n);
}

void printAsteriskRow(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("*");
    }
    printf("\n");
}