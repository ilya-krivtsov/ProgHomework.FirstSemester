#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>
#include <string.h>

#include "stringDictionary.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

StringDictionary *createDict(void) {
    StringDictionary *dictionary = NULL;
    ASSERT_TRUE(createDictionary(&dictionary));
    return dictionary;
}

void addToDict(StringDictionary *dict, const char *key, const char *value) {
    ASSERT_TRUE(addToDictionary(dict, key, value));
}

CTEST(dictonaryTests, emptyTest) {
    StringDictionary *dict = createDict();
    disposeDictionary(dict);
}

CTEST(dictonaryTests, singleEntryTest) {
    StringDictionary *dict = createDict();

    const char *key = "key_0";
    const char *value = "value_0";
    addToDict(dict, key, value);
    ASSERT_TRUE(containsKey(dict, key));

    ASSERT_STR(getValue(dict, key), value);

    ASSERT_TRUE(removeFromDictionary(dict, key));
    ASSERT_FALSE(removeFromDictionary(dict, key));
    ASSERT_FALSE(containsKey(dict, key));
    ASSERT_NULL(getValue(dict, key));

    disposeDictionary(dict);
}

void assertAddingAndRemoving(const char **keys, const char **values, int size) {
    StringDictionary *dict = createDict();

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
        int index = (i + (size / 3)) % size;
        ASSERT_TRUE(removeFromDictionary(dict, keys[index]));
        ASSERT_FALSE(removeFromDictionary(dict, keys[index]));
        ASSERT_FALSE(containsKey(dict, keys[index]));
        ASSERT_NULL(getValue(dict, keys[index]));
    }

    disposeDictionary(dict);
}

CTEST(dictonaryTests, binaryEntriesTest) {
    const char *keys[15] = {
        "key_32", "key_16", "key_48", "key_8", "key_24", "key_40", "key_56", "key_4",
        "key_12", "key_20", "key_28", "key_36", "key_44", "key_52", "key_60"
    };

    const char *values[15] = {
        "value_32", "value_16", "value_48", "value_8", "value_24", "value_40", "value_56", "value_4",
        "value_12", "value_20", "value_28", "value_36", "value_44", "value_52", "value_60"
    };

    assertAddingAndRemoving(keys, values, 15);
}

CTEST(dictonaryTests, randomEntriesTest) {
#define size 16384
    char *keys[size] = { 0 };
    char *values[size] = { 0 };

    const char *keyTemplate = "key_000000";
    const char *valueTemplate = "value_000000";
    const int keyOffset = strlen("key_");
    const int valueOffset = strlen("value_");
    const int digitsCount = strlen(keyTemplate) - keyOffset;

    for (int i = 0; i < size; ++i) {
        char *key = strdup(keyTemplate);
        char *value = strdup(valueTemplate);

        ASSERT_NOT_NULL(key);
        ASSERT_NOT_NULL(value);

        keys[i] = key;
        values[i] = value;

        int number = i;
        for (int j = digitsCount - 1; j >= 0; --j) {
            char digit = (number % 10) + '0';
            key[keyOffset + j] = digit;
            value[valueOffset + j] = digit;
            number /= 10;
        }
    }

    srand(453563458);

    for (int i = 0; i < size; ++i) {
        int index = (rand() % (size - i)) + i;

        char *key = keys[i];
        keys[i] = keys[index];
        keys[index] = key;

        char *value = values[i];
        values[i] = values[index];
        values[index] = value;
    }

    assertAddingAndRemoving((const char **)keys, (const char **)values, size);

    for (int i = 0; i < size; ++i) {
        free(keys[i]);
        free(values[i]);
    }
#undef size
}
