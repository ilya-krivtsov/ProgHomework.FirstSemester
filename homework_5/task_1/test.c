#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "bracketsBalance.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

CTEST(bracketsBalanceTest, emptyStringTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced(""), BALANCED);
}

CTEST(bracketsBalanceTest, randomCharactersTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("sdfhJGGjGJHJhgJhgjhgFygYIOTyF:bKFyGFTKYtygGhggFYTfhkuasbvV2346T362T7*$&^I^&26234R623"), BALANCED);
}

CTEST(bracketsBalanceTest, singleOpeningBracketTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("("), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("["), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("{"), UNBALANCED);
}

CTEST(bracketsBalanceTest, singleClosingBracketTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced(")"), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("]"), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("}"), UNBALANCED);
}

CTEST(bracketsBalanceTest, singlePairTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("()"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("[]"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("{}"), BALANCED);
}

CTEST(bracketsBalanceTest, nonNestedPairsTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("()[]{}{}"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("[](){}[][][]"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("{}[]()(){}[]"), BALANCED);
}

CTEST(bracketsBalanceTest, nestedPairsTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("({[]})"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("{{{}}}[[[]]]((()))"), BALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("{()[({}()[]){[]}()({})]}"), BALANCED);
}

CTEST(bracketsBalanceTest, unbalancedTest) {
    ASSERT_EQUAL(checkIfBracketsBalanced("{({)}}"), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("(((((([))))))]"), UNBALANCED);
    ASSERT_EQUAL(checkIfBracketsBalanced("(({}(({}(([))){})))]"), UNBALANCED);
}
