#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "frequencyLookup.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

FrequencyLookup *createNewLookup(void) {
    FrequencyLookup *lookup = NULL;
    ASSERT_TRUE(createLookup(&lookup));
    return lookup;
}

CTEST(lookupTests, createTest) {
    FrequencyLookup *lookup = createNewLookup();
    disposeLookup(lookup);
}

CTEST(lookupTests, addSomeValues) {
#define size 10
    char *strings[size] = { "abc", "def", "ghi", "testString", "testString2", "qwertyuiop", "asdfghjkl", "zxcvbnm", "0123456789", "abcdefghijklmnopqrstuvwxyz" };
    int frequencies[size] = { 12, 542, 1, 4, 61, 234, 101, 456, 789, 42 };

    FrequencyLookup *lookup = createNewLookup();

    for (int i = 0; i < size; ++i) {
        ASSERT_TRUE(addFrequency(lookup, strings[i], frequencies[i]));

        int frequency = 0;
        ASSERT_TRUE(getFrequencyByString(lookup, strings[i], &frequency));
        ASSERT_EQUAL(frequency, frequencies[i]);
    }

    for (int i = 0; i < size; ++i) {
        int frequency = 0;
        ASSERT_TRUE(getFrequencyByString(lookup, strings[i], &frequency));

        int newFrequency = frequency * 11;
        ASSERT_TRUE(addFrequency(lookup, strings[i], newFrequency));

        ASSERT_TRUE(getFrequencyByString(lookup, strings[i], &frequency));
        ASSERT_EQUAL(frequency, newFrequency);
    }

    disposeLookup(lookup);
#undef size
}
