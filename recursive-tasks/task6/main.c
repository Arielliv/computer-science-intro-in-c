/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>

void minMax(int arr[], int left, int right, int min_max[]);

void main() {
    int arr[10];
    int min_max[2] = {INT_MAX, INT_MIN};
    int userNumberInput1, userNumberInput2, userNumberInput3, userNumberInput4, userNumberInput5, leftIndex, rightIndex;

    scanf("%d %d %d %d %d %d %d", &userNumberInput1, &userNumberInput2, &userNumberInput3, &userNumberInput4, &userNumberInput5,
          &leftIndex, &rightIndex);

    arr[0] = userNumberInput1;
    arr[1] = userNumberInput2;
    arr[2] = userNumberInput3;
    arr[3] = userNumberInput4;
    arr[4] = userNumberInput5;

    minMax(arr, leftIndex, rightIndex, min_max);
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
