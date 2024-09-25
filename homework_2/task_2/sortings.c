#include "sortings.h"

#include <stdbool.h>
#include <stdlib.h>

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
