#pragma once

#include <stdbool.h>

typedef struct FrequencyLookup FrequencyLookup;

typedef struct LookupIterator LookupIterator;

bool createLookup(FrequencyLookup **lookup);

bool addFrequency(FrequencyLookup *lookup, const char *string, int frequency);

bool getFrequencyByString(FrequencyLookup *lookup, const char *string, int *frequency);

LookupIterator *getIterator(FrequencyLookup *lookup);

int getCount(FrequencyLookup *lookup);

int getCapacity(FrequencyLookup *lookup);

int getMinBucketLength(FrequencyLookup *lookup);

int getMaxBucketLength(FrequencyLookup *lookup);

void disposeLookup(FrequencyLookup *lookup);

bool moveNext(LookupIterator *iterator);

void getCurrent(LookupIterator *iterator, const char **string, int *frequency);

void disposeIterator(LookupIterator *iterator);
