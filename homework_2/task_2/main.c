#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sortings.h"

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

// returns time in nanoseconds
long long measureTime(void (*sortingAlgoritm)(int *, int), int *array, int arrayLength) {
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    sortingAlgoritm(array, arrayLength);
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    return (endTime.tv_nsec - startTime.tv_nsec) + (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 * 1000;
}

int main(void) {
    const int arrayLength = 100000;

    int *arrayA = calloc(arrayLength, sizeof(int)),
        *arrayB = calloc(arrayLength, sizeof(int));

    srand(time(NULL));
    randomizeArray(arrayA, arrayLength, VALUE_MIN, VALUE_MAX);
    arrayB = memcpy(arrayB, arrayA, arrayLength * sizeof(int));

    printf("counting sort sorted array of %d elements in %.2f us\n", arrayLength, measureTime(countingSort, arrayA, arrayLength) / 1000.0);
    printf("bubble sort   sorted array of %d elements in %.2f us\n", arrayLength, measureTime(bubbleSort, arrayA, arrayLength) / 1000.0);

    free(arrayA);
    free(arrayB);
}
