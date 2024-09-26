#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sortAndSearch.h"

int getRandom(int minValue, int maxValue) {
    int r = rand();
    return r * (maxValue - minValue) / RAND_MAX + minValue;
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf(prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf(incorrectValueMessage);
    }
}

int main(void) {
    int arrayLength = readValue("enter array length: ", "incorrect value: array length cannot be less than zero; try again: ");
    int numbersToCheckCount = readValue("enter amount of numbers to check: ", "incorrect value: amount cannot be less than zero; try again: ");

    int *array = calloc(arrayLength, sizeof(int));

    int minRandom = 0,
        maxRandom = 128;

    srand(time(NULL));

    for (int i = 0; i < arrayLength; ++i) {
        array[i] = getRandom(minRandom, maxRandom);
    }

    quickSort(array, arrayLength);

    int foundNumbers = 0;
    for (int i = 0; i < numbersToCheckCount; ++i) {
        int number = getRandom(minRandom, maxRandom);
        if (containsElement(array, arrayLength, number)) {
            ++foundNumbers;
        }
    }

    printf("out of %d randomly generated numbers %d %s in the array\n", numbersToCheckCount, foundNumbers, foundNumbers == 1 ? "was" : "were");
}
