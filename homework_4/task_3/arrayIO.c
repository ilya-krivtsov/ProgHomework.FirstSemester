#include "arrayIO.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool readFromStream(FILE *file, int **array, int *arrayLength) {
    int arrayCapacity = 4;
    *arrayLength = 0;
    *array = malloc(arrayCapacity * sizeof(int));

    if (array == NULL) {
        return false;
    }

    while (!feof(file)) {
        int value = -1;
        if (fscanf(file, "%d", &value) != 1) {
            continue;
        }

        if (*arrayLength == arrayCapacity) {
            arrayCapacity *= 2;
            *array = realloc(*array, arrayCapacity * sizeof(int));
            if (*array == NULL) {
                return false;
            }
        }
        (*array)[*arrayLength] = value;
        ++*arrayLength;
    }

    return true;
}
