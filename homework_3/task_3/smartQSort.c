#include "smartQSort.h"

void insertionSort(int *array, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        for (int j = i - 1; j >= left; --j) {
            if (array[j] <= array[j + 1]) {
                break;
            }

            int temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}

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

void smartQuickSortInternal(int *array, int left, int right) {
    if (right - left + 1 <= 10) {
        insertionSort(array, left, right);
        return;
    }

    int part = partition(array, left, right);
    smartQuickSortInternal(array, left, part);
    smartQuickSortInternal(array, part + 1, right);
}

void quickSort(int *array, int arrayLength) {
    quickSortInternal(array, 0, arrayLength - 1);
}

void smartQuickSort(int *array, int arrayLength) {
    smartQuickSortInternal(array, 0, arrayLength - 1);
}
