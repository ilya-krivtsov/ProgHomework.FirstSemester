#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VALUE_MIN -4096
#define VALUE_MAX 4095
#define VALUES_COUNT (VALUE_MAX - VALUE_MIN)

void countingSort(int *array, int arrayLength) {
    int *countingArray = calloc(VALUES_COUNT, sizeof(int));

    for (int i = 0; i < arrayLength; ++i) {
        ++countingArray[array[i] - VALUE_MIN];
    }

    int arrayPointer = 0;

    for (int i = 0; i < VALUES_COUNT; ++i) {
        int count = countingArray[i];
        for (int k = 0; k < count; ++k) {
            array[arrayPointer] = i + VALUE_MIN;
            ++arrayPointer;
        }
    }
}

void bubbleSort(int *array, int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        bool swappedAny = false;
        for (int j = arrayLength - 1; j > i; --j) {
            if (array[j - 1] > array[j]) {
                swappedAny = true;

                int t = array[j - 1];
                array[j - 1] = array[j];
                array[j] = t;
            }
        }

        if (!swappedAny) {
            break;
        }
    }
}

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

int main() {
    const int arrayLength = 100000;

    int *arrayA = calloc(arrayLength, sizeof(int)),
        *arrayB = calloc(arrayLength, sizeof(int));

    srand(time(NULL));
    randomizeArray(arrayA, arrayLength, VALUE_MIN, VALUE_MAX);
    arrayB = memcpy(arrayB, arrayA, arrayLength * sizeof(int));

    printf("counting sort sorted array of %d elements in %.2f us\n", arrayLength, measureTime(countingSort, arrayA, arrayLength) / 1000.0);
    printf("bubble sort   sorted array of %d elements in %.2f us\n", arrayLength, measureTime(bubbleSort, arrayA, arrayLength) / 1000.0);
}
