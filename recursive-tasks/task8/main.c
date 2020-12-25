/*315363366*/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>

#define NOTFOUND -1
#define USER_INPUT_SIZE 5

bool haveSameElems(int arr1[], int arr2[], int size);

int linearSearch(int array[], int size, int num);

void main() {
    int userInputArray1[USER_INPUT_SIZE];
    int userInputArray2[USER_INPUT_SIZE];
    int index;
    int result;

    for (index = 0; index < USER_INPUT_SIZE; ++index) {
        scanf("%d", &userInputArray1[index]);
    }
    for (index = 0; index < USER_INPUT_SIZE; ++index) {
        scanf("%d", &userInputArray2[index]);
    }

    result = haveSameElems(userInputArray1, userInputArray2, 5) ? 1 : 0;
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