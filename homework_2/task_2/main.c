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

// returns false if allocation failed
// result: time in nanoseconds
bool measureMeanTime(bool (*sortingAlgoritm)(int *, int), int *array, int arrayLength, double *result) {
    long long totalTime = 0;
    const int iterations = 256;

    for (int i = 0; i < iterations; ++i) {
        struct timespec startTime;
        clock_gettime(CLOCK_MONOTONIC, &startTime);

        if (!sortingAlgoritm(array, arrayLength)) {
            return false;
        }

        struct timespec endTime;
        clock_gettime(CLOCK_MONOTONIC, &endTime);

        long long elapsedNanoseconds = (endTime.tv_nsec - startTime.tv_nsec);
        long long elapsedSeconds = (endTime.tv_sec - startTime.tv_sec);

        totalTime += elapsedNanoseconds + (elapsedSeconds * 1'000'000'000);
    }

    *result = (double)totalTime / iterations;
    return true;
}

int main(void) {
    const int arrayLength = 100000;

    int *countingSortArray = calloc(arrayLength, sizeof(int));
    int *bubbleSortArray = calloc(arrayLength, sizeof(int));

    if (countingSortArray == NULL || bubbleSortArray == NULL) {
        free(countingSortArray);
        free(bubbleSortArray);
        return 1;
    }

    srand(time(NULL));
    randomizeArray(countingSortArray, arrayLength, -4096, 4095);
    bubbleSortArray = memcpy(bubbleSortArray, countingSortArray, arrayLength * sizeof(int));

    double countingSortTime = 0;
    double bubbleSortTime = 0;

    if (measureMeanTime(countingSort, countingSortArray, arrayLength, &countingSortTime) &&
        measureMeanTime(bubbleSort, countingSortArray, arrayLength, &bubbleSortTime)) {
        printf("counting sort sorted array of %d elements in %.2f us\n", arrayLength, countingSortTime / 1000.0);
        printf("bubble sort   sorted array of %d elements in %.2f us\n", arrayLength, bubbleSortTime / 1000.0);
    } else {
        printf("allocation error occured while sorting\n");
        free(countingSortArray);
        free(bubbleSortArray);
        return 1;
    }

    free(countingSortArray);
    free(bubbleSortArray);
}
