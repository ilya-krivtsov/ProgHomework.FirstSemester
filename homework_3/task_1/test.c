#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "frequencySearch.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

CTEST(frequencySearchTests, emptyArrayTest) {
    ASSERT_FALSE(findMostFrequentElement(NULL, 0, NULL, NULL));
}

CTEST(frequencySearchTests, oneElementArrayTest) {
#define size 1
    int array[size] = { 42 };
    int mostFrequentExpected = 42;
    int mostFrequentResult = 0;
    ASSERT_TRUE(findMostFrequentElement(array, size, &mostFrequentResult, NULL));
    ASSERT_EQUAL(mostFrequentResult, mostFrequentExpected);
#undef size
}

CTEST(frequencySearchTests, sameElementsArrayTest) {
#define size 8
    int array[size] = { 42, 42, 42, 42, 42, 42, 42, 42 };
    int mostFrequentExpected = 42, occurrencesExpected = size;
    int mostFrequentResult = 0, occurrencesResult = 0;
    ASSERT_TRUE(findMostFrequentElement(array, size, &mostFrequentResult, &occurrencesResult));
    ASSERT_EQUAL(mostFrequentResult, mostFrequentExpected);
    ASSERT_EQUAL(occurrencesResult, occurrencesExpected);
#undef size
}

CTEST(frequencySearchTests, constantArrayTest) {
#define size 10
    int array[size] = { 1, 2, 3, 3, 3, 7, 9, 12, 8, 3 };
    int mostFrequentExpected = 3, occurrencesExpected = 4;
    int mostFrequentResult = 0, occurrencesResult = 0;
    ASSERT_TRUE(findMostFrequentElement(array, size, &mostFrequentResult, &occurrencesResult));
    ASSERT_EQUAL(mostFrequentResult, mostFrequentExpected);
    ASSERT_EQUAL(occurrencesResult, occurrencesExpected);
#undef size
}
