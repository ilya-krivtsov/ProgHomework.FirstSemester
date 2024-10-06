#include "personEntry.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool tryParsePhoneNumber(const char *input, PhoneNumber *phoneNumber) {
    if (input == NULL) {
        return false;
    }
    if (phoneNumber == NULL) {
        return false;
    }

    char buffer[1024] = { 0 };

    bool hasOpenParen = false, hyphen = false;

    for (int i = 0, j = 0; i < sizeof(buffer) - 1; ++i) {
        char c = input[i];
        if (c == '\0') {
            break;
        }

        if (c == '-') {
            // no two consecutive hyphens
            if (hyphen) {
                return false;
            }
            hyphen = true;
            continue;
        } else {
            hyphen = false;
        }

        if (c == '(') {
            if (hasOpenParen) {
                return false;
            }
            hasOpenParen = true;
            continue;
        }

        if (c == ')') {
            hasOpenParen = false;
            continue;
        }

        if ((c >= '0' && c <= '9') || c == '+') {
            buffer[j] = c;
            ++j;
            continue;
        }

        // all other allowed character(s)
        if (c == ' ') {
            continue;;
        }

        // fallback
        return false;
    }

    if (hyphen || hasOpenParen) {
        return false;
    }

    char *result = strdup(buffer);

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
