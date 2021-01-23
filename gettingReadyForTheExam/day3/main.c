#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int arr_concatenate(int a[], int a_sz, int b[], int b_sz, int c[]);

void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2);

int strToInt(char str[], int *size);

char *addNumInStr(char str[], int num);

void main() {
    int b[4] = {3, 4, 5, 6};
    int a[4] = {1, 2, 3, 4};
    int c[20] = {};
    int result = arr_concatenate(a, 4, b, 4, c);
    printf("%d\n", result);

    int sortedArr1[3] = {-3, 1, 5};
    int sortedArr2[8] = {-7, -1, -1, 1, 6};
    combineArrays(sortedArr1, 3, sortedArr2, 5);
    for (int i = 0; i < 8; i++) {
        printf("%d ", sortedArr2[i]);
    }
    char *n;
    n = addNumInStr("123ab4d5*+", 4565);
    printf("\n%s", n);

}


int arr_concatenate(int a[], int a_sz, int b[], int b_sz, int c[]) {
    if (a_sz == 0) {
        if (b_sz != 0) {
            c[0] = b[0];
            arr_concatenate(a, a_sz, b + 1, b_sz - 1, c + 1);
        }
    } else {
        c[0] = a[0];
        arr_concatenate(a + 1, a_sz - 1, b, b_sz, c + 1);
    }
    return (a_sz + b_sz);
}


void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2) {
    if (size1 == 0)
        return;
    if (size2 == 0) {
        sortedArr2[size1 - 1] = sortedArr1[size1 - 1];
        combineArrays(sortedArr1, size1 - 1, sortedArr2, size2);
    } else if (sortedArr1[size1 - 1] > sortedArr2[size2 - 1]) {
        sortedArr2[size1 + size2 - 1] = sortedArr1[size1 - 1];
        combineArrays(sortedArr1, size1 - 1, sortedArr2, size2);
    } else {
        sortedArr2[size1 + size2 - 1] = sortedArr2[size2 - 1];
        combineArrays(sortedArr1, size1, sortedArr2, size2 - 1);
    }
}


char *addNumInStr(char str[], int num) {
    char *sumNum;
    int newSize = 0;
    int i = 0;
    int newNum = strToInt(str, &newSize);
    char digit;
    newNum += num;
    sumNum = (char *) malloc(sizeof(char) * newSize + 1);
    sumNum[newSize - 1] = '\0';
    while (newNum / 10 != 0) {
        digit = (char) ('0' + newNum % 10);
        sumNum[newSize - i] = digit;
        i++;
        newNum = newNum / 10;
    }
    sumNum[0] = (char) ('0' + newNum);
    return sumNum;
}

int strToInt(char str[], int *size) {
    int counter, result;
    counter = 0;
    result = 0;
    while (str[counter] != '\0' & str[counter] >= '1' && str[counter] <= '9') {
        result = (result * 10) + (int) (str[counter] - '0');
        counter++;
    };
    *size = counter;
    return result;
}

