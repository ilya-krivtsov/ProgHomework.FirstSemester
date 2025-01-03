#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frequencyLookup.h"

bool isNonWord(char c) {
    return c == ' ' || c == EOF || c == '\n' || c == '\r';
}

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

    char buffer[1024] = { '\0' };
    int bufferIndex = 0;
    while (!feof(file)) {
        int c = fgetc(file);
        if (bufferIndex >= (int)sizeof(buffer) || isNonWord(c)) {
            if (bufferIndex == 0) {
                continue;
            }

            int frequency = -1;
            if (!getFrequencyByString(lookup, buffer, &frequency)) {
                frequency = 0;
            }
            ++frequency;
            addFrequency(lookup, buffer, frequency);
            memset(buffer, 0, sizeof(buffer));
            bufferIndex = 0;
        } else {
            buffer[bufferIndex] = c;
            ++bufferIndex;
        }
    }

    int count = getCount(lookup);
    printf("word count: %d\n", count);

    int capacity = getCapacity(lookup);
    int maxBucketLength = getMaxBucketLength(lookup);
    float averageBucketLength = getAverageBucketLength(lookup);
    printf("capacity: %d, max bucket length: %d, average length of non-empty buckets: %lf\n", capacity, maxBucketLength, averageBucketLength);
    printf("occupancy ratio: %lf\n", (float)count / capacity);

    const char **strings = malloc(sizeof(char *) * count);
    int *frequencies = malloc(sizeof(int) * count);

    LookupIterator *iterator = getIterator(lookup);
    int index = 0;
    while (moveNext(iterator)) {
        const char *string = NULL;
        int frequency = 0;
        getCurrent(iterator, &string, &frequency);

        strings[index] = string;
        frequencies[index] = frequency;
        ++index;
    }
    disposeIterator(iterator);

    printf("words:\n");

    for (int i = 0; i < count; ++i) {
        int j = count - i - 1;
        printf("\"%s\" : %d\n", strings[j], frequencies[j]);
    }

    disposeLookup(lookup);

    fclose(file);
}
