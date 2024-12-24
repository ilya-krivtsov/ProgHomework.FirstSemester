#pragma once

#include <stdbool.h>

void quickSort(int *array, int arrayLength);

/// array must be sorted before calling this function
bool containsElement(int *array, int arrayLength, int value);
