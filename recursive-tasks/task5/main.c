/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void printPrimeFactors(int num);

int main() {
    int userNumberInput;
    scanf("%d", &userNumberInput);
    printPrimeFactors(userNumberInput);
}

void printPrimeFactors(int num) {
    int i = 2;
    if (num == 1) {
        return;
    }
    while (num % i != 0) {
        i++;
    }
    printf("%d ", i);
    printPrimeFactors(num / i);
}
