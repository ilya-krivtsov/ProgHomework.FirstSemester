#include <stdbool.h>
#include <stdio.h>

#include "stringDictionary.h"

void addEntryCommand(StringDictionary *dictionary) {
    printf("Enter key to add: ");
    char key[256] = { 0 };
    if (scanf("%255s", key) != 1) {
        printf("Error: not a string\n");
        return;
    }

    printf("Enter value to add: ");
    char value[256] = { 0 };
    if (scanf("%255s", value) != 1) {
        printf("Error: not a string\n");
        return;
    }

    if (!addToDictionary(dictionary, key, value)) {
        printf("Error: cannot add new entry\n");
    }
}

void getValueCommand(StringDictionary *dictionary) {
    printf("Enter a key of value to retrieve: ");
    char key[256] = { 0 };
    if (scanf("%255s", key) != 1) {
        printf("Error: not a string\n");
        return;
    }

    const char *value = getValue(dictionary, key);
    if (value == NULL) {
        printf("Value with key '%s' does not exist in dictionary\n", key);
    } else {
        printf("Found value with key '%s': \"%s\"\n", key, value);
    }
}

void checkIfExistsCommand(StringDictionary *dictionary) {
    printf("Enter a key of value to check: ");
    char key[256] = { 0 };
    if (scanf("%255s", key) != 1) {
        printf("Error: not a string\n");
        return;
    }

    printf("Key '%s' %s in dictionary\n", key, containsKey(dictionary, key) ? "exists" : "does not exist");
}

void removeEntryCommand(StringDictionary *dictionary) {
    printf("Enter a key of value to remove: ");
    char key[256] = { 0 };
    if (scanf("%255s", key) != 1) {
        printf("Error: not a string\n");
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

bool doConversation(StringDictionary *dictionary) {
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
    StringDictionary *dictionary = NULL;
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
