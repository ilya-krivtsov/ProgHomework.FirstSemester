#pragma once

#include <stdbool.h>

/// @brief Calculator that works with basic operations like
/// addition, subtraction, multiplication and division
/// using integer numbers.
///
/// Recieves expression character by character in
/// postfix notation(also known as Reverse Polish notation(PRN))
typedef struct PostfixCalc PostfixCalc;

typedef enum {
    CALC_CONSUME_OK,
    CALC_CONSUME_NOT_ENOUGH_OPERANDS,
    CALC_CONSUME_ALLOCATION_ERROR,
    CALC_CONSUME_UNKNOWN_INPUT
} CalcConsumeResult;

typedef enum {
    CALC_GET_RESULT_OK,
    CALC_IS_EMPTY_BEFORE_READ,
    CALC_NOT_EMPTY_AFTER_READ
} CalcGetResultResult;

/// @brief Creates `PostfixCalc`
/// @param calc Pointer to store created `PostfixCalc` to
/// @return `true` if successful, `false` otherwise (allocation failed)
bool calcCreate(PostfixCalc **calc);

/// @brief Tries to read input to calculator
/// @param calc Pointer to `PostfixCalc` instance
/// @param input Input to read
/// @return `CALC_CONSUME_OK` if read successfully
///
/// `CALC_CONSUME_NOT_ENOUGH_OPERANDS` if there were not enough operands provided before specified operator
///
/// `CALC_CONSUME_UNKNOWN_INPUT` if unknown character was provided
///
/// `CALC_CONSUME_ALLOCATION_ERROR` if allocation error ocurred internally
CalcConsumeResult calcConsumeInput(PostfixCalc *calc, char input);

/// @brief Tries to get last result
/// @param calc Pointer to `PostfixCalc` instance
/// @param result Pointer to write evaluation result to
/// @return `CALC_GET_RESULT_OK` if evaluated successfully
///
/// `CALC_IS_EMPTY_BEFORE_READ` if there wasn't any result to return
///
/// `CALC_NOT_EMPTY_AFTER_READ` if there are more than one result
CalcGetResultResult calcTryGetResult(PostfixCalc *calc, int *result);

/// @brief Disposes calculator
/// @param calc `PostfixCalc` to dispose
void calcDispose(PostfixCalc *calc);
