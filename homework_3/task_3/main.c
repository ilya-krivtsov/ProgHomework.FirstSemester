#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "smartQSort.h"

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf(prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf(incorrectValueMessage);
    }
}

long long measureTime(void (*sort)(int *, int), int *array, int arrayLength) {
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    sort(array, arrayLength);
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    return (endTime.tv_nsec - startTime.tv_nsec) + (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 * 1000;
}

int main(void) {
    int arrayLength = readValue("enter array length: ", "incorrect value: array length cannot be less than zero; try again: ");

    int *arrayA = calloc(arrayLength, sizeof(int)),
        *arrayB = calloc(arrayLength, sizeof(int));

    srand(time(NULL));
    randomizeArray(arrayA, arrayLength, 0, 1024);
    arrayB = memcpy(arrayB, arrayA, arrayLength * sizeof(int));

    printf("qsort:       %.2f ms\n", measureTime(quickSort, arrayA, arrayLength) / 1000.0 / 1000.0);
    printf("smart qsort: %.2f ms\n", measureTime(smartQuickSort, arrayB, arrayLength) / 1000.0 / 1000.0);

    free(arrayA);
    free(arrayB);
}
