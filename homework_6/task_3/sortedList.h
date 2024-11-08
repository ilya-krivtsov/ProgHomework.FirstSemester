#pragma once

#include <stdbool.h>

typedef struct Element Element;

typedef struct SortedList SortedList;

bool createList(SortedList **list);

bool addElement(SortedList *list, int value);

bool removeElement(SortedList *list, int value);

Element *getFirst(SortedList *list);

void disposeList(SortedList *list);

Element *getNext(Element *element);

int getValue(Element *element);
