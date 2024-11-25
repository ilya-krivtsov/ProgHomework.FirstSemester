#pragma once

#include <stdbool.h>

/// @brief Lookup of frequencies, where key is string and value is int
typedef struct FrequencyLookup FrequencyLookup;

/// @brief Iterator that iterates through lookup
typedef struct LookupIterator LookupIterator;

/// @brief Creates `FrequencyLookup`
/// @param lookup Pointer to store `FrequencyLookup` to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createLookup(FrequencyLookup **lookup);

/// @brief Adds new frequency to lookup or updates existing one
/// @param lookup Lookup to add frequency to
/// @param string String to add
/// @param frequency Frequency to add
/// @return `true` if added successfully, `false` otherwise (allocation failed)
bool addFrequency(FrequencyLookup *lookup, const char *string, int frequency);

/// @brief Tries to get frequency by string
/// @param lookup Lookup to get frequency from
/// @param string String to get frequency by
/// @param frequency Pointer to store frequency to
/// @return `true` if found corresponding frequency, `false otherwise`
bool getFrequencyByString(FrequencyLookup *lookup, const char *string, int *frequency);

/// @brief Creates new iterator
/// @param lookup Lookup to get iterator of
/// @return New iterator
LookupIterator *getIterator(FrequencyLookup *lookup);

/// @brief Gets count of entries in lookup
/// @param lookup Lookup to get count of
/// @return Count of entries
int getCount(FrequencyLookup *lookup);

/// @brief Gets capacity of lookup
/// @param lookup Lookup to get capacity of
/// @return Capacity of lookup
int getCapacity(FrequencyLookup *lookup);

/// @brief Gets min length of all buckets in lookup
/// @param lookup A lookup
/// @return Min length of all buckets in lookup
int getMinBucketLength(FrequencyLookup *lookup);

/// @brief Gets max length of all buckets in lookup
/// @param lookup A lookup
/// @return Max length of all buckets in lookup
int getMaxBucketLength(FrequencyLookup *lookup);

/// @brief Disposes lookup and all of its entries
/// @param lookup Lookup to dispose
void disposeLookup(FrequencyLookup *lookup);

/// @brief Moves to next element in iterator
/// @param iterator An iterator
/// @return `true` if there are available element, `false` otherwise (end of lookup)
bool moveNext(LookupIterator *iterator);

/// @brief Gets current string and frequency in iterator
/// @param iterator An iterator
/// @param string Pointer to store string to
/// @param frequency Pointer to store frequency to
void getCurrent(LookupIterator *iterator, const char **string, int *frequency);

/// @brief Disposes iterator
/// @param iterator Iterator to dispose
void disposeIterator(LookupIterator *iterator);
