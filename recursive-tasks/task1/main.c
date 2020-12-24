/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printTriangle(int n);
void printAsteriskRow(int n);

void main() {
    int userSizeInput;
    scanf("%d", &userSizeInput);
    printTriangle(userSizeInput);
}

void printTriangle(int n) {
    if (n < 1) {
        return;
    }
    printTriangle(n - 1);
    printAsteriskRow(n);
}

void printAsteriskRow(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("*");
    }
    printf("\n");
}
