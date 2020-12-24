#include <stdio.h>
#include <stdbool.h>

bool subsetSum(int numbers[], int size, int sum);

int main() {
    int array[5];
    int sum;
    int result;
    int userNumberInput1, userNumberInput2, userNumberInput3, userNumberInput4, userNumberInput5;

    scanf("%d %d %d %d %d", &userNumberInput1, &userNumberInput2, &userNumberInput3, &userNumberInput4,
          &userNumberInput5);
    scanf("%d", &sum);

    result = subsetSum(array, 5, sum) ? 1 : 0;
    printf("%d", result);
}

bool subsetSum(int numbers[], int size, int sum) {
    bool result = true;
    int tempNumber, currentSum;
    if (size == 1) {
        if (numbers[0] == sum) {
            result = true;
        } else {
            result = false;
        }
    } else {
        if (sum == numbers[0]) {
            result = true;
        }

        for (int i = 0; i < size; ++i) {
            tempNumber = numbers[size - 1];
            numbers[size - 1] = numbers[i];
            numbers[i] = tempNumber;
            currentSum = sum - numbers[size - 1];
            if (currentSum > 0) {
                result = subsetSum(numbers, size - 1, currentSum);
            }

            numbers[i] = numbers[size - 1];
            numbers[size - 1] = tempNumber;
        }
    }
    return result;
}