#include <stdbool.h>
#include <stdio.h>

#include "cyclicList.h"

bool getLastWarrior(int warriorsCount, int killersPerWarrior, int *result) {
    ListElement *lastElement = NULL;
    for (int i = 0; i < warriorsCount; ++i) {
        ListElement *newElement = NULL;
        if (!addElementAfter(lastElement, &newElement, i + 1)) {
            return false;
        }

        lastElement = newElement;
    }

    // set lastElement to point to element
    lastElement = getNext(lastElement);

    while (getNext(lastElement) != lastElement) {
        for (int i = 0; i < killersPerWarrior; ++i) {
            lastElement = getNext(lastElement);
        }
        ListElement *next = getNext(lastElement);
        removeElement(lastElement);
        lastElement = next;
    }

    *result = getValue(lastElement);
    removeAllElements(lastElement);

    return true;
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1) || value <= 0) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
    return value;
}

int main(void) {
    int warriorsCount = readValue("warriors count: ", "incorrect value; warriors count should be greater than zero; try again: ");
    int nthWarrior = readValue("n-th warrior to be killed: ", "incorrect value; n should be greater than zero; try again: ");

    int result = 0;
    if (!getLastWarrior(warriorsCount, nthWarrior - 1, &result)) {
        printf("allocation error\n");
        return 1;
    }

    printf("last warrior: %d\n", result);
}
