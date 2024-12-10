#include "frequencyList.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct FrequencyElement {
    char *string;
    int frequency;
    FrequencyElement *next;
} FrequencyElement;

typedef struct FrequencyList {
    FrequencyElement *first;
    FrequencyElement *last;
    int length;
} FrequencyList;

bool createFrequencyList(FrequencyList **list) {
    *list = malloc(sizeof(FrequencyList));

    if (*list == NULL) {
        return false;
    }

    (*list)->first = NULL;
    (*list)->last = NULL;
    (*list)->length = 0;

    return true;
}

FrequencyElement *getFirstElement(FrequencyList *list) {
    return list->first;
}

FrequencyElement *addNewElement(FrequencyList *list) {
    FrequencyElement *element = malloc(sizeof(FrequencyElement));
    if (element == NULL) {
        return NULL;
    }

    element->string = NULL;
    element->frequency = 0;

    element->next = NULL;
    if (list->first == NULL) {
        list->first = element;
        list->last = element;
        list->length = 1;
        return element;
    }

    list->last->next = element;
    list->last = element;

    ++list->length;

    return element;
}

int getLength(FrequencyList *list) {
    return list->length;
}

void disposeList(FrequencyList *list) {
    FrequencyElement *element = list->first;
    while (element != NULL) {
        FrequencyElement *next = element->next;
        free(element->string);
        free(element);
        element = next;
    }

    free(list);
}

FrequencyElement *getNextElement(FrequencyElement *element) {
    return element->next;
}

const char *getString(FrequencyElement *element) {
    return element->string;
}

int getFrequency(FrequencyElement *element) {
    return element->frequency;
}

bool setString(FrequencyElement *element, const char *string) {
    char *newString = strdup(string);
    if (newString == NULL) {
        return false;
    }
    free(element->string);
    element->string = newString;
    return true;
}

void setFrequency(FrequencyElement *element, int frequency) {
    element->frequency = frequency;
}
