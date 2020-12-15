/*315363366*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printTriangle(int n);

void printPatternRowRecur(int n);

void main() {
    int userSizeInput;
    scanf("%d",&userSizeInput);
    printTriangle(userSizeInput);
}

void printTriangle(int n) {
    if (n < 1) {
        return;
    }
    printTriangle(n - 1);
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
