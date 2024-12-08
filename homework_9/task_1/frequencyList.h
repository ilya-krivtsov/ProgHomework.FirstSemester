#pragma once

#include <stdbool.h>

/// @brief Element of a `FrequencyList` that contains string and frequency
typedef struct FrequencyElement FrequencyElement;

/// @brief List where every element contains string and frequency
typedef struct FrequencyList FrequencyList;

/// @brief Creates `FrequencyList`
/// @param list Pointer to store `FrequencyList` to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createFrequencyList(FrequencyList **list);

/// @brief Gets first element of a list
/// @param list List to get first element from
/// @return Fist element, may be `NULL` if list is empty
FrequencyElement *getFirstElement(FrequencyList *list);

/// @brief Creates new element, adds it to list, and returns it
/// @param list List to add new element to
/// @return Created element
FrequencyElement *addNewElement(FrequencyList *list);

/// @brief Gets length of a list
/// @param list List to get lenght of
/// @return Length of the given list
int getLength(FrequencyList *list);

/// @brief Disposes list and all of its element
/// @param list List to dispose
void disposeList(FrequencyList *list);

/// @brief Gets next element of given element
/// @param element Element to get next element of
/// @return Element that follows given element, may be `NULL`
FrequencyElement *getNextElement(FrequencyElement *element);

/// @brief Gets string stored in an element
/// @param element Element to get string from
/// @return String that is stored in an element
const char *getString(FrequencyElement *element);

/// @brief Gets frequency stored in an element
/// @param element Element to get frequency from
/// @return Frequency that is stored in an element
int getFrequency(FrequencyElement *element);

/// @brief Sets string into an element
/// @param element Element to set string into
/// @param string String to set
void setString(FrequencyElement *element, const char *string);

/// @brief Sets frequency into an element
/// @param element Element to set frequency into
/// @param frequency Frequency to set
void setFrequency(FrequencyElement *element, int frequency);
