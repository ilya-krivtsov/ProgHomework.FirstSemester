#include "sortedList.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct Element {
    int value;
    struct Element *next;
} Element;

typedef struct SortedList {
    Element *first;
} SortedList;

bool createList(SortedList **list) {
    *list = malloc(sizeof(SortedList));
    if (*list == NULL) {
        return false;
    }

    (*list)->first = NULL;
    // (*list)->last = NULL;

    return true;
}

bool addElement(SortedList *list, int value) {
    Element *element = malloc(sizeof(Element));
    if (element == NULL) {
        return false;
    }

    element->value = value;
    element->next = NULL;

    if (list->first == NULL) {
        list->first = element;
        return true;
    }

    if (value < getValue(list->first)) {
        element->next = list->first;
        list->first = element;
        return true;
    }

    Element *last = list->first;
    while (last->next != NULL) {
        if (getValue(last->next) > value) {
            break;
        }

        last = last->next;
    }

    element->next = last->next;
    last->next = element;

    return true;
}

bool removeElement(SortedList *list, int value) {
    if (list->first == NULL) {
        return false;
    }

    if (value < getValue(list->first)) {
        return false;
    }

    if (value == getValue(list->first)) {
        Element *next = list->first->next;
        free(list->first);
        list->first = next;
        return true;
    }

    Element *last = list->first;
    while (last->next != NULL) {
        if (getValue(last->next) == value) {
            break;
        }

        last = last->next;
    }

    if (last->next == NULL) {
        return false;
    }

    Element *next = last->next->next;
    free(last->next);
    last->next = next;

    return true;
}

Element *getFirst(SortedList *list) {
    return list->first;
}

void disposeList(SortedList *list) {
    Element *last = list->first;
    while (last != NULL) {
        Element *next = last->next;
        free(last);
        last = next;
    }
    free(list);
}

Element *getNext(Element *element) {
    return element->next;
}

int getValue(Element *element) {
    return element->value;
}
