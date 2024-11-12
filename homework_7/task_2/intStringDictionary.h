#pragma once

typedef struct IntStringDictionary IntStringDictionary;

bool createDictionary(IntStringDictionary **dictionary);

bool addToDictionary(IntStringDictionary *dictionary, int key, const char *value);

const char *getValue(IntStringDictionary *dictionary, int key);

bool containsKey(IntStringDictionary *dictionary, int key);

bool removeFromDictionary(IntStringDictionary *dictionary, int key);

void disposeDictionary(IntStringDictionary *dictionary);
