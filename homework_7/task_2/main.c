#include <stdio.h>
#include <string.h>

#include "intStringDictionary.h"

void addEntryCommand(IntStringDictionary *dictionary) {
    printf("Enter key to add: ");
    int key = 0;
    if (scanf("%d", &key) != 1) {
        printf("Error: not a number\n");
        return;
    }

    printf("Enter value to add: ");
    char buffer[256] = { 0 };
    if (scanf("%255s", buffer) != 1) {
        printf("Error: not a string\n");
        return;
    }

    char *newString = strdup(buffer);

    if (newString == NULL || !addToDictionary(dictionary, key, newString)) {
        printf("Error: cannot add new entry\n");
    }
}

void getValueCommand(IntStringDictionary *dictionary) {
    printf("Enter a key of value to retrieve: ");
    int key = 0;
    if (scanf("%d", &key) != 1) {
        printf("Error: not a number\n");
        return;
    }

    char *value = getValue(dictionary, key);
    if (value == NULL) {
        printf("Value with key '%d' does not exist in dictionary\n", key);
    } else {
        printf("Found value with key '%d': \"%s\"\n", key, value);
    }
}

void checkIfExistsCommand(IntStringDictionary *dictionary) {
    printf("Enter a key of value to check: ");
    int key = 0;
    if (scanf("%d", &key) != 1) {
        printf("Error: not a number\n");
        return;
    }

    printf("Key '%d' %s in dictionary\n", key, containsKey(dictionary, key) ? "exists" : "does not exist");
}

void removeEntryCommand(IntStringDictionary *dictionary) {
    printf("Enter a key of value to remove: ");
    int key = 0;
    if (scanf("%d", &key) != 1) {
        printf("Error: not a number\n");
        return;
    }

    if (!removeFromDictionary(dictionary, key)) {
        printf("Error: cannot remove value; it is not stored in dictionary\n");
    }
}

int readCommand(void) {
    int command = -1;
    if (scanf("%d", &command) != 1) {
        command = -1;
    }
    while (getchar() != '\n') {}
    switch (command) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return command;
    default:
        printf("Error: unknown command\n");
        return -1;
    }
}

bool doConversation(IntStringDictionary *dictionary) {
    printf("Dictionary\n");
    printf("Available commands: \n");
    printf("  0 - exit;\n");
    printf("  1 - add new entry (key and value);\n");
    printf("  2 - get value by key;\n");
    printf("  3 - check if key exists in dictionary;\n");
    printf("  4 - remove entry by key;\n");

    while (true) {
        printf("dictionary> ");
        int command = readCommand();
        switch (command)
        {
        case -1:
            break;

        case 0:
            return true;

        case 1:
            addEntryCommand(dictionary);
            break;

        case 2:
            getValueCommand(dictionary);
            break;

        case 3:
            checkIfExistsCommand(dictionary);
            break;

        case 4:
            removeEntryCommand(dictionary);
            break;

        default:
            printf("Error: unknown state\n");
            return false;
        }
    }
}

int main(void) {
    IntStringDictionary *dictionary = NULL;
    if (!createDictionary(&dictionary)) {
        printf("Error: allocation failed\n");
        return 1;
    }

    if (!doConversation(dictionary)) {
        disposeDictionary(dictionary);
        return 1;
    }
    disposeDictionary(dictionary);
}
