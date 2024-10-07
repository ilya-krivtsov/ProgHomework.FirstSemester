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
double measureMeanTime(void (*sortingAlgoritm)(int *, int), int *array, int arrayLength) {
    long long totalTime = 0;
    const int iterations = 256;

    for (int i = 0; i < iterations; ++i) {
        struct timespec startTime;
        clock_gettime(CLOCK_MONOTONIC, &startTime);

        sortingAlgoritm(array, arrayLength);

        struct timespec endTime;
        clock_gettime(CLOCK_MONOTONIC, &endTime);

        long long elapsedNanoseconds = (endTime.tv_nsec - startTime.tv_nsec);
        long long elapsedSeconds = (endTime.tv_sec - startTime.tv_sec);

        totalTime += elapsedNanoseconds + (elapsedSeconds * 1'000'000'000);
    }

    return (double)totalTime / iterations;
}

int main(void) {
    const int arrayLength = 100000;

    int *arrayA = calloc(arrayLength, sizeof(int)),
        *arrayB = calloc(arrayLength, sizeof(int));

    if (arrayA == NULL || arrayB == NULL) {
        return 1;
    }

    srand(time(NULL));
    randomizeArray(arrayA, arrayLength, VALUE_MIN, VALUE_MAX);
    arrayB = memcpy(arrayB, arrayA, arrayLength * sizeof(int));

    printf("counting sort sorted array of %d elements in %.2f us\n", arrayLength, measureMeanTime(countingSort, arrayA, arrayLength) / 1000.0);
    printf("bubble sort   sorted array of %d elements in %.2f us\n", arrayLength, measureMeanTime(bubbleSort, arrayA, arrayLength) / 1000.0);

    free(arrayA);
    free(arrayB);
}
