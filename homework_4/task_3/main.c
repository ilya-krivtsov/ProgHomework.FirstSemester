#include <stdio.h>
#include <stdlib.h>

#include "frequencySearch.h"
#include "arrayIO.h"

int main(void) {
    char buffer[1024];
    printf("input file path: ");
    scanf("%1023s", buffer);

    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        perror("opening file failed");
        return 1;
    }

    int *array;
    int arrayLength;
    if (!readFromStream(file, &array, &arrayLength)) {
        printf("allocation error\n");
        return 1;
    }

    if (ferror(file)) {
        perror("read error");
        fclose(file);
        return 1;
    }
    fclose(file);

    int mostFrequentElement, occurrences;
    if (findMostFrequentElement(array, arrayLength, &mostFrequentElement, &occurrences)) {
        printf("most frequent element is %d (appears %d time%s)\n", mostFrequentElement, occurrences, occurrences == 1 ? "" : "s");
    } else {
        printf("couldn't find most frequent element: array is empty\n");
    }

    free(array);
}
