#include "bracketsBalance.h"

#include <stdlib.h>

#include "../stack/stack.h"

BalanceResult checkIfBracketsBalanced(const char *string) {
    Stack *stack = NULL;
    if (!stackCreate(&stack)) {
        return ALLOCATION_FAILED;
    }

    bool checkedAll = true;

    for (int i = 0; string[i] != '\0'; ++i) {
        char chr = string[i];

        if (chr == '(' || chr == '[' || chr == '{') {
            stackPush(stack, chr);
        } else if (chr == ')' || chr == ']' || chr == '}') {
            uint64_t value = -1;
            if (!stackTryPop(stack, &value)) {
                checkedAll = false;
                break;
            }

            char popped = (char)value;

            if ((popped == '(' && chr != ')') ||
                (popped == '[' && chr != ']') ||
                (popped == '{' && chr != '}')) {
                checkedAll = false;
                break;
            }
        }
    }

    BalanceResult result = checkedAll && stackIsEmpty(stack) ? BALANCED : UNBALANCED;

    stackDispose(stack);

    return result;
}
