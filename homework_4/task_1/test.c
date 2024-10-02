#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>

#include "binaryAddition.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

CTEST(additionTests, zeroTest) {
    ASSERT_EQUAL(addTwoNumbers(0, 0, NULL), 0);
}

CTEST(additionTests, zeroPlusAnyTest) {
    ASSERT_EQUAL(addTwoNumbers(0, 1, NULL), 1);
    ASSERT_EQUAL(addTwoNumbers(0, 2, NULL), 2);
    ASSERT_EQUAL(addTwoNumbers(0, 4, NULL), 4);
    ASSERT_EQUAL(addTwoNumbers(0, 45, NULL), 45);
    ASSERT_EQUAL(addTwoNumbers(0, 98, NULL), 98);
    ASSERT_EQUAL(addTwoNumbers(0, 121, NULL), 121);
    ASSERT_EQUAL(addTwoNumbers(0, -1, NULL), -1);
    ASSERT_EQUAL(addTwoNumbers(0, -3, NULL), -3);
    ASSERT_EQUAL(addTwoNumbers(0, -11, NULL), -11);
}

CTEST(additionTests, oneNegativeTest) {
    ASSERT_EQUAL(addTwoNumbers(31, -29, NULL), 2);
    ASSERT_EQUAL(addTwoNumbers(-16, 4, NULL), -12);
    ASSERT_EQUAL(addTwoNumbers(-1, 1, NULL), 0);
    ASSERT_EQUAL(addTwoNumbers(-100, 100, NULL), 0);
}

CTEST(additionTests, twoNegativeTest) {
    ASSERT_EQUAL(addTwoNumbers(-31, -29, NULL), -60);
    ASSERT_EQUAL(addTwoNumbers(-1, -2, NULL), -3);
    ASSERT_EQUAL(addTwoNumbers(-10, -24, NULL), -34);
    ASSERT_EQUAL(addTwoNumbers(-110, -10, NULL), -120);
}
