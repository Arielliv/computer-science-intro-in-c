/*315363366*/

#define _CRT_SECURE_NO_WARNINGS
#define USER_INPUT_SIZE 5

#include <stdio.h>
#include <limits.h>

void minMax(int arr[], int left, int right, int min_max[]);

void main() {
    int min_max[2] = {INT_MAX, INT_MIN};
    int userInputArray[USER_INPUT_SIZE];
    int leftIndex, rightIndex;
    int index;

    for (index = 0; index < USER_INPUT_SIZE; ++index) {
        scanf("%d", &userInputArray[index]);
    }

    scanf("%d %d",&leftIndex, &rightIndex);

    minMax(userInputArray, leftIndex, rightIndex, min_max);
    printf("%d %d", min_max[0], min_max[1]);
}

void minMax(int arr[], int left, int right, int min_max[]) {
    if (left > right) {
        return;
    }

    if (min_max[0] > arr[left]) {
        min_max[0] = arr[left];
    }

    if (min_max[0] > arr[right]) {
        min_max[0] = arr[right];
    }

    if (min_max[1] < arr[left]) {
        min_max[1] = arr[left];
    }

    if (min_max[1] < arr[right]) {
        min_max[1] = arr[right];
    }

    minMax(arr, left + 1, right - 1, min_max);
}
