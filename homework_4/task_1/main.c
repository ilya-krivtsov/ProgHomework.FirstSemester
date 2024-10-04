#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>

#include "binaryAddition.h"

// set to false to disable color and line overrides
#define PRINT_ANSI true

void printAnsi(const char *format) {
#if PRINT_ANSI
    printf(format);
#endif
}

void printBinary(int8_t number, int bits, int bitToHighlight) {
    for (int i = bits - 1; i >= 0; --i) {
        int bit = (number >> i) & 1;
        if (i == bitToHighlight) {
            printAnsi("\e[1;32m");
            printf("%d", bit);
            printAnsi("\e[0m");
        } else {
            printf("%d", bit);
        }
    }
}

void printStep(int8_t left, int8_t right, int8_t accumulatedResult, int8_t accumulatedCarry,
    int8_t leftBit, int8_t rightBit, int8_t resultBit, int8_t oldCarryBit, int8_t newCarryBit, int steps) {

    if (steps != 0) {
#if PRINT_ANSI
        // 0th step prints 4 lines, 1st step and further - 6, and user inputs one more
        const int clearLines = (steps == 1 ? 4 : 6) + 1;

        // move cursor back, clear all lines and move cursor again 
        printf("\e[%dA", clearLines);
        for (int i = 0; i < clearLines; ++i) {
            printf("\e[K\n");
        }
        printf("\e[%dA", clearLines);
#endif
    }

    const int bitWidth = sizeof(int8_t) * 8;

    // 1 space here because carry can overflow
    printf(" ");
    // print all carry bits
    for (int i = bitWidth - 1; i >= 0; --i) {
        if ((accumulatedCarry >> i) & 1 == 1) {
            if (i + 1 == steps) {
                printAnsi("\e[43m");
                printf(".");
                printAnsi("\e[0m");
            } else {
                printf(".");
            }
        } else {
            printf(" ");
        }
    }
    printf("\n");

    // print left
    printf("  ");
    printBinary(left, bitWidth, steps - 1);
    printf("\n");

    // print right
    printf("+ ");
    printBinary(right, bitWidth, steps - 1);
    printf("\n");

    // print delimiter
    printf("  ");
    for (int i = 0; i < bitWidth; ++i) {
        printf("-");
    }
    printf("\n");

    if (steps > 0) {

        const int stepsNotCompletedYet = bitWidth - steps;

        // print result
        printf("= ");
        for (int i = 0; i < stepsNotCompletedYet; ++i) {
            printf(" ");
        }
        printBinary(accumulatedResult, steps, steps - 1);
        printf("\n");

        // print head
        printf("  ");
        for (int i = 0; i < stepsNotCompletedYet; ++i) {
            printf(" ");
        }
        printf("^ <--> %d + %d", leftBit, rightBit);

        if (oldCarryBit != 0) {
            printf(" + 1");
        }

        printf(" = %d", resultBit);

        if (newCarryBit != 0) {
            printf(" (1 в уме)");
        }

        printf("\n");
    }

    // wait for enter
    while (getchar() != '\n') {}
}

int8_t readValue(const char *prompt, void (*printIncorrectValue)(long long, long long), long long lowLimit, long long highLimit) {
    long long value;
    printf("%s", prompt);
    while ((scanf("%lld", &value) != 1) || value < lowLimit || value > highLimit) {
        while (getchar() != '\n') {}
        printIncorrectValue(lowLimit, highLimit);
    }
    return (int8_t)value;
}

void printError(long long lowLimit, long long highLimit) {
    printf("введено неверное значение: число должно быть больше %lld и меньше %lld; попробуйте ещё раз: ", lowLimit, highLimit);
}

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int8_t left = readValue("введите первое число: ", printError, INT8_MIN, INT8_MAX);
    int8_t right = readValue("введите второе число: ", printError, INT8_MIN, INT8_MAX);

    // reset input
    while (getchar() != '\n') {}

    printf("для следующего шага нажмите Enter\n");

    int8_t result = addTwoNumbers(left, right, printStep);

    printf("результат: \n");
    printf("%d + %d = %d\n", left, right, result);
}
