#include "shuntingYard.h"

#include <stdint.h>
#include <stdlib.h>

#include "../stack/stack.h"

typedef struct ShuntingYard {
    Stack *stack;
} ShuntingYard;

bool shuntingYardCreate(ShuntingYard **yard) {
    *yard = malloc(sizeof(ShuntingYard));
    if (*yard == NULL) {
        return false;
    }

    if (!stackCreate(&(*yard)->stack)) {
        return false;
    }

    return true;
}

static int getPrecedence(char operator) {
    switch (operator)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    default:
        return -1;
    }
}

bool writeToBuffer(char output, char *buffer, int bufferLength, int *bufferPosition) {
    buffer[*bufferPosition] = output;
    ++*bufferPosition;
    return *bufferPosition < bufferLength;
}

YardConsumeResult shuntingYardConsumeInput(ShuntingYard *yard, char input, char *outputBuffer, int bufferLength, int *bufferPosition) {
    if (*bufferPosition >= bufferLength) {
        return YARD_BUFFER_OVERFLOW;
    }

    switch (input)
    {
    case '(':
        if (!stackPush(yard->stack, input)) {
            return YARD_ALLOCATION_ERROR;
        }
        return YARD_OK;

    case '+':
    case '-':
    case '*':
    case '/':
    {
        uint64_t stackTop = 0;
        while (stackTryPeek(yard->stack, &stackTop)) {
            char chr = (char)stackTop;

            if (getPrecedence(chr) < getPrecedence(input)) {
                break;
            }

            stackTryPop(yard->stack, &stackTop);
            if (!writeToBuffer(chr, outputBuffer, bufferLength, bufferPosition)) {
                return YARD_BUFFER_OVERFLOW;
            }
        }

        if (!stackPush(yard->stack, input)) {
            return YARD_ALLOCATION_ERROR;
        }
        return YARD_OK;
    }

    case ')':
    {
        uint64_t stackTop = 0;
        while (stackTryPop(yard->stack, &stackTop)) {
            char chr = (char)stackTop;

            if (chr == '(') {
                return YARD_OK;
            }
            if (!writeToBuffer(chr, outputBuffer, bufferLength, bufferPosition)) {
                return YARD_BUFFER_OVERFLOW;
            }
        }

        return YARD_INCORRECT_INPUT;
    }

    case '\0':
    {
        uint64_t stackTop = 0;
        while (stackTryPop(yard->stack, &stackTop)) {
            if (!writeToBuffer((char)stackTop, outputBuffer, bufferLength, bufferPosition)) {
                return YARD_BUFFER_OVERFLOW;
            }
        }

        return YARD_OK;
    }

    default:
        if (input >= '0' && input <= '9') {
            if (!writeToBuffer(input, outputBuffer, bufferLength, bufferPosition)) {
                return YARD_BUFFER_OVERFLOW;
            }
            return YARD_OK;
        }
        return YARD_UNKNOWN_INPUT;
    }
}

void shuntingYardDispose(ShuntingYard *yard) {
    stackDispose(yard->stack);
    free(yard);
}
