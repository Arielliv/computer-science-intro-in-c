/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printPatternRowRecur(int n);

void printOppositeTriangles(int n);

void main() {
    int userSizeInput;
    scanf("%d",&userSizeInput);
    printOppositeTriangles(userSizeInput);
}


void printOppositeTriangles(int n) {
    if (n < 1) {
        return;
    }
    printPatternRowRecur(n);
    printf("\n");
    printOppositeTriangles(n - 1);
    printPatternRowRecur(n);
    printf("\n");
}

void printPatternRowRecur(int n) {
    if (n < 1) {
        return;
    }
    printf("*");
    printPatternRowRecur(n - 1);
}