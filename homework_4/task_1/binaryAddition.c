#include "binaryAddition.h"

#include <stdbool.h>
#include <stdio.h>

int8_t addTwoNumbers(int8_t left, int8_t right, AdditionCallback callback) {
    const int bitWidth = sizeof(int8_t) * 8;

    int8_t result = 0;
    int8_t accumulatedCarry = 0;
    bool carryBit = 0;

    if (callback != NULL) {
        callback(left, right, result, accumulatedCarry, false, false, false, false, false, 0);
    }

    for (int i = 0; i < bitWidth; ++i) {
        bool leftBit = ((left >> i) & 1) == 1;
        bool rightBit = ((right >> i) & 1) == 1;
        bool resultBit = ((leftBit + rightBit + carryBit) % 2) == 1;

        bool newCarryBit = (leftBit + rightBit + carryBit) >= 2;

        result |= resultBit << i;
        accumulatedCarry |= newCarryBit << i;

        if (callback != NULL) {
            callback(left, right, result, accumulatedCarry, leftBit, rightBit, resultBit, carryBit, newCarryBit, i + 1);
        }
        carryBit = newCarryBit;
    }

    return result;
}
