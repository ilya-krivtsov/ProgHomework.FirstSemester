#include "cyclicList.h"

#include <stdlib.h>

typedef struct ListElement {
    struct ListElement *left;
    struct ListElement *right;
    int value;
} ListElement;

bool addElementAfter(ListElement *element, ListElement **newElement, int value) {
    *newElement = malloc(sizeof(ListElement));
    if (*newElement == NULL) {
        return false;
    }

    if (element == NULL) {
        (*newElement)->left = *newElement;
        (*newElement)->right = *newElement;
    } else {
        (*newElement)->left = element;
        (*newElement)->right = element->right;
        element->right = *newElement;
    }

    (*newElement)->value = value;

    return true;
}

ListElement *getNext(ListElement *element) {
    return element->right;
}

int getValue(ListElement *element) {
    return element->value;
}

void removeElement(ListElement *element) {
    element->left->right = element->right;
    element->right->left = element->left;
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
