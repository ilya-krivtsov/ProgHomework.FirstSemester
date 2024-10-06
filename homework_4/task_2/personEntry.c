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

    *phoneNumber = result;

    return true;
}

void disposeEntry(PersonEntry *entry) {
    if (entry == NULL) {
        return;
    }

    free(entry->personName);
    free(entry->phoneNumber);
}
