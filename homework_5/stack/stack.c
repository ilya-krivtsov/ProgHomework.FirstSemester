#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    uint64_t value;
    struct Node *previous;
} Node;

typedef struct Stack {
    Node *head;
} Stack;

static void removeLastNode(Stack *stack) {
    Node *prev = stack->head;
    stack->head = stack->head->previous;
    free(prev);
}

bool stackCreate(Stack **stack) {
    *stack = malloc(sizeof(Stack));
    if (*stack == NULL) {
        return false;
    }

    (*stack)->head = NULL;

    return true;
}

bool stackPush(Stack *stack, uint64_t value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }

    if (stackIsEmpty(stack)) {
        node->previous = NULL;
    } else {
        node->previous = stack->head;
    }

    node->value = value;
    stack->head = node;

    return true;
}


bool stackTryPop(Stack *stack, uint64_t *value) {
    if (stackIsEmpty(stack)) {
        return false;
    }

    *value = stack->head->value;

    removeLastNode(stack);

    return true;
}

bool stackTryPeek(Stack *stack, uint64_t *value) {
    if (stackIsEmpty(stack)) {
        return false;
    }

    *value = stack->head->value;

    return true;
}

bool stackIsEmpty(Stack *stack) {
    return stack->head == NULL;
}

void stackDispose(Stack *stack) {
    while (!stackIsEmpty(stack)) {
        removeLastNode(stack);
    }

    free(stack);
}
