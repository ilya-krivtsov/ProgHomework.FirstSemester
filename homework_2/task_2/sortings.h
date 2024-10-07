#pragma once

#define VALUE_MIN -4096
#define VALUE_MAX 4095
#define VALUES_COUNT (VALUE_MAX - VALUE_MIN)

/// @brief Sorts array using counting algorithm
/// @param array Array to sort
/// @param arrayLength Length of `array`
void countingSort(int *array, int arrayLength);

/// @brief Sorts array with bubble sort
/// @param array Array to sort
/// @param arrayLength Length of `array`
void bubbleSort(int *array, int arrayLength);
