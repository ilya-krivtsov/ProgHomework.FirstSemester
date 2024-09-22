#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "power.h"

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}

typedef uint64_t(*power)(uint64_t, uint64_t);

void testExponentIsZero(power power) {
    ASSERT_EQUAL(power(0, 0), 1); /* for now let 0 ^ 0 == 1 */
    ASSERT_EQUAL(power(1, 0), 1);
    ASSERT_EQUAL(power(2, 0), 1);
    ASSERT_EQUAL(power(4, 0), 1);
    ASSERT_EQUAL(power(100, 0), 1);
    ASSERT_EQUAL(power(100000, 0), 1);
    ASSERT_EQUAL(power(10000000, 0), 1);
}

void testBaseIsZero(power power) {
    ASSERT_EQUAL(power(0, 1), 0);
    ASSERT_EQUAL(power(0, 2), 0);
    ASSERT_EQUAL(power(0, 4), 0);
    ASSERT_EQUAL(power(0, 10), 0);
    ASSERT_EQUAL(power(0, 100), 0);
    ASSERT_EQUAL(power(0, 10'000), 0);
    ASSERT_EQUAL(power(0, 1'000'000), 0);
}

void testBaseIsOne(power power) {
    ASSERT_EQUAL(power(1, 1), 1);
    ASSERT_EQUAL(power(1, 2), 1);
    ASSERT_EQUAL(power(1, 4), 1);
    ASSERT_EQUAL(power(1, 10), 1);
    ASSERT_EQUAL(power(1, 100), 1);
    ASSERT_EQUAL(power(1, 10'000), 1);
    ASSERT_EQUAL(power(1, 1'000'000), 1);
}

void testRegularCases(power power) {
    ASSERT_EQUAL(power(2, 1), 2);
    ASSERT_EQUAL(power(2, 2), 4);
    ASSERT_EQUAL(power(2, 4), 16);
    ASSERT_EQUAL(power(4, 3), 64);
    ASSERT_EQUAL(power(4, 8), 65'536);
    ASSERT_EQUAL(power(10, 3), 1'000);
    ASSERT_EQUAL(power(10, 6), 1'000'000);
}

void testAllCases(power power) {
    testExponentIsZero(power);
    testBaseIsZero(power);
    testBaseIsOne(power);
    testRegularCases(power);
}

CTEST(powerTests, powerNaiiveTest) {
    testAllCases(powerNaiive);
}

CTEST(powerTests, powerRecursiveTest) {
    testAllCases(powerRecursive);
}

CTEST(powerTests, powerIterativeTest) {
    testAllCases(powerIterative);
}
