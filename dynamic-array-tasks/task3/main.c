/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

int *blowUpArray(int numArray[], int amountArray[], int size);

// sum up all values in array
int getArrayValuesSum(int array[], int size);

// handle malloc failure
void handleMallocFailure();

void main() {
    int arraySize, index1, index2, newArraySize;
    int *numArray, *amountArray, *resultArray;
    scanf("%d", &arraySize);

    numArray = (int *) malloc(sizeof(int) * arraySize);
    if (numArray == NULL) {
        handleMallocFailure();
    }
    for (index1 = 0; index1 < arraySize; ++index1) {
        scanf("%d", &numArray[index1]);
    }

    amountArray = (int *) malloc(sizeof(int) * arraySize);
    if (amountArray == NULL) {
        handleMallocFailure();
    }
    for (index2 = 0; index2 < arraySize; ++index2) {
        scanf("%d", &amountArray[index2]);
    }

    resultArray = blowUpArray(numArray, amountArray, arraySize);
    newArraySize = getArrayValuesSum(amountArray, arraySize);
    for (int i = 0; i < newArraySize; ++i) {
        printf("%d ", resultArray[i]);
    }
    free(numArray);
    free(amountArray);
    free(resultArray);
}

int *blowUpArray(int numArray[], int amountArray[], int size) {
    int *tempArray;
    int newSize, i, j, counter = 0;
    newSize = getArrayValuesSum(amountArray, size);
    tempArray = (int *) malloc(sizeof(int) * newSize);
    if (tempArray == NULL) {
        handleMallocFailure();
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < amountArray[i]; j++) {
            tempArray[counter] = numArray[i];
            counter++;
        }
    }
    return tempArray;
}

int getArrayValuesSum(int array[], int size) {
    int i, sum = 0;
    for (i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

void handleMallocFailure() {
    printf("Memory allocation failure!!!\n");
    exit(1);
}