// 315363366


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int binarySearchRecursive(int *array, int value, int left, int right);

int binarySearchIterative(int *array, int size, int value);

void swap(int *value1, int *value2);

void mergeSort(int *array, int size);

int *mergeArrays(int *array1, int size1, int *array2, int size2);

void copyArray(int *des, int *src, int size);

void main() {
    int unSortedArray[] = {9, 1, 6, 10, 5, 3, 7, 8, 2, 4};

    printf("before merge sort\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", unSortedArray[i]);
    }
    printf("\n");

    mergeSort(unSortedArray, 10);
    printf("after merge sort\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", unSortedArray[i]);
    }

    printf("\n");

    int resultRecursive = binarySearchRecursive(unSortedArray, 10, 0, 10);
    int resultIterative = binarySearchIterative(unSortedArray, 10, 10);
    printf("Recursive solution %d, actual value : %d\n", resultRecursive, unSortedArray[resultRecursive]);
    printf("Iterative solution %d, actual value : %d\n", resultIterative, unSortedArray[resultIterative]);
}

int binarySearchRecursive(int *array, int value, int left, int right) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if (array[mid] == value) {
        return mid;
    } else if (value < array[mid]) {
        return binarySearchRecursive(array, value, left, mid - 1);
    } else if (value > array[mid]) {
        return binarySearchRecursive(array, value, mid + 1, right);
    }
}

int binarySearchIterative(int *array, int size, int value) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == value) {
            return mid;
        } else if (value < array[mid]) {
            right = mid - 1;
        } else if (value > array[mid]) {
            left = mid + 1;
        }
    }
}

void swap(int *value1, int *value2) {
    int *tmp;
    tmp = value1;
    *value1 = *value2;
    *value2 = *tmp;
}

void mergeSort(int *array, int size) {
    int *tmpArray = NULL;
    if (size <= 1) {
        return;
    }
    mergeSort(array, size / 2);
    mergeSort(array + size / 2, size - size / 2);
    tmpArray = mergeArrays(array, size / 2, array + size / 2, size - size / 2);
    if (tmpArray) {
        copyArray(array, tmpArray, size);
        free(tmpArray);
    } else {
        printf("error");
    }
}

int *mergeArrays(int *array1, int size1, int *array2, int size2) {
    int index1, index2, indexResult;
    int *tempArray = (int *) malloc(sizeof(int) * (size1 + size2));
    if (tempArray == NULL) {
        printf("error");
    } else {
        index1 = index2 = indexResult = 0;
        while ((index1 < size1) && (index2 < size2)) {
            if (array1[index1] <= array2[index2]) {
                tempArray[indexResult] = array1[index1];
                index1++;
            } else {
                tempArray[indexResult] = array2[index2];
                index2++;
            }
            indexResult++;
        }

        while (index1 < size1) {
            tempArray[indexResult] = array1[index1];
            index1++;
            indexResult++;
        }
        while (index2 < size2) {
            tempArray[indexResult] = array2[index2];
            index2++;
            indexResult++;
        }
    }
    return tempArray;
}

void copyArray(int *des, int *src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        des[i] = src[i];

    }
}