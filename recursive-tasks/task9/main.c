#include <stdio.h>
#include <stdbool.h>

#define USER_INPUT_SIZE 5

bool subsetSum(int numbers[], int size, int sum);

int main() {
    int userInputArray[USER_INPUT_SIZE];
    int sum;
    int result;
    int index;

    for (index = 0; index < USER_INPUT_SIZE; ++index) {
        scanf("%d", &userInputArray[index]);
    }

    scanf("%d", &sum);

    result = subsetSum(userInputArray, 5, sum) ? 1 : 0;
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