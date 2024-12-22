#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>
#include <stdbool.h>

#include "halfQSort.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() * (maxValue - minValue) / RAND_MAX + minValue;
    }
}

void assertHalfSorted(int *array, int arrayLength, int firstElement) {
    bool reachedHalf = false;
    for (int i = 0; i < arrayLength; ++i) {
        int element = array[i];
        if (element >= firstElement) {
            reachedHalf = true;
        }
        if (reachedHalf) {
            ASSERT_GE(array[i], firstElement);
        } else {
            ASSERT_LT(array[i], firstElement);
        }
    }
}

void testArray(int *array, int arrayLength) {
    int firstElement = array[0];
    halfQSort(array, arrayLength);
    assertHalfSorted(array, arrayLength, firstElement);
}

CTEST(halfQSortTests, emptyArrayTest) {
    halfQSort(NULL, 0);
}

CTEST(halfQSortTests, constantArrayTest_FirstElementWillBeFirst) {
#define size 8
    int array[size] = { 4, 6, 7, 5, 8, 10, 9, 24 };

    testArray(array, size);
#undef size
}

CTEST(halfQSortTests, constantArrayTest_FirstElementWillBeLast) {
#define size 8
    int array[size] = { 44, 6, 7, 5, 8, 10, 9, 24 };

    testArray(array, size);
#undef size
}

CTEST(halfQSortTests, constantArrayTest_FirstElementWillBeInMiddle_A) {
#define size 8
    int array[size] = { 4, 6, 2, 5, -1, 10, 9, 0 };

    testArray(array, size);
#undef size
}

CTEST(halfQSortTests, constantArrayTest_FirstElementWillBeInMiddle_B) {
#define size 8
    int array[size] = { 4, 0, 23, 6, -3, 10, 2, 14 };

    testArray(array, size);
#undef size
}

CTEST(halfQSortTests, dynamicArrayTest_A) {
#define size 8
    int array[size] = { 0 };
    randomizeArray(array, size, -2048, 2048);
    testArray(array, size);
#undef size
}

CTEST(halfQSortTests, dynamicArrayTest_B) {
#define size 16
    int array[size] = { 0 };

    const int iterations = 8;
    for (int i = 0; i < iterations; ++i) {
        randomizeArray(array, size, -2048, 2048);
        testArray(array, size);
    }
#undef size
}

CTEST(halfQSortTests, dynamicArrayTest_C) {
#define size 64
    int array[size] = { 0 };

    const int iterations = 16;
    for (int i = 0; i < iterations; ++i) {
        randomizeArray(array, size, -2048, 2048);
        testArray(array, size);
    }
#undef size
}

CTEST(halfQSortTests, dynamicArrayTest_D) {
#define size 65536
    int array[size] = { 0 };

    const int iterations = 128;
    for (int i = 0; i < iterations; ++i) {
        randomizeArray(array, size, -2048, 2048);
        testArray(array, size);
    }
#undef size
}

