#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "entryList.h"

#define TEST_FILES "testFiles/"
#define IN "_in.txt"
#define OUT "_out.txt"

#define BY_NAME_OUT "_out_byName.txt"
#define BY_PHONE_OUT "_out_byPhone.txt"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

EntryList *readList(const char *filename) {
    FILE *file = fopen(filename, "r");
    ASSERT_NOT_NULL(file);

    EntryList *list = NULL;
    ASSERT_TRUE(readToList(&list, file));

    ASSERT_EQUAL(fclose(file), 0);
    return list;
}

void assertTwoFiles(const char *input, const char *expectedOutput, SortChoice choice) {
    EntryList *list = readList(input);

    sortList(list, choice);

    const char *outputName = TEST_FILES "output.txt";
    FILE *outputFile = fopen(outputName, "w+");
    ASSERT_NOT_NULL(outputFile);

    printList(list, outputFile);
    ASSERT_EQUAL(fclose(outputFile), 0);

    FILE *expectedOutputFile = fopen(expectedOutput, "r");
    ASSERT_NOT_NULL(expectedOutputFile);
    FILE *realOutputFile = fopen(outputName, "r");
    ASSERT_NOT_NULL(outputFile);

    while (!feof(expectedOutputFile) && !feof(realOutputFile)) {
        char expected = fgetc(expectedOutputFile);
        char real = fgetc(realOutputFile);
        ASSERT_EQUAL(expected, real);
    }

    ASSERT_EQUAL(fclose(expectedOutputFile), 0);
    ASSERT_EQUAL(fclose(realOutputFile), 0);

    disposeList(list);
}

CTEST(entryListTests, emptyListTest) {
    assertTwoFiles(TEST_FILES "empty" IN, TEST_FILES "empty" OUT, SORT_BY_NAME);
}

CTEST(entryListTests, oneEntryTest) {
    assertTwoFiles(TEST_FILES "oneEntry" IN, TEST_FILES "oneEntry" OUT, SORT_BY_NAME);
}

CTEST(entryListTests, twoEntriesTest) {
    assertTwoFiles(TEST_FILES "twoEntries" IN, TEST_FILES "twoEntries" BY_NAME_OUT, SORT_BY_NAME);
    assertTwoFiles(TEST_FILES "twoEntries" IN, TEST_FILES "twoEntries" BY_PHONE_OUT, SORT_BY_PHONE);
}

CTEST(entryListTests, someEntriesTest) {
    assertTwoFiles(TEST_FILES "someEntries" IN, TEST_FILES "someEntries" BY_NAME_OUT, SORT_BY_NAME);
    assertTwoFiles(TEST_FILES "someEntries" IN, TEST_FILES "someEntries" BY_PHONE_OUT, SORT_BY_PHONE);
}
