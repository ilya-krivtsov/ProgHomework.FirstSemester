#pragma once

typedef struct ShuntingYard ShuntingYard;

typedef enum {
    YARD_OK,
    YARD_UNKNOWN_INPUT,
    YARD_INCORRECT_INPUT,
    YARD_BUFFER_OVERFLOW,
    YARD_ALLOCATION_ERROR
} YardConsumeResult;

bool shuntingYardCreate(ShuntingYard **yard);

YardConsumeResult shuntingYardConsumeInput(ShuntingYard *yard, char input, char *outputBuffer, int bufferLength, int *bufferPosition);

void shuntingYardDispose(ShuntingYard *yard);
