#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "stdio.h"
#include "sortings.h"

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}

void assertEqual(int *arrayA, int *arrayB, int size) {
    for (int i = 0; i < size; ++i) {
        ASSERT_EQUAL(arrayA[i], arrayB[i]);
    }
}

typedef void (*sort)(int *, int);

void testEmptyArray(sort sort) {
    sort(NULL, 0);
}

void testOneElementArray(sort sort) {
#define size 1
    int array[size] = { 2354 },
        expected[size] = { 2354 };
    sort(array, size);
    assertEqual(array, expected, size);
#undef size
}

void testEightElementsArray(sort sort) {
#define size 8
    int array[size] = { 2865, -3452, 123, 0, 2104, -1923, -242, 1532 },
        expected[size] = { -3452, -1923, -242, 0, 123, 1532, 2104, 2865 };
    sort(array, size);
    assertEqual(array, expected, size);
#undef size
}

void test20ElementsSameValuesArray(sort sort) {
#define size 20
    int array[size], expected[size];

    for (int i = 0; i < size; ++i) {
        array[i] = expected[i] = 1532;
    }

    sort(array, size);
    assertEqual(array, expected, size);
#undef size
}

void testEverything(sort sort) {
    testEmptyArray(sort);
    testOneElementArray(sort);
    testEightElementsArray(sort);
    test20ElementsSameValuesArray(sort);
}

CTEST(sortingTests, countingSortTest) {
    testEverything(countingSort);
}

CTEST(sortingTests, bubbleSortTest) {
    testEverything(bubbleSort);
}
