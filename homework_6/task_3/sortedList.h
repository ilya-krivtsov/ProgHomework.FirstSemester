#pragma once

#include <stdbool.h>

/// @brief Element of the sorted list
typedef struct Element Element;

/// @brief List of numbers that remains always sorted
typedef struct SortedList SortedList;

/// @brief Creates new instance of `SortedList`
/// @param list Pointer to store list to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createList(SortedList **list);

/// @brief Adds value to list
/// @param list List to add value to
/// @param value Value to add
/// @return `true` if added successfully, `false` otherwise (allocation failed)
bool addElement(SortedList *list, int value);

/// @brief Removes value from list
/// @param list List to remove value from
/// @param value Value to remove
/// @return `true` if removed successfully, `false` otherwise (element doesn't exist in list)
bool removeElement(SortedList *list, int value);

/// @brief Gets first element in list
/// @param list List to get first element from
/// @return First element in list
Element *getFirst(SortedList *list);

/// @brief Disposes list and all of its elements
/// @param list List to dispose
void disposeList(SortedList *list);

/// @brief Gets element that follows specified element
/// @param element An element
/// @return Element that follows specified element
Element *getNext(Element *element);

/// @brief Gets value of specified element
/// @param element An element
/// @return Value of an element
int getValue(Element *element);
