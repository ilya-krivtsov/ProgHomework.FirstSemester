#include "halfQSort.h"

#include <stdbool.h>
#include <stdio.h>

void swap(int *left, int *right) {
    int temp = *left;
    *left = *right;
    *right = temp;
}

void halfQSort(int *array, int arrayLength) {
    if (arrayLength == 0) {
        return;
    }

    int firstElement = array[0],
        pointerA = 0,
        pointerB = 0,
        pointerC = arrayLength - 1;

    while (pointerB <= pointerC) {
        if (array[pointerB] < firstElement) {
            swap(&array[pointerA], &array[pointerB]);
            ++pointerA;
            ++pointerB;
        } else if (array[pointerB] > firstElement) {
            swap(&array[pointerB], &array[pointerC]);
            --pointerC;
        } else {
            ++pointerB;
        }
    }
}
