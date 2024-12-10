#pragma once

#include <stdbool.h>

/// @brief Dictionary of `int` keys associated with `char *` values
typedef struct IntStringDictionary IntStringDictionary;

/// @brief Creates new dictionary
/// @param dictionary Pointer to write new dictionary to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createDictionary(IntStringDictionary **dictionary);

/// @brief Adds key and associated with it value to dictionary
/// @param dictionary Dictionary to add key and value to
/// @param key Key to add
/// @param value Value to add
/// @return `true` if added successfully, `false` otherwise (allocation failed)
bool addToDictionary(IntStringDictionary *dictionary, int key, const char *value);

/// @brief Gets value corresponding to given key
/// @param dictionary Dictionary to get value from
/// @param key Key associated with value
/// @return String associated with key, or `NULL` if value was not found
char *getValue(IntStringDictionary *dictionary, int key);

/// @brief Checks if dictionary contains given key
/// @param dictionary Dictionary to check
/// @param key Key to check
/// @return `true` if key exists in dictionary, `false` otherwise
bool containsKey(IntStringDictionary *dictionary, int key);

/// @brief Removes value from dictionary using given key
/// @param dictionary Dictionary to remove value from
/// @param key Key associated with value to be removed
/// @return `true` if removed successfully, `false` otherwise (key does not exist in dictionary)
bool removeFromDictionary(IntStringDictionary *dictionary, int key);

/// @brief Disposes dictionary and all of its entries
/// @param dictionary Dictionary to dispose
void disposeDictionary(IntStringDictionary *dictionary);
