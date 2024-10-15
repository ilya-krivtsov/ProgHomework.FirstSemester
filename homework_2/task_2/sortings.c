#include "sortings.h"

#include <stdbool.h>
#include <stdlib.h>

bool countingSort(int *array, int arrayLength) {
    if (arrayLength == 0) {
        return true;
    }

    int maxElement = array[0];
    int minElement = array[0];

    for (int i = 0; i < arrayLength; ++i) {
        if (array[i] > maxElement) {
            maxElement = array[i];
        }

        if (array[i] < minElement) {
            minElement = array[i];
        }
    }

    int valuesCount = maxElement - minElement + 1;
    if (valuesCount < 0) {
        return false;
    }

    int *countingArray = calloc(valuesCount, sizeof(int));
    if (countingArray == NULL) {
        return false;
    }

    for (int i = 0; i < arrayLength; ++i) {
        ++countingArray[array[i] - minElement];
    }

    int arrayPointer = 0;

    for (int i = 0; i < valuesCount; ++i) {
        int count = countingArray[i];
        for (int k = 0; k < count; ++k) {
            array[arrayPointer] = i + minElement;
            ++arrayPointer;
        }
    }

    free(countingArray);
}

bool bubbleSort(int *array, int arrayLength) {
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

    return true;
}
