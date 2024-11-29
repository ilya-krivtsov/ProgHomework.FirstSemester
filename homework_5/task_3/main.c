#include <stdio.h>

#include "shuntingYard.h"

bool consumeInput(ShuntingYard *yard, char input) {
    char buffer[1024] = { 0 };
    int safeBufferLength = 1024 - 1;
    int bufferPosition = 0;

    switch (shuntingYardConsumeInput(yard, input, buffer, safeBufferLength, &bufferPosition))
    {
    case YARD_OK:
        break;

    case YARD_ALLOCATION_ERROR:
        printf("allocation error\n");
        return false;

    case YARD_INCORRECT_INPUT:
        printf("incorrect input - probably missed an opening parenthesis\n");
        return false;

    case YARD_BUFFER_OVERFLOW:
        printf("buffer ovwerflow - input was too long\n");
        return false;

    case YARD_UNKNOWN_INPUT:
        printf("unknown character: '%c'\n", input);
        return false;
    }

    printf("%s", buffer);
    return true;
}

bool readAndEvaluate(ShuntingYard *yard) {
    printf("input infix notation expression (allowed characters: ()0123456789+-*/) (you can use space to split characters):\n");
    printf(" > ");

    while (true) {
        char input = getchar();
        if (input == EOF || input == '\n') {
            break;
        }

        if (input == ' ') {
            continue;
        }

        if (!consumeInput(yard, input)) {
            return false;
        }
    }
    return consumeInput(yard, '\0');
}

int main(void) {
    ShuntingYard *yard;

    if (!shuntingYardCreate(&yard)) {
        printf("allocation failed");
        return 1;
    }

    if (!readAndEvaluate(yard)) {
        shuntingYardDispose(yard);
        return 1;
    }

    shuntingYardDispose(yard);
}
