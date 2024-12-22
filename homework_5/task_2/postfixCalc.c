#include "postfixCalc.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../stack/stack.h"

typedef struct PostfixCalc {
    Stack *stack;
} PostfixCalc;

bool calcCreate(PostfixCalc **calc) {
    *calc = malloc(sizeof(PostfixCalc));
    if (*calc == NULL) {
        return false;
    }

    if (!stackCreate(&(*calc)->stack)) {
        return false;
    }

    return true;
}

CalcConsumeResult calcConsumeInput(PostfixCalc *calc, char input) {
    switch (input)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        uint64_t valueA = -1;
        if (!stackTryPop(calc->stack, &valueA)) {
            return CALC_CONSUME_NOT_ENOUGH_OPERANDS;
        }

        uint64_t valueB = -1;
        if (!stackTryPop(calc->stack, &valueB)) {
            return CALC_CONSUME_NOT_ENOUGH_OPERANDS;
        }

        int left = (int)valueB;
        int right = (int)valueA;

        int value = 0;
        if (input == '+') {
            value = left + right;
        } else if (input == '-') {
            value = left - right;
        } else if (input == '*') {
            value = left * right;
        } else if (input == '/') {
            value = left / right;
        }

        if (!stackPush(calc->stack, (uint64_t)value)) {
            return CALC_CONSUME_ALLOCATION_ERROR;
        }

        break;

    default:
        if (input >= '0' && input <= '9') {
            uint64_t value = input - '0';
            if (!stackPush(calc->stack, value)) {
                return CALC_CONSUME_ALLOCATION_ERROR;
            }
        } else {
            return CALC_CONSUME_UNKNOWN_INPUT;
        }

        break;
    }

    return CALC_CONSUME_OK;
}

CalcGetResultResult calcTryGetResult(PostfixCalc *calc, int *result) {
    uint64_t value = 0;
    if (!stackTryPop(calc->stack, &value)) {
        return CALC_IS_EMPTY_BEFORE_READ;
    }

    *result = (int)value;
    return stackIsEmpty(calc->stack) ? CALC_GET_RESULT_OK : CALC_NOT_EMPTY_AFTER_READ;
}

void calcDispose(PostfixCalc *calc) {
    stackDispose(calc->stack);
    free(calc);
}
