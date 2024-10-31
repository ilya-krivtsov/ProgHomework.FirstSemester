#include "cyclicList.h"

#include <stdlib.h>

typedef struct ListElement {
    struct ListElement *left;
    struct ListElement *right;
    int value;
} ListElement;

bool addElementAfter(ListElement *previous, ListElement **newElement, int value) {
    ListElement *element = malloc(sizeof(ListElement));
    if (element == NULL) {
        return false;
    }

    if (previous == NULL) {
        element->left = element;
        element->right = element;
    } else {
        ListElement *next = previous->right;
        element->left = previous;
        element->right = next;

        next->left = element;
        previous->right = element;
    }

    element->value = value;
    *newElement = element;

    return true;
}

ListElement *getNext(ListElement *element) {
    return element->right;
}

int getValue(ListElement *element) {
    return element->value;
}

void removeElement(ListElement *element) {
    ListElement *left = element->left;
    ListElement *right = element->right;
    left->right = right;
    right->left = left;
    free(element);
}

void removeAllElements(ListElement *element) {
    ListElement *right = element->right;
    do {
        ListElement *next = right->right;
        removeElement(right);
        right = next;
    } while (right != element);
}
