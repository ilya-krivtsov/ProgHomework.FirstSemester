#pragma once

#include <stdbool.h>

typedef char* PhoneNumber;

typedef struct {
    char *personName;
    PhoneNumber phoneNumber;
} PersonEntry;

/// @brief Parses phone number from input string
/// @param input Input string to be parsed
/// @param phoneNumber Pointer to write result to
/// @return `true` if parsed successfully, `false` otherwise
bool tryParsePhoneNumber(const char *input, PhoneNumber *phoneNumber);

/// @brief Disposes person entry and all of its phone numbers
/// @param entry Entry to dipose (can be `NULL`)
void disposeEntry(PersonEntry *entry);
