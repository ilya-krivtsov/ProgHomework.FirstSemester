#include <stdio.h>

#include "frequencyLookup.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    FrequencyLookup *lookup = NULL;
    if (!createLookup(&lookup)) {
        printf("allocation error\n");
        return 1;
    }

    disposeLookup(lookup);

    fclose(file);
}
