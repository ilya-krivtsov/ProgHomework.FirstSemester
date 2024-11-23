#include "frequencyLookup.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "frequencyList.h"

typedef struct FrequencyLookup {
    FrequencyList **buckets;
    int capacity;
} FrequencyLookup;

bool createLookup(FrequencyLookup **lookup) {
    FrequencyLookup *newLookup = malloc(sizeof(FrequencyLookup));

    if (newLookup == NULL) {
        return false;
    }

    newLookup->capacity = 64;
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

static unsigned int getStringHash(const char *string) {
    unsigned int hash = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        hash = hash * 57 + string[i];
    }
    return hash;
}

// adds or creates new element
bool addFrequency(FrequencyLookup *lookup, const char *string, int frequency) {
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

void disposeLookup(FrequencyLookup *lookup) {
    for (int i = 0; i < lookup->capacity; ++i) {
        disposeList(lookup->buckets[i]);
    }
    free(lookup);
}
