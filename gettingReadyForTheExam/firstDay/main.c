// 315363366


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

int binarySearchRecursive(int *array, int value, int left, int right);

int binarySearchIterative(int *array, int size, int value);

void swap(int *value1, int *value2);

void mergeSort(int *array, int size);

int *mergeArrays(int *array1, int size1, int *array2, int size2);

void copyArray(int *des, int *src, int size);

int countRulingRows(int matNum[][MAX_SIZE], int size);

void swapInArrays(int array1[], int array2[], int index);

void arrangeArrays(int data1[], int data2[], int size);

int gcd(int num1, int num2);

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

    int mat[][MAX_SIZE] = {{1,  2,  4,  3, 2},
                           {4,  5,  6,  5, 4},
                           {4,  4,  6,  5, 5},
                           {15, 20, 10, 2, 4},
                           {15, 20, 10, 5, 5}};
    int re = countRulingRows(mat, 5);
    printf("%d\n", re);

    int data1[] = {2, -3, 5, -7, 8};
    int data2[] = {5, -3, 9, -9, 10};
    printf("data1 before: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data1[i]);
    }
    printf("\ndata2 before: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data2[i]);
    }
    arrangeArrays(data1, data2, 5);

    printf("\ndata1 after: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data1[i]);
    }
    printf("\ndata2 after: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data2[i]);
    }

    printf("\n%d", gcd(24, 36));
    printf("\n%d", gcd(12, 17));
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


//*********************************************************************************************************************//
//  2015 question 3
// first try
//int countRulingRows(int matNum[][MAX_SIZE], int size) {
//    int i, y, j;
//    int counterRows = 0, counterInRows = 0, counter = 0;
//    int comp;
//    for (i = 1; i < size; i++) {
//        for (y = 0; y < size; y++) {
//            comp = matNum[i][y];
//            for (j = i - 1; j >= 0; j--) {
//                if (comp < matNum[j][y]) {
//                    counter++;
//                }
//            }
//            if (counter == 0) {
//                counterInRows++;
//            }
//            counter = 0;
//        }
//        if (counterInRows == size) {
//            counterRows++;
//        }
//        counterInRows = 0;
//    }
//    return counterRows;
//}

int countRulingRows(int matNum[][MAX_SIZE], int size) {
    int i, y, j;
    int maxArray[MAX_SIZE];
    int counter = 0;
    bool isRuling = false;
    for (i = 0; i < size; i++) {
        maxArray[i] = matNum[0][i];
    }

    for (y = 1; y < size; y++) {
        isRuling = true;
        for (j = 0; j < size; j++) {
            if (maxArray[j] <= matNum[y][j]) {
                maxArray[j] = matNum[y][j];
            } else {
                isRuling = false;
            }
        }
        if (isRuling) {
            counter++;
        }
    }

    return counter;
}

//  2015 question 4.1
void arrangeArrays(int data1[], int data2[], int size) {
    if (size == 0) {
        return;
    }

    if (data1[size - 1] > data2[size - 1]) {
        swapInArrays(data1, data2, size - 1);
    }
    arrangeArrays(data1, data2, size - 1);
}

void swapInArrays(int array1[], int array2[], int index) {
    int tmp = array1[index];
    array1[index] = array2[index];
    array2[index] = tmp;
}

// 2015 question 4.2

int gcd(int num1, int num2) {
    int result = num1;
    if (num1 == num2) {
        return result;
    }
    if (num1 > num2) {
        result = gcd(num2, num1 - num2);
    } else {
        result = gcd(num1, num2 - num1);
    }
    return result;
}