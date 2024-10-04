#include "frequencySearch.h"

#include <stdbool.h>
#include <stdio.h>

int partition(int *array, int left, int right) {
    int first = array[left], middle = array[(left + right) / 2], last = array[right];

    int pivot = first;
    if (first <= middle && middle <= last) {
        pivot = middle;
    } else if (middle <= first && first <= last) {
        pivot = first;
    } else {
        pivot = last;
    }

    --left;
    ++right;

    while (true) {
        do {
            ++left;
        } while (array[left] < pivot);
        do {
            --right;
        } while (array[right] > pivot);

        if (left >= right) break;

        int t = array[left];
        array[left] = array[right];
        array[right] = t;
    }

    return right;
}

void quickSort(int *array, int left, int right) {
    if (left >= right) {
        return;
    }

    int part = partition(array, left, right);
    quickSort(array, left, part);
    quickSort(array, part + 1, right);
}

bool findMostFrequentElement(int *array, int arrayLength, int *mostFrequentElement, int *occurrences) {
    if (arrayLength == 0) {
        return false;
    }

    quickSort(array, 0, arrayLength - 1);

    int element = array[0], count = 0;
    int maxCountElement = element, maxCount = count;

    for (int i = 0; i < arrayLength; ++i) {
        if (array[i] != element) {
            if (count > maxCount) {
                maxCount = count;
                maxCountElement = element;
            }
            count = 0;
            element = array[i];
        }
        ++count;
    }

    if (count > maxCount) {
        maxCount = count;
        maxCountElement = element;
    }

    if (mostFrequentElement != NULL) {
        *mostFrequentElement = maxCountElement;
    }
    if (occurrences != NULL) {
        *occurrences = maxCount;
    }

    return true;
}
