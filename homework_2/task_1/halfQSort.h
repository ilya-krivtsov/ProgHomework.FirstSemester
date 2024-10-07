#pragma once

/// @brief Performs half-QSort: all elements on the left will be ledd than first element, 
/// and all elements on the right will be greater or equal to first element
/// @param array Array to perform half-QSort on
/// @param arrayLength Length of `array`
void halfQSort(int *array, int arrayLength);
