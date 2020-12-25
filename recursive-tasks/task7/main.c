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
    if (num / 10 == 0) {
        s[0] = (char) (num) + '0';
        s[1] = '\0';
        return;
    }
    intToStr(num / 10, s);
    int currentNumber = (num % 10);
    int lastIndex = strlen(s);
    s[lastIndex] = (char) (currentNumber) + '0';
    s[lastIndex + 1] = '\0';
}