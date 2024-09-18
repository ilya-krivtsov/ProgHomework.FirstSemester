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

void printArray(const int *array, int arrayLength) {
    printf("[ ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d", array[i]);
        if (i != arrayLength - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

int main() {
    int arrayLength = 16;
    printf("enter array length: ");
    while ((scanf("%d", &arrayLength) != 1) || arrayLength <= 0) {
        while (getchar() != '\n') {}
        printf("incorrect value: array length must be greater than zero; try again: ");
    }

    int *arrayA = calloc(arrayLength, sizeof(int)), *arrayB = calloc(arrayLength, sizeof(int));

    srand(time(NULL));
    randomizeArray(arrayA, arrayLength, VALUE_MIN, VALUE_MAX);
    arrayB = memcpy(arrayB, arrayA, arrayLength * sizeof(int));

    printf("random array:\n");
    printArray(arrayA, arrayLength);

    countingSort(arrayA, arrayLength);
    printf("sorted with counting sort:\n");
    printArray(arrayA, arrayLength);

    bubbleSort(arrayB, arrayLength);
    printf("sorted with bubble sort:\n");
    printArray(arrayB, arrayLength);
}
