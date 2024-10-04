#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "frequencySearch.h"

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
}

int main(void) {
    int arrayLength = readValue("enter array length: ", "incorrect value: array length cannot be less than zero; try again: ");

    int *array = calloc(arrayLength, sizeof(int));
    if (array == NULL) {
        return 1;
    }

    srand(time(NULL));
    randomizeArray(array, arrayLength, 0, 128);

    int mostFrequentElement = 0, occurrences = 0;
    if (findMostFrequentElement(array, arrayLength, &mostFrequentElement, &occurrences)) {
        printf("most frequent element is %d; it appears %d times in array", mostFrequentElement, occurrences);
    } else {
        printf("couldn't find most frequent element: the array is empty\n");
    }

    free(array);
}
