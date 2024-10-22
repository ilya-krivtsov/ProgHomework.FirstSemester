#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdint.h>

#include "../stack/stack.h"
#include "shuntingYard.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

ShuntingYard *createYard(void) {
    ShuntingYard *yard;
    ASSERT_TRUE(shuntingYardCreate(&yard));
    ASSERT_NOT_NULL(yard);

    return yard;
}

void assertOutput(ShuntingYard *yard, const char *input, const char *expectedOutput) {
#define BUFFER_LENGTH 1024
    char buffer[BUFFER_LENGTH] = { 0 };
    int bufferPosition = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        ASSERT_EQUAL(shuntingYardConsumeInput(yard, input[i], buffer, BUFFER_LENGTH, &bufferPosition), YARD_OK);
    }

    ASSERT_EQUAL(shuntingYardConsumeInput(yard, '\0', buffer, BUFFER_LENGTH, &bufferPosition), YARD_OK);

    ASSERT_STR(buffer, expectedOutput);

#undef BUFFER_LENGTH
}

void testYard(const char *input, const char *expectedOutput) {
    ShuntingYard *yard = createYard();
    assertOutput(yard, input, expectedOutput);
    shuntingYardDispose(yard);
}

CTEST(yardTests, createTest) {
    ShuntingYard *yard = createYard();
    shuntingYardDispose(yard);
}

CTEST(yardTests, singleNumberTest) {
    testYard("0", "0");
    testYard("5", "5");
}

CTEST(yardTests, simpleOperationTest) {
    testYard("0+0", "00+");
    testYard("5+5", "55+");

    testYard("5-7", "57-");
    testYard("5-5", "55-");

    testYard("0*5", "05*");
    testYard("8*4", "84*");

    testYard("4/2", "42/");
    testYard("9/4", "94/");
}

CTEST(yardTests, simpleOperationInParenthesesTest) {
    testYard("(0+0)", "00+");
    testYard("(5+5)", "55+");

    testYard("(5-7)", "57-");
    testYard("(5-5)", "55-");

    testYard("(0*5)", "05*");
    testYard("(8*4)", "84*");

    testYard("(4/2)", "42/");
    testYard("(9/4)", "94/");
}

CTEST(yardTests, operationBetweenParenthesesAndNumberTest) {
    testYard("(0+0)*4", "00+4*");
    testYard("(5+5)-3", "55+3-");

    testYard("(5-7)/1", "57-1/");
    testYard("1+(5-5)", "155-+");

    testYard("(0*5)*9", "05*9*");
    testYard("2+(8*4)", "284*+");

    testYard("(4/2)-8", "42/8-");
    testYard("(9/4)*6", "94/6*");
}

CTEST(yardTests, operationBetweenTwoParenthesesTest) {
    testYard("(4-1)*(8+1)", "41-81+*");
    testYard("(9*2)/(9-2)", "92*92-/");
    testYard("(6/3)+(8/2)", "63/82/+");
}
