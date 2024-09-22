#pragma once

#define VALUE_MIN -4096
#define VALUE_MAX 4095
#define VALUES_COUNT (VALUE_MAX - VALUE_MIN)

void countingSort(int *array, int arrayLength);
void bubbleSort(int *array, int arrayLength);
