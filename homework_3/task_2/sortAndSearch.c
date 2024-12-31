#include "sortAndSearch.h"

#include <stdbool.h>

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

void quickSortInternal(int *array, int left, int right) {
    if (left >= right) {
        return;
    }

    int part = partition(array, left, right);
    quickSortInternal(array, left, part);
    quickSortInternal(array, part + 1, right);
}

void quickSort(int *array, int arrayLength) {
    quickSortInternal(array, 0, arrayLength - 1);
}

bool containsElement(int *array, int arrayLength, int value) {
    if (arrayLength == 0) {
        return false;
    }

    int left = 0, right = arrayLength - 1;

    while (left <= right) {
        int middlePoint = (left + right) / 2,
            middleElement = array[middlePoint];

        if (value < middleElement) {
            right = middlePoint - 1;
        } else if (value > middleElement) {
            left = middlePoint + 1;
        } else {
            return true;
        }
    }

    return array[left] == value;
}
