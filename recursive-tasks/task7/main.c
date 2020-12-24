/*315363366*/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>

void intToStr(unsigned int num, char s[]);

void main() {
    char s[10];
    int userInputNumber;
    scanf("%d", &userInputNumber);
    intToStr(userInputNumber, s);
    printf("%s", s);
}

void intToStr(unsigned int num, char s[]) {
    if (num <= 0) {
        return;
    }
    int currentNumber = (num % 10);
    intToStr(num / 10, s);
    s[strlen(s)] = (char) currentNumber + '0';
    s[strlen(s) + 1] = '\0';
}