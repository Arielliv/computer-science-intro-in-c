/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

// get static back as result
int OrderStat(int array[], int size, int k);

// sort the array
void bubbleSort(int arr[], int size);

// swap between two places in the array
void swap(int *index1p, int *index2p);

void main() {
    int arraySize, index, k, result;
    int *inputArray;
    scanf("%d", &arraySize);

    inputArray = (int *) malloc(sizeof(int) * arraySize);
    for (index = 0; index < arraySize; ++index) {
        scanf("%d", &inputArray[index]);
    }

    scanf("%d", &k);
    result = OrderStat(inputArray, arraySize, k);
    printf("%d", result);
}

int OrderStat(int array[], int size, int k) {
    int *tempArray = array;
    bubbleSort(tempArray, size);
    return tempArray[k - 1];
}

void bubbleSort(int arr[], int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(int *index1p, int *index2p) {
    int tmp = *index1p;
    *index1p = *index2p;
    *index2p = tmp;
}