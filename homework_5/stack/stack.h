#pragma once

#include <stdbool.h>
#include <stdint.h>

/// @brief Stack that stores all of its elements as `uint64_t`
typedef struct Stack Stack;

/// @brief Creates `Stack`
/// @param stack Pointer to store created `Stack` to
/// @return `true` if successful, `false` otherwise (allocation failed)
bool stackCreate(Stack **stack);

/// @brief Pushes value on top of the stack
/// @param stack Pointer to `Stack` instance
/// @return `true` if successful, `false` otherwise (allocation failed)
bool stackPush(Stack *stack, uint64_t value);

/// @brief Pops value from the top of the stack
/// @param stack Pointer to `Stack` instance
/// @param value Pointer to write value to
/// @return `true` if stack was non-empty, `false` otherwise
bool stackTryPop(Stack *stack, uint64_t *value);

/// @brief Returns value from the top of the stack without removing it
/// @param stack Pointer to `Stack` instance
/// @param value Pointer to write value to
/// @return `true` if stack was non-empty, `false` otherwise
bool stackTryPeek(Stack *stack, uint64_t *value);

/// @brief Checks if stack is empty
/// @param stack Pointer to `Stack` instance
/// @return `true` if stack is empty, `false` otherwise
bool stackIsEmpty(Stack *stack);

/// @brief Disposes stack and all of its elements
/// @param stack `Stack` to dispose 
void stackDispose(Stack *stack);
