#pragma once

#include <stdbool.h>

typedef struct FrequencyElement FrequencyElement;

typedef struct FrequencyList FrequencyList;

bool createFrequencyList(FrequencyList **list);

FrequencyElement *getFirstElement(FrequencyList *list);

FrequencyElement *addNewElement(FrequencyList *list);

int getLength(FrequencyList *list);

void disposeList(FrequencyList *list);

FrequencyElement *getNextElement(FrequencyElement *element);

const char *getString(FrequencyElement *element);

int getFrequency(FrequencyElement *element);

void setString(FrequencyElement *element, const char *string);

void setFrequency(FrequencyElement *element, int frequency);
