#pragma once

#include <stdint.h>

typedef int8_t stdint;
#define STDINT_MIN INT8_MIN
#define STDINT_MAX INT8_MAX

/// Callback that is called after performing every step of addition.
/// Arguments in order: left, right, accumulatedResult, accumulatedCarryBits,
/// leftBit, rightBit, resultBit, oldCarryBit, newCarryBit, steps (0 before first step, incrementing after every step)
typedef void (*AdditionCallback)(stdint, stdint, stdint, stdint, stdint, stdint, stdint, stdint, stdint, int);

/// @brief Adds two numbers with pre-step callback
/// @param left Left operand
/// @param right Right operand
/// @param callback Function to call after every step, can be `NULL`; it will be called once before first step
/// @return Result of the addition
stdint addTwoNumbers(stdint left, stdint right, AdditionCallback callback);
