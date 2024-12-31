#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdbool.h>
#include <stdlib.h>

#include "sortings.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void assertEqual(int *arrayA, int *arrayB, int size) {
    for (int i = 0; i < size; ++i) {
        ASSERT_EQUAL(arrayA[i], arrayB[i]);
    }
}

typedef bool (*sort)(int *, int);

void testEmptyArray(sort sort) {
    ASSERT_TRUE(sort(NULL, 0));
}

void testOneElementArray(sort sort) {
#define size 1
    int array[size] = { 2354 };
    int expected[size] = { 2354 };
    ASSERT_TRUE(sort(array, size));
    assertEqual(array, expected, size);
#undef size
}

void testEightElementsArray(sort sort) {
#define size 8
    int array[size] = { 2865, -3452, 123, 0, 2104, -1923, -242, 1532 };
    int expected[size] = { -3452, -1923, -242, 0, 123, 1532, 2104, 2865 };
    ASSERT_TRUE(sort(array, size));
    assertEqual(array, expected, size);
#undef size
}

void test20ElementsSameValuesArray(sort sort) {
#define size 20
    int array[size];
    int expected[size];

    for (int i = 0; i < size; ++i) {
        array[i] = 1532;
        expected[i] = array[i];
    }

    ASSERT_TRUE(sort(array, size));
    assertEqual(array, expected, size);
#undef size
}

// ========================================

CTEST(countingSortTests, testEmptyArray) {
    testEmptyArray(countingSort);
}

CTEST(countingSortTests, testOneElementArray) {
    testOneElementArray(countingSort);
}

CTEST(countingSortTests, testEightElementsArray) {
    testEightElementsArray(countingSort);
}

CTEST(countingSortTests, test20ElementsSameValuesArray) {
    test20ElementsSameValuesArray(countingSort);
}

// ========================================

CTEST(bubbleSortTests, testEmptyArray) {
    testEmptyArray(bubbleSort);
}

CTEST(bubbleSortTests, testOneElementArray) {
    testOneElementArray(bubbleSort);
}

CTEST(bubbleSortTests, testEightElementsArray) {
    testEightElementsArray(bubbleSort);
}

CTEST(bubbleSortTests, test20ElementsSameValuesArray) {
    test20ElementsSameValuesArray(bubbleSort);
}
