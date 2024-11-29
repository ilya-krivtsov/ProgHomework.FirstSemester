#pragma once

#include <stdbool.h>
#include <stdio.h>

/// @brief List of entries in format `name` - `phone number`
typedef struct EntryList EntryList;

typedef enum {
    SORT_BY_PHONE,
    SORT_BY_NAME
} SortChoice;

/// @brief Reads entries from `stream` to `list`
/// @param list Pointer to store `EntryList` to
/// @param stream Stream to read entries from
/// @return `true` if read successfully, `false` otherwise (allocation failed)
bool readToList(EntryList **list, FILE *stream);

/// @brief Sorts list
/// @param list List to sort
/// @param choice What sorting key to use (name or phone number)
void sortList(EntryList *list, SortChoice choice);

/// @brief Prints list to specified stream
/// @param list List to print
/// @param stream Stream to write to
void printList(EntryList *list, FILE *stream);

/// @brief Disposes list and all of its elements
/// @param list List to dispose
void disposeList(EntryList *list);
