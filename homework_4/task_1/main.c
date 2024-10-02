#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "binaryAddition.h"

// set to false to disable color and line overrides
#define PRINT_ANSI true

void printAnsi(const char *format) {
#if PRINT_ANSI
    printf(format);
#endif
}

void printBinary(stdint number, int bits, int bitToHighlight) {
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

void printStep(stdint left, stdint right, stdint accumulatedResult, stdint accumulatedCarry,
    stdint leftBit, stdint rightBit, stdint resultBit, stdint oldCarryBit, stdint newCarryBit, int steps) {

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

    const int bitWidth = sizeof(stdint) * 8;

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

stdint readValue(const char *prompt, const char *incorrectValueMessage, long long lowLimit, long long highLimit) {
    long long value;
    printf(prompt);
    while ((scanf("%lld", &value) != 1) || value < lowLimit || value > highLimit) {
        while (getchar() != '\n') {}
        printf(incorrectValueMessage, lowLimit, highLimit);
    }
    return (stdint)value;
}

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    const char *errorMessage = "введено неверное значение: число должно быть больше %d и меньше %d; попробуйте ещё раз: ";
    stdint left = readValue("введите первое число: ", errorMessage, STDINT_MIN, STDINT_MAX);
    stdint right = readValue("введите второе число: ", errorMessage, STDINT_MIN, STDINT_MAX);

    // reset input
    while (getchar() != '\n') {}

    printf("для следующего шага нажмите Enter\n");

    stdint result = addTwoNumbers(left, right, printStep);

    printf("результат: \n");
    printf("%d + %d = %d\n", left, right, result);
}
