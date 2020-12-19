/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int numWays(int n);

void main() {
    int userSizeInput;
    scanf("%d", &userSizeInput);
    printf("%d", numWays(userSizeInput));
}

int numWays(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }

    return numWays(n - 1) + numWays(n - 2);

}
