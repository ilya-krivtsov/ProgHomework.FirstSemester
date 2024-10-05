#pragma once

#include <stdbool.h>

typedef struct {
    char *number;
} PhoneNumber;

typedef struct {
    int phoneNumbersCount, phoneNumbersCapacity;
    char *personName;
    PhoneNumber *phoneNumbers;
} PersonEntry;

/// @brief Parses phone number from input string
/// @param input Input string to be parsed
/// @param phoneNumber Pointer to write result to (can't be `NULL`)
/// @return `true` if parsed successfully, `false` otherwise
bool tryParsePhoneNumber(const char *input, PhoneNumber *phoneNumber);

/// @brief Creates empty person entry
/// @param entry Pointer to write result to
/// @return `true` if successful, `false` otherwise (allocation failed)
bool tryCreateEntry(PersonEntry **entry, const char *personName);

/// @brief Adds phone number to person entry
/// @param entry Pointer to person entry
/// @param number Phone number to add
/// @return `true` if successful, `false` otherwise (allocation failed)
bool tryAddPhoneNumber(PersonEntry *entry, PhoneNumber number);

/// @brief Adds raw phone number to person entry
/// @param entry Pointer to person entry
/// @param number Raw phone number to add
/// @return `true` if successful, `false` otherwise (allocation failed)
bool tryAddRawPhoneNumber(PersonEntry *entry, const char *number);

/// @brief Disposes person entry and all of its phone numbers
/// @param entry Entry to dipose (can be `NULL`)
void disposeEntry(PersonEntry *entry);
