#include "halfQSort.h"

#include <stdbool.h>
#include <stdio.h>

void halfQSort(int *array, int arrayLength) {
    if (arrayLength == 0) {
        return;
    }

    int firstElement = array[0];

    int left = -1;
    int right = arrayLength;

    while (true) {
        do {
            ++left;
        } while (array[left] < firstElement);
        do {
            --right;
        } while (array[right] >= firstElement);

        if (left >= right) {
            break;
        }

        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
    }
}
