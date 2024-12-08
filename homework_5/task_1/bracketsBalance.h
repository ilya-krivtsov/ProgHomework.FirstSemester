#pragma once

typedef enum {
    BALANCED,
    UNBALANCED,
    ALLOCATION_FAILED
} BalanceResult;

/// @brief Checks if brackets are balanced in given string, all other characters are ignored
/// @param string String to be checked
/// @return `BALANCED` if brackets are balanced, `UNBALANCED` otherwise,
/// `ALLOCATION_FAILED` if allocation failed
BalanceResult checkIfBracketsBalanced(const char *string);
