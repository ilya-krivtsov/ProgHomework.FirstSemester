#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frequencyLookup.h"

int readNextUTF8(FILE *stream) {
    int c = fgetc(stream);
    if (c == EOF) {
        return EOF;
    }

    if (c < 0b1'0000000) {
        return c;
    }

    int expectedLength = 0;
    int result = EOF;
    if ((c >> 5) == 0b110) {
        expectedLength = 1;
        result = c & 0b000'11111;
    } else if ((c >> 4) == 0b1110) {
        expectedLength = 2;
        result = c & 0b0000'1111;
    } else if ((c >> 3) == 0b11110) {
        expectedLength = 3;
        result = c & 0b00000'111;
    } else {
        return EOF;
    }

    for (int i = 0; i < expectedLength; ++i) {
        result <<= 6;
        c = fgetc(stream);
        if (c == EOF) {
            return EOF;
        }
        if ((c >> 6) != 0b10) {
            return EOF;
        }

        result |= (c & 0b00'111111);
    }

    return result;
}

void writeToBuffer(int utfChar, char *buffer, int *bufferIndex, int bufferLength) {
    if (*bufferIndex >= bufferLength) {
        return;
    }

    if (utfChar >= 0x0000 && utfChar <= 0x007F) {
        buffer[*bufferIndex] = utfChar;
        ++(*bufferIndex);
        return;
    }

    int byteLength = 0;
    if (utfChar >= 0x0080 && utfChar <= 0x07FF) {
        byteLength = 1;
        buffer[*bufferIndex] = 0b110'00000 | ((utfChar >> 6) & 0b000'11111);
    } else if (utfChar >= 0x0800 && utfChar <= 0xFFFF) {
        byteLength = 2;
        buffer[*bufferIndex] = 0b1110'0000 | ((utfChar >> 12) & 0b000'11111);
    } else if (utfChar >= 0x10000 && utfChar <= 0x10FFFF) {
        byteLength = 3;
        buffer[*bufferIndex] = 0b11110'000 | ((utfChar >> 18) & 0b000'11111);
    }
    ++(*bufferIndex);

    for (int i = byteLength - 1; i >= 0; --i) {
        if (*bufferIndex >= bufferLength) {
            return;
        }

        buffer[*bufferIndex] = 0b10'000000 | ((utfChar >> i * 6) & 0b00'111111);
        ++(*bufferIndex);
    }
}

int  partition(const char **strings, int *frequencies, int left, int right) {
    if (left >= right) {
        return left;
    }

    int pivot = frequencies[left];
    --left;
    ++right;
    while (true) {
        do {
            ++left;
        } while (frequencies[left] < pivot);
        do {
            --right;
        } while (frequencies[right] > pivot);

        if (left >= right) {
            break;
        }

        int frequency = frequencies[left];
        frequencies[left] = frequencies[right];
        frequencies[right] = frequency;

        const char *string = strings[left];
        strings[left] = strings[right];
        strings[right] = string;
    }

    return right;
}

void sortStrings(const char **strings, int *frequencies, int left, int right) {
    if (left >= right) {
        return;
    }

    int part = partition(strings, frequencies, left, right);
    sortStrings(strings, frequencies, left, part);
    sortStrings(strings, frequencies, part + 1, right);
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
        int utfChar = readNextUTF8(file);

        if ((utfChar >= 0x41 && utfChar <= 0x5A) || // A-Z
            (utfChar >= 0x61 && utfChar <= 0x7A) || // a-z
            (utfChar >= 0x0410 && utfChar <= 0x04FF) || // А-Я + а-я
            (utfChar == 0x0401 || utfChar == 0x0451)) { // Ё + ё
            writeToBuffer(utfChar, buffer, &bufferIndex, sizeof(buffer));
        } else {
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
        }
    }

    int count = getCount(lookup);
    printf("count: %d\n", count);

    int capacity = getCapacity(lookup);
    int minBucketLength = getMinBucketLength(lookup);
    int maxBucketLength = getMaxBucketLength(lookup);
    printf("capacity: %d, min length: %d, max length: %d]\n", capacity, minBucketLength, maxBucketLength);
    printf("occup: %lf\n", (float)count / capacity);

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

    sortStrings(strings, frequencies, 0, count - 1);

    printf("words:\n");

    for (int i = 0; i < count; ++i) {
        int j = count - i - 1;
        printf("%s : %d\n", strings[j], frequencies[j]);

        if (i >= 20) {
            break;
        }
    }

    disposeIterator(iterator);

    disposeLookup(lookup);

    fclose(file);
}
