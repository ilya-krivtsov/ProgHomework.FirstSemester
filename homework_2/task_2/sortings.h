#pragma once

#include <stdbool.h>

/// @brief Sorts array using counting algorithm
/// @param array Array to sort
/// @param arrayLength Length of `array`
/// @return `true` if sorted successfully, `false` otherwise (allocation failed)
bool countingSort(int *array, int arrayLength);

/// @brief Sorts array with bubble sort
/// @param array Array to sort
/// @param arrayLength Length of `array`
/// @return Always returns `true`
bool bubbleSort(int *array, int arrayLength);
