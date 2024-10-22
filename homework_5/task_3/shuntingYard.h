#pragma once

/// @brief Structure for converting infix notation to postfix (also known as Reverse Polish notation (PRN))
typedef struct ShuntingYard ShuntingYard;

typedef enum {
    YARD_OK,
    YARD_UNKNOWN_INPUT,
    YARD_INCORRECT_INPUT,
    YARD_BUFFER_OVERFLOW,
    YARD_ALLOCATION_ERROR
} YardConsumeResult;

/// @brief Creates `ShuntingYard`
/// @param yard Pointer to store created `ShuntingYard` to
/// @return `true` if successful, `false` otherwise (allocation failed)
bool shuntingYardCreate(ShuntingYard **yard);

/// @brief Tries to read input to shunting yard
/// @param yard Pointer to `ShuntingYard` instance
/// @param input Input to read (use `'\0'` flush remaining characters to buffer)
/// @param outputBuffer Buffer to write to
/// @param bufferLength Length of buffer; used to prevent buffer overflow
/// @param bufferPosition Position in buffer to write character into
/// @return `YARD_OK` if read successfully
///
/// `YARD_UNKNOWN_INPUT` if unknown character was provided
///
/// `YARD_INCORRECT_INPUT` if previously characters were provided in incorrect format,
/// probably an opening parenthesis was missed
///
/// `YARD_BUFFER_OVERFLOW` if `bufferPosition` exceeded `bufferLength`
///
/// `YARD_ALLOCATION_ERROR` if allocation error ocurred internally
YardConsumeResult shuntingYardConsumeInput(ShuntingYard *yard, char input, char *outputBuffer, int bufferLength, int *bufferPosition);

/// @brief Disposes shunting yard
/// @param yard `ShuntingYard` to dispose
void shuntingYardDispose(ShuntingYard *yard);
