#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "postfixCalc.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

PostfixCalc *createCalc(void) {
    PostfixCalc *calc;
    ASSERT_TRUE(calcCreate(&calc));
    ASSERT_NOT_NULL(calc);

    return calc;
}

void assertResult(PostfixCalc *calc, int expected) {
    int result = 0;
    ASSERT_EQUAL(calcTryGetResult(calc, &result), CALC_GET_RESULT_OK);
    ASSERT_EQUAL(expected, result);
}

void assertConsumeString(PostfixCalc *calc, const char *input, int expected) {
    for (int i = 0; input[i] != '\0'; ++i) {
        ASSERT_EQUAL(calcConsumeInput(calc, input[i]), CALC_CONSUME_OK);
    }

    assertResult(calc, expected);
}

void testCalc(const char *input, int expected) {
    PostfixCalc *calc = createCalc();

    assertConsumeString(calc, input, expected);

    free(calc);
}

CTEST(postfixCalcTests, createTest) {
    PostfixCalc *calc = createCalc();
    free(calc);
}

CTEST(postfixCalcTests, singleNumberTest) {
    testCalc("4", 4);
}

CTEST(postfixCalcTests, additionTest) {
    testCalc("12+", 3);
    testCalc("00+", 0);
    testCalc("50+", 5);
    testCalc("09+", 9);
    testCalc("78+", 15);
    testCalc("99+", 18);
}

CTEST(postfixCalcTests, subtractionTest) {
    testCalc("53-", 2);
    testCalc("00-", 0);
    testCalc("50-", 5);
    testCalc("09-", -9);
    testCalc("78-", -1);
    testCalc("99-", 0);
    testCalc("98-", 1);
    testCalc("38-", -5);
}

CTEST(postfixCalcTests, multiplicationTest) {
    testCalc("53*", 15);
    testCalc("00*", 0);
    testCalc("50*", 0);
    testCalc("09*", 0);
    testCalc("78*", 56);
    testCalc("99*", 81);
    testCalc("98*", 72);
    testCalc("38*", 24);
    testCalc("88*", 64);
}

CTEST(postfixCalcTests, divisionTest) {
    testCalc("51/", 5);
    testCalc("09/", 0);
    testCalc("78/", 0);
    testCalc("99/", 1);
    testCalc("93/", 3);
    testCalc("31/", 3);
    testCalc("88/", 1);
    testCalc("82/", 4);
    testCalc("62/", 3);
    testCalc("63/", 2);
}

CTEST(postfixCalcTests, complexTest) {
    testCalc("12+34++", 10);
    testCalc("12+34+*", 21);
    testCalc("12+34+*2*", 42);
    testCalc("12*34*56***", 720);

    testCalc("96-12+*", 9);
}
