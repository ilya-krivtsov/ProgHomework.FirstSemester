#include "frequencyLookup.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frequencyList.h"

typedef struct FrequencyLookup {
    FrequencyList **buckets;
    int capacity;
    int count;
} FrequencyLookup;

typedef struct LookupIterator {
    FrequencyLookup *lookup;
    int bucketIndex;
    FrequencyElement *currentElement;
} LookupIterator;

static bool createLookupInternal(FrequencyLookup **lookup, int capacity) {
    FrequencyLookup *newLookup = malloc(sizeof(FrequencyLookup));

    if (newLookup == NULL) {
        return false;
    }

    newLookup->count = 0;
    newLookup->capacity = capacity;
    newLookup->buckets = malloc(sizeof(FrequencyList *) * newLookup->capacity);

    bool failed = false;
    for (int i = 0; i < newLookup->capacity; ++i) {
        if (!createFrequencyList(&(newLookup->buckets[i]))) {
            failed = true;
            break;
        }
    }

    if (failed) {
        disposeLookup(newLookup);
        return false;
    }

    *lookup = newLookup;
    return true;
}

bool createLookup(FrequencyLookup **lookup) {
    return createLookupInternal(lookup, 64);
}

static unsigned int getStringHash(const char *string) {
    unsigned int hash = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        hash = hash * 57 + string[i];
    }
    return hash;
}

static void disposeBuckets(FrequencyLookup *lookup) {
    for (int i = 0; i < lookup->capacity; ++i) {
        disposeList(lookup->buckets[i]);
    }
}

static bool expandLookup(FrequencyLookup *lookup) {
    int newCapacity = lookup->capacity * 4;

    FrequencyLookup *newLookup = NULL;
    if (!createLookupInternal(&newLookup, newCapacity)) {
        return false;
    }

    LookupIterator *iterator = getIterator(lookup);
    while (moveNext(iterator)) {
        const char *string = NULL;
        int frequency = 0;
        getCurrent(iterator, &string, &frequency);

        if (!addFrequency(newLookup, string, frequency)) {
            return false;
        }
    }
    disposeIterator(iterator);

    disposeBuckets(lookup);

    // copy new lookup to old one
    *lookup = *newLookup;

    // free(), because disposeLookup() will dispose buckets
    free(newLookup);

    return true;
}

bool addFrequency(FrequencyLookup *lookup, const char *string, int frequency) {
    if ((float)lookup->count / lookup->capacity > 4.0) {
        expandLookup(lookup);
    }

    int bucketIndex = getStringHash(string) % lookup->capacity;
    FrequencyList *bucket = lookup->buckets[bucketIndex];
    FrequencyElement *element = getFirstElement(bucket);

    while (element != NULL) {
        const char *elementString = getString(element);
        if (strcmp(string, elementString) == 0) {
            setFrequency(element, frequency);
            return true;
        }
        element = getNextElement(element);
    }

    element = addNewElement(bucket);
    if (element == NULL) {
        return false;
    }

    ++lookup->count;
    setString(element, string);
    setFrequency(element, frequency);
    return true;
}

bool getFrequencyByString(FrequencyLookup *lookup, const char *string, int *frequency) {
    int bucketIndex = getStringHash(string) % lookup->capacity;
    FrequencyList *bucket = lookup->buckets[bucketIndex];
    FrequencyElement *element = getFirstElement(bucket);

    while (element != NULL) {
        const char *elementString = getString(element);
        if (strcmp(string, elementString) == 0) {
            *frequency = getFrequency(element);
            return true;
        }
        element = getNextElement(element);
    }

    return false;
}

LookupIterator *getIterator(FrequencyLookup *lookup) {
    LookupIterator *iterator = malloc(sizeof(LookupIterator));
    if (iterator == NULL) {
        return NULL;
    }

    iterator->lookup = lookup;
    iterator->bucketIndex = -1;
    iterator->currentElement = NULL;

    return iterator;
}

int getCount(FrequencyLookup *lookup) {
    return lookup->count;
}

int getCapacity(FrequencyLookup *lookup) {
    return lookup->capacity;
}

int getMinBucketLength(FrequencyLookup *lookup) {
    int length = -1;
    for (int i = 0; i < lookup->capacity; ++i) {
        int bucketLength = getLength(lookup->buckets[i]);
        if (length == -1 || bucketLength < length) {
            length = bucketLength;
        }
    }
    return length;
}

int getMaxBucketLength(FrequencyLookup *lookup) {
    int length = -1;
    for (int i = 0; i < lookup->capacity; ++i) {
        int bucketLength = getLength(lookup->buckets[i]);
        if (length == -1 || bucketLength > length) {
            length = bucketLength;
        }
    }
    return length;
}

void disposeLookup(FrequencyLookup *lookup) {
    disposeBuckets(lookup);
    free(lookup);
}

bool moveNext(LookupIterator *iterator) {
    while (iterator->currentElement == NULL) {
        ++iterator->bucketIndex;
        if (iterator->bucketIndex >= iterator->lookup->capacity) {
            return false;
        }
        iterator->currentElement = getFirstElement(iterator->lookup->buckets[iterator->bucketIndex]);
    }

    return true;
}

void getCurrent(LookupIterator *iterator, const char **string, int *frequency) {
    *string = getString(iterator->currentElement);
    *frequency = getFrequency(iterator->currentElement);

    iterator->currentElement = getNextElement(iterator->currentElement);
}

void disposeIterator(LookupIterator *iterator) {
    free(iterator);
}
