#pragma once

#include <stdbool.h>

typedef struct FrequencyLookup FrequencyLookup;

bool createLookup(FrequencyLookup **lookup);

bool addFrequency(FrequencyLookup *lookup, const char *string, int frequency);

bool getFrequencyByString(FrequencyLookup *lookup, const char *string, int *frequency);

void disposeLookup(FrequencyLookup *lookup);
