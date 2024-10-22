#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdint.h>

#include "stack.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

#pragma region Helpers

Stack *createStack(void) {
    Stack *stack;
    ASSERT_TRUE(stackCreate(&stack));
    ASSERT_NOT_NULL(stack);

    return stack;
}

void assertPop(Stack *stack, uint64_t value) {
    uint64_t top = 0;
    ASSERT_TRUE(stackTryPop(stack, &top));
    ASSERT_EQUAL_U(value, top);
}

void assertPeek(Stack *stack, uint64_t value) {
    uint64_t top = 0;
    ASSERT_TRUE(stackTryPeek(stack, &top));
    ASSERT_EQUAL_U(value, top);
}

#pragma endregion

CTEST(stackTests, createTest) {
    Stack *stack = createStack();
    ASSERT_TRUE(stackIsEmpty(stack));
    stackDispose(stack);
}

#pragma region Push & Pop

CTEST(stackTests, pushPopTestA) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 0));
    assertPop(stack, 0);

    ASSERT_TRUE(stackIsEmpty(stack));

    stackDispose(stack);
}

CTEST(stackTests, pushPopTestB) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 0));
    assertPop(stack, 0);
    ASSERT_TRUE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 47));
    assertPop(stack, 47);
    ASSERT_TRUE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 1245));
    ASSERT_TRUE(stackPush(stack, 44362));
    assertPop(stack, 44362);
    assertPop(stack, 1245);
    ASSERT_TRUE(stackIsEmpty(stack));

    stackDispose(stack);
}

CTEST(stackTests, pushPopTestC) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 2352));
    ASSERT_TRUE(stackPush(stack, 43634));
    assertPop(stack, 43634);
    ASSERT_FALSE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 9999));
    ASSERT_TRUE(stackPush(stack, 7777777));
    assertPop(stack, 7777777);
    assertPop(stack, 9999);
    assertPop(stack, 2352);
    ASSERT_TRUE(stackIsEmpty(stack));

    stackDispose(stack);
}

#pragma endregion

#pragma region Push & Peek

CTEST(stackTests, pushPeekTestA) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 0));
    assertPeek(stack, 0);

    ASSERT_FALSE(stackIsEmpty(stack));

    stackDispose(stack);
}

CTEST(stackTests, pushPeekTestB) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 0));
    assertPeek(stack, 0);
    ASSERT_FALSE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 47));
    assertPeek(stack, 47);
    ASSERT_FALSE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 1245));
    ASSERT_TRUE(stackPush(stack, 44362));
    assertPeek(stack, 44362);
    assertPeek(stack, 44362);
    ASSERT_FALSE(stackIsEmpty(stack));

    stackDispose(stack);
}

CTEST(stackTests, pushPeekTestC) {
    Stack *stack = createStack();

    ASSERT_TRUE(stackPush(stack, 2352));
    ASSERT_TRUE(stackPush(stack, 43634));
    assertPeek(stack, 43634);
    ASSERT_FALSE(stackIsEmpty(stack));

    ASSERT_TRUE(stackPush(stack, 9999));
    ASSERT_TRUE(stackPush(stack, 7777777));
    assertPeek(stack, 7777777);
    assertPeek(stack, 7777777);
    assertPeek(stack, 7777777);
    ASSERT_FALSE(stackIsEmpty(stack));

    stackDispose(stack);
}

#pragma endregion
