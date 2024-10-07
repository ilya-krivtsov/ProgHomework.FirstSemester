#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "halfQSort.h"

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

void printArray(const int *array, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d", array[i]);
        if (i != length - 1)
            printf(", ");
    }
    printf("\n");
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value = -1;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
    return value;
}

int main(void) {
    int arrayLength = readValue("enter array length: ", "incorrect value: array length cannot be less than zero; try again: ");

    int *array = calloc(arrayLength, sizeof(int));
    if (array == NULL) {
        return 1;
    }

    srand(time(NULL));
    randomizeArray(array, arrayLength, -4096, 4096);

    printf("array before halfQSort:\n");
    printArray(array, arrayLength);

    halfQSort(array, arrayLength);

    printf("array after halfQSort:\n");
    printArray(array, arrayLength);

    free(array);
}
