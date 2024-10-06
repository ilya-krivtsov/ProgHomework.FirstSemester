#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "frequencySearch.h"
#include "arrayIO.h"

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

void loadFile(const char *path, int **array, int *arrayLength) {
    FILE *file = fopen(path, "r");
    ASSERT_NOT_NULL(file);
    ASSERT_TRUE(readFromStream(file, array, arrayLength));
    ASSERT_EQUAL(fclose(file), 0);
}

CTEST(arrayIOTests, emptyArrayTest) {
    int *array, arrayLength;
    loadFile("./testFiles/emptyArray", &array, &arrayLength);
    ASSERT_EQUAL(arrayLength, 0);
}

CTEST(arrayIOTests, singleElementTest) {
    int *array, arrayLength;
    loadFile("./testFiles/singleElement", &array, &arrayLength);
    ASSERT_EQUAL(arrayLength, 1);
    ASSERT_EQUAL(array[0], 8192);
}

CTEST(arrayIOTests, incrementalArrayTest) {
    int *array, arrayLength;
    loadFile("./testFiles/incrementalArray", &array, &arrayLength);
    ASSERT_EQUAL(arrayLength, 8);
    for (int i = 0; i < arrayLength; ++i) {
        ASSERT_EQUAL(i, array[i]);
    }
}
