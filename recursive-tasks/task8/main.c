/*315363366*/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>

#define NOTFOUND -1

bool haveSameElems(int arr1[], int arr2[], int size);

int linearSearch(int array[], int size, int num);

void main() {
    int array1[5];
    int array2[5];
    int userNumberInput1, userNumberInput2, userNumberInput3, userNumberInput4, userNumberInput5;
    int userNumberInput6, userNumberInput7, userNumberInput8, userNumberInput9, userNumberInput10;
    int result;

    scanf("%d %d %d %d %d", &userNumberInput1, &userNumberInput2, &userNumberInput3, &userNumberInput4,
          &userNumberInput5);
    scanf("%d %d %d %d %d", &userNumberInput6, &userNumberInput7, &userNumberInput8, &userNumberInput9,
          &userNumberInput10);
    array1[0] = userNumberInput1;
    array1[1] = userNumberInput2;
    array1[2] = userNumberInput3;
    array1[3] = userNumberInput4;
    array1[4] = userNumberInput5;

    array2[0] = userNumberInput6;
    array2[1] = userNumberInput7;
    array2[2] = userNumberInput8;
    array2[3] = userNumberInput9;
    array2[4] = userNumberInput10;

    result = haveSameElems(array1, array2, 5) ? 1 : 0;
    printf("%d", result);

}

int linearSearch(int array[], int size, int num) {
    int reply;

    if (size == 1) {
        if (array[0] == num) {
            reply = 0;
        } else {
            reply = NOTFOUND;
        }
    } else {
        reply = linearSearch(array, size - 1, num);
        if (reply == NOTFOUND && array[size - 1] == num) {
            reply = size - 1;
        }
    }
    return reply;
}


bool haveSameElems(int arr1[], int arr2[], int size) {
    bool result = true;
    int index;
    int temp;
    if (size == 0) {
        result = true;
    } else {
        index = linearSearch(arr2, size, arr1[size - 1]);
        if (index == NOTFOUND) {
            result = false;
        } else {
            temp = arr2[index];
            arr2[index] = arr2[size - 1];
            result = haveSameElems(arr1, arr2, size - 1);
            arr2[index] = temp;
        }
    }
    return result;
}