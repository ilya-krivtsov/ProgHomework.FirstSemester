#include <stdio.h>

#include "sortedList.h"

typedef enum {
    Exit,
    Menu,
    AddElement,
    RemoveElement,
    PrintList
} State;

State readCommand(void) {
    int command = -1;
    if (scanf("%d", &command) != 1) {
        command = -1;
    }
    while (getchar() != '\n') {}
    switch (command) {
    case 0:
        return Exit;
    case 1:
        return AddElement;
    case 2:
        return RemoveElement;
    case 3:
        return PrintList;
    default:
        printf("Error: unknown command\n");
        return Menu;
    }
}

State addElementCommand(SortedList *list) {
    printf("Enter a number to add: ");
    int value = 0;
    if (scanf("%d", &value) != 1) {
        printf("Error: not a number\n");
        return Menu;
    }

    if (!addElement(list, value)) {
        printf("Error: cannot add number\n");
        return Menu;
    }

    return Menu;
}

State removeElementCommand(SortedList *list) {
    printf("Enter a number to remove: ");
    int value = 0;
    if (scanf("%d", &value) != 1) {
        printf("Error: not a number\n");
        return Menu;
    }

    if (!removeElement(list, value)) {
        printf("Error: cannot remove number; probably, it isn't in the list\n");
        return Menu;
    }

    return Menu;
}

State printListCommand(SortedList *list) {
    printf("[ ");
    Element *element = getFirst(list);
    while (element != NULL) {
        printf("%d", getValue(element));

        element = getNext(element);
        if (element != NULL & getNext(element) != NULL) {
            printf(", ");
        }
    }
    printf(" ]\n");

    return Menu;
}

bool doConversation(SortedList *list) {
    printf("Sorted list\n");
    printf("Available commands: \n");
    printf("  0 - exit;\n");
    printf("  1 - add a number;\n");
    printf("  2 - remove a number;\n");
    printf("  3 - print list.\n");

    State state = Menu;
    while (true) {
        switch (state)
        {
        case Exit:
            return true;

        case Menu:
            printf("sorted_list> ");
            state = readCommand();
            break;

        case AddElement:
            state = addElementCommand(list);
            break;

        case RemoveElement:
            state = removeElementCommand(list);
            break;

        case PrintList:
            state = printListCommand(list);
            break;

        default:
            printf("Error: unknown state\n");
            return false;
        }
    }
}

int main(void) {
    SortedList *list = NULL;
    if (!createList(&list)) {
        printf("Error: allocation failed\n");
        return 1;
    }

    if (!doConversation(list)) {
        disposeList(list);
        return 1;
    }
    disposeList(list);
}
