#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "expressionTree.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

ExpressionTree *readTree(FILE *file) {
    ExpressionTree *tree = NULL;
    ASSERT_TRUE(readExpressionTree(&tree, file));
    ASSERT_NOT_NULL(tree);

    return tree;
}

void assertExpression(const char *expression, int expectedResult) {
    const char *filename = "testTree.txt";

    FILE *file = fopen(filename, "w+");
    ASSERT_NOT_NULL(file);
    fprintf(file, "%s\n", expression);
    ASSERT_EQUAL(fclose(file), 0);

    file = fopen(filename, "r");
    ASSERT_NOT_NULL(file);
    ExpressionTree *tree = readTree(file);
    ASSERT_EQUAL(fclose(file), 0);
    ASSERT_EQUAL(remove(filename), 0);

    ASSERT_EQUAL(evaluateExpressionTree(tree), expectedResult);

    disposeTree(tree);
}

CTEST(expressionTreeTests, singleExpressionTest) {
    assertExpression("(+ 2 3)", (2 + 3));
    assertExpression("(- 24 14)", (24 - 14));
    assertExpression("(* 15 17)", (15 * 17));
    assertExpression("(/ 45 10)", (45 / 10));
}

CTEST(expressionTreeTests, twoNestedExpressionTest) {
    assertExpression("(* (+ 12 11) 21)", ((12 + 11) * 21));
    assertExpression("(- 64 (* 7 9))", (64 - (7 * 9)));
    assertExpression("(+ (* 2 1) (/ 6 2))", ((2 * 1) + (6 / 2)));
    assertExpression("(* (* 4 9) (- 5 -4))", ((4 * 9) * (5 - (-4))));
    assertExpression("(+ (- 23 4) (* 3 21))", ((23 - 4) + (3 * 21)));
}

CTEST(expressionTreeTests, nestedExpressionTest) {
    assertExpression("(/ (* 2 (+ -1 (/ -12 12))) (* 2 4))", ((2 * (-1 + (-12 / 12))) / (2 * 4)));
    assertExpression("(* 2 (+ 1 (/ 12 12)))", (2 * (1 + (12 / 12))));
}
