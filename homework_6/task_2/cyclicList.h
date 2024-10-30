#pragma once

/// @brief Cyclic list element
typedef struct ListElement ListElement;

/// @brief Adds new element after specified element
/// @param element Element that will be on the left relative to new element,
/// must be `NULL` when creating new list
/// @param newElement Pointer to store created `ListElement` to
/// @param value Value to store in new element
/// @return `true` if added successfully, `false` otherwise (allocaton failed)
bool addElementAfter(ListElement *element, ListElement **newElement, int value);

/// @brief Gets element on the right of the specified element
/// @param element Element of cyclic list
/// @return Element on the right of the specified element
ListElement *getNext(ListElement *element);

/// @brief Gets value of the specified element
/// @param element Element of cyclic list
/// @return Value of specified element
int getValue(ListElement *element);

/// @brief Removes an element (and calls `free()` on it)
/// @param element Element to remove
void removeElement(ListElement *element);

/// @brief Removes all elements of cyclic list
/// @param element Any element of the list
void removeAllElements(ListElement *element);
