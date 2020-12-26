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
    bool withLast, withoutLast;

    if (size == 0) {
        return (sum == 0);
    }
    withLast = subsetSum(numbers, size - 1, sum - numbers[size - 1]);
    withoutLast = subsetSum(numbers, size - 1, sum);
    return (withLast || withoutLast);
}