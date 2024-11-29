#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>
#include <stdlib.h>

#include "smartQSort.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void assertSorted(int *array, int arrayLength) {
    for (int i = 1; i < arrayLength; ++i) {
        ASSERT_GE(array[i], array[i - 1]);
    }
}

void sortAndAssert(int *array, int arrayLength) {
    smartQuickSort(array, arrayLength);

    for (int i = 1; i < arrayLength; ++i) {
        ASSERT_GE(array[i], array[i - 1]);
    }
}

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

CTEST(smartQSortTests, emptyArrayTest) {
    smartQuickSort(NULL, 0);
}

CTEST(smartQSortTests, oneElementArrayTest) {
#define size 1
    int array[size] = { 24 };
    sortAndAssert(array, size);
#undef size
}

CTEST(smartQSortTests, sameElementsArrayTest) {
#define size 8
    int array[size] = { 31, 31, 31, 31, 31, 31, 31, 31 };
    sortAndAssert(array, size);
#undef size
}

CTEST(smartQSortTests, constantArrayTest) {
#define size 10
    int array[size] = { 23, 12, 4, 35, 20, -15, 17, 8, 19, 40 };
    sortAndAssert(array, size);
#undef size
}

CTEST(smartQSortTests, randomArrayTest) {
#define size 100
    int array[size];

    randomizeArray(array, size, -128, 128);

    sortAndAssert(array, size);
#undef size
}
