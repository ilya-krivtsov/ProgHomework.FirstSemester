#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "sortAndSearch.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

CTEST(binSearchTests, emptyArrayTest) {
    ASSERT_FALSE(containsElement(NULL, 0, 0));
}

CTEST(binSearchTests, oneElementArrayTest) {
#define size 1
    int array[size] = { 42 };
    ASSERT_TRUE(containsElement(array, size, 42));
    ASSERT_FALSE(containsElement(array, size, 21));
#undef size
}

CTEST(binSearchTests, sameElementsArrayTest) {
#define size 8
    int array[size] = { 42, 42, 42, 42, 42, 42, 42, 42 };

    ASSERT_TRUE(containsElement(array, size, 42));
    ASSERT_FALSE(containsElement(array, size, 21));
#undef size
}

CTEST(binSearchTests, constantArrayTest) {
#define size 10
    int array[size] = { 1, 2, 3, 7, 10, 13, 15, 16, 19, 20 };
    for (int i = 0; i < size; ++i) {
        ASSERT_TRUE(containsElement(array, size, array[i]));
    }
    ASSERT_FALSE(containsElement(array, size, 0));
    ASSERT_FALSE(containsElement(array, size, -1));
    ASSERT_FALSE(containsElement(array, size, -4));
    ASSERT_FALSE(containsElement(array, size, 40));
    ASSERT_FALSE(containsElement(array, size, 50));
    ASSERT_FALSE(containsElement(array, size, 70));
#undef size
}
