#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "intStringDictionary.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

IntStringDictionary *createDict(void) {
    IntStringDictionary *dictionary = NULL;
    ASSERT_TRUE(createDictionary(&dictionary));
    return dictionary;
}

void addToDict(IntStringDictionary *dict, int key, const char *value) {
    ASSERT_TRUE(addToDictionary(dict, key, value));
}

CTEST(dictonaryTests, emptyTest) {
    IntStringDictionary *dict = createDict();
    disposeDictionary(dict);
}

CTEST(dictonaryTests, singleEntryTest) {
    IntStringDictionary *dict = createDict();

    const int key = 0;
    const char *value = "string_0";
    addToDict(dict, key, value);
    ASSERT_TRUE(containsKey(dict, key));

    ASSERT_STR(getValue(dict, key), value);

    ASSERT_TRUE(removeFromDictionary(dict, key));
    ASSERT_FALSE(removeFromDictionary(dict, key));
    ASSERT_FALSE(containsKey(dict, key));
    ASSERT_NULL(getValue(dict, key));

    disposeDictionary(dict);
}

void assertAddingAndRemoving(int keys[], const char *values[], int size) {
    IntStringDictionary *dict = createDict();

    for (int i = 0; i < size; ++i) {
        addToDict(dict, keys[i], values[i]);
        ASSERT_TRUE(containsKey(dict, keys[i]));
        ASSERT_STR(getValue(dict, keys[i]), values[i]);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_TRUE(containsKey(dict, keys[i]));
        ASSERT_STR(getValue(dict, keys[i]), values[i]);
    }

    for (int i = 0; i < size; ++i) {
        // offset index so values will be removed a bit randomly
        int index = (i + (size * 2 / 3)) % size;

        ASSERT_TRUE(removeFromDictionary(dict, keys[index]));
        ASSERT_FALSE(removeFromDictionary(dict, keys[index]));
        ASSERT_FALSE(containsKey(dict, keys[index]));
        ASSERT_NULL(getValue(dict, keys[index]));
    }

    disposeDictionary(dict);
}

CTEST(dictonaryTests, binaryEntriesTest) {
    int keys[15] = { 32, 16, 48, 8, 24, 40, 56, 4, 12, 20, 28, 36, 44, 52, 60 };
    const char *values[15] = { "32", "16", "48", "8", "24", "40", "56", "4", "12", "20", "28", "36", "44", "52", "60" };
    assertAddingAndRemoving(keys, values, 15);
}

CTEST_SKIP(dictonaryTests, randomEntriesTest) {
#define size 16384
    int keys[size] = { 0 };
    const char *values[size] = { 0 };

    srand(453563458);

    const char *string = "random_string";

    const int minValue = -14274;
    const int maxValue = 17343;
    for (int i = 0; i < size; ++i) {
        while (true) {
            int value = rand() * (maxValue - minValue) / RAND_MAX + minValue;
            bool contains = false;
            for (int j = 0; j < i; ++j) {
                if (keys[j] == value) {
                    contains = true;
                    break;
                }
            }
            if (!contains) {
                keys[i] = value;
                break;
            }
        }

        values[i] = string;
    }

    assertAddingAndRemoving(keys, values, size);
#undef size
}
