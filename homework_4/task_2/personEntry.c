#include "personEntry.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool tryParsePhoneNumber(const char *input, PhoneNumber *phoneNumber) {
    if (phoneNumber == NULL) {
        return false;
    }

    // TODO: actual parsing
    char *result = strdup(input);

    if (result == NULL) {
        return false;
    }

    phoneNumber->number = result;

    return true;
}

bool tryCreateEntry(PersonEntry **personEntry, const char *personName) {
    PersonEntry *entry = malloc(sizeof(PersonEntry));

    entry->phoneNumbersCount = 0;
    entry->phoneNumbersCapacity = 4;
    entry->phoneNumbers = malloc(entry->phoneNumbersCapacity * sizeof(PhoneNumber *));
    if (entry->phoneNumbers == NULL) {
        *personEntry = NULL;
        return false;
    }

    char *name = strdup(personName);
    if (name == NULL) {
        *personEntry = NULL;
        return false;
    }
    entry->personName = name;

    *personEntry = entry;

    return true;
}

bool tryAddPhoneNumber(PersonEntry *entry, PhoneNumber number) {
    if (entry->phoneNumbersCount == entry->phoneNumbersCapacity) {
        entry->phoneNumbersCapacity *= 2;
        PhoneNumber *numbers = realloc(entry->phoneNumbers, entry->phoneNumbersCapacity * sizeof(PhoneNumber *));
        if (numbers == NULL) {
            return false;
        }
        entry->phoneNumbers = numbers;
    }
    entry->phoneNumbers[entry->phoneNumbersCount] = number;
    ++entry->phoneNumbersCount;
    return true;
}

bool tryAddRawPhoneNumber(PersonEntry *entry, const char *number) {
    PhoneNumber phoneNumber;
    if (!tryParsePhoneNumber(number, &phoneNumber)) {
        return false;
    }
    if (!tryAddPhoneNumber(entry, phoneNumber)) {
        return false;
    }
    return true;
}

void disposeEntry(PersonEntry *entry) {
    if (entry == NULL) {
        return;
    }

    for (int i = 0; i < entry->phoneNumbersCount; ++i) {
        free(entry->phoneNumbers[i].number);
    }
    free(entry->phoneNumbers);
    free(entry);
}
