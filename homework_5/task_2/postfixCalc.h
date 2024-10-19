#pragma once

#include "stdbool.h"

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

bool calcCreate(PostfixCalc **calc);

CalcConsumeResult calcConsumeInput(PostfixCalc *calc, char input);

CalcGetResultResult calcTryGetResult(PostfixCalc *calc, int *result);

void calcDispose(PostfixCalc *calc);
