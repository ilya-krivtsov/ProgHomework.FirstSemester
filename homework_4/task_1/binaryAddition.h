#pragma once

#include <stdint.h>

/// Callback that is called after performing every step of addition.
/// Arguments in order: left, right, accumulatedResult, accumulatedCarryBits,
/// leftBit, rightBit, resultBit, oldCarryBit, newCarryBit, steps (0 before first step, incrementing after every step)
typedef void (*AdditionCallback)(int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int);

/// @brief Adds two numbers with pre-step callback
/// @param left Left operand
/// @param right Right operand
/// @param callback Function to call after every step, can be `NULL`; it will be called once before first step
/// @return Result of the addition
int8_t addTwoNumbers(int8_t left, int8_t right, AdditionCallback callback);
