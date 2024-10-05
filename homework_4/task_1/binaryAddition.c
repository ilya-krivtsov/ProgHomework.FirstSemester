#include "binaryAddition.h"

#include "stdio.h"

int8_t addTwoNumbers(int8_t left, int8_t right, AdditionCallback callback) {
    const int bitWidth = sizeof(int8_t) * 8;

    int8_t result = 0, carryBit = 0, accumulatedCarry = 0;

    if (callback != NULL) {
        callback(left, right, result, accumulatedCarry, 0, 0, 0, 0, 0, 0);
    }

    for (int i = 0; i < bitWidth; ++i) {
        int8_t
            leftBit = (left >> i) & 1,
            rightBit = (right >> i) & 1,
            resultBit = 0;

        resultBit = (leftBit + rightBit + carryBit) % 2;
        int8_t newCarryBit = leftBit + rightBit + carryBit >= 2 ? 1 : 0;

        result |= resultBit << i;
        accumulatedCarry |= newCarryBit << i;

        if (callback != NULL) {
            callback(left, right, result, accumulatedCarry, leftBit, rightBit, resultBit, carryBit, newCarryBit, i + 1);
        }
        carryBit = newCarryBit;
    }

    return result;
}
