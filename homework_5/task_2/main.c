#include <stdio.h>

#include "postfixCalc.h"

bool readAndEvaluate(PostfixCalc *calc) {
    printf("input digits and operands (allowed characters: 0123456789+-*/) (you can use space to split them):\n");
    printf(" > ");

    while (true) {
        char input = getchar();
        if (input == EOF || input == '\n') {
            break;
        }

        if (input == ' ') {
            continue;
        }

        switch (calcConsumeInput(calc, input))
        {
        case CALC_CONSUME_OK:
            break;
        case CALC_CONSUME_ALLOCATION_ERROR:
            printf("allocation error\n");
            return false;

        case CALC_CONSUME_NOT_ENOUGH_OPERANDS:
            printf("not enough operands to perform operation '%c'\n", input);
            return false;

        case CALC_CONSUME_UNKNOWN_INPUT:
            printf("unknown character: '%c'\n", input);
            return false;
        }
    }

    int result = 0;

    switch (calcTryGetResult(calc, &result))
    {
    case CALC_GET_RESULT_OK:
        printf("evaluation result: %d\n", result);
        break;

    case CALC_IS_EMPTY_BEFORE_READ:
        printf("nothing to evaluate\n");
        return false;

    case CALC_NOT_EMPTY_AFTER_READ:
        printf("not all numbers are used\n");
        return false;
    }

    return true;
}

int main(void) {
    PostfixCalc *calc;

    if (!calcCreate(&calc)) {
        printf("allocation failed");
        return 1;
    }

    if (!readAndEvaluate(calc)) {
        calcDispose(calc);
        return 1;
    }

    calcDispose(calc);
}
