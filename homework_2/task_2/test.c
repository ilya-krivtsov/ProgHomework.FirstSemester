#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "power.h"

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}

#define TEST_ZERO_EXPONENT(implementation) CTEST(powerTests, test_##implementation##_zeroExponent) {    \
    ASSERT_EQUAL(implementation(0, 0), 1); /* for now let 0 ^ 0 == 1 */                                 \
    ASSERT_EQUAL(implementation(1, 0), 1);                                                              \
    ASSERT_EQUAL(implementation(2, 0), 1);                                                              \
    ASSERT_EQUAL(implementation(4, 0), 1);                                                              \
    ASSERT_EQUAL(implementation(100, 0), 1);                                                            \
    ASSERT_EQUAL(implementation(100000, 0), 1);                                                         \
    ASSERT_EQUAL(implementation(10000000, 0), 1);                                                       \
}

#define TEST_BASE_IS_ZERO(implementation) CTEST(powerTests, test_##implementation##_base_is_zero) { \
    ASSERT_EQUAL(implementation(0, 1), 0);                                                          \
    ASSERT_EQUAL(implementation(0, 2), 0);                                                          \
    ASSERT_EQUAL(implementation(0, 4), 0);                                                          \
    ASSERT_EQUAL(implementation(0, 10), 0);                                                         \
    ASSERT_EQUAL(implementation(0, 100), 0);                                                        \
    ASSERT_EQUAL(implementation(0, 10'000), 0);                                                     \
    ASSERT_EQUAL(implementation(0, 1'000'000), 0);                                                  \
}

#define TEST_BASE_IS_ONE(implementation) CTEST(powerTests, test_##implementation##_base_is_one) {   \
    ASSERT_EQUAL(implementation(1, 1), 1);                                                          \
    ASSERT_EQUAL(implementation(1, 2), 1);                                                          \
    ASSERT_EQUAL(implementation(1, 4), 1);                                                          \
    ASSERT_EQUAL(implementation(1, 10), 1);                                                         \
    ASSERT_EQUAL(implementation(1, 100), 1);                                                        \
    ASSERT_EQUAL(implementation(1, 10'000), 1);                                                     \
    ASSERT_EQUAL(implementation(1, 1'000'000), 1);                                                  \
}

#define TEST_REGULAR_CASES(implementation) CTEST(powerTests, test_##implementation##_regular_cases) {   \
    ASSERT_EQUAL(implementation(2, 1), 2);                                                              \
    ASSERT_EQUAL(implementation(2, 2), 4);                                                              \
    ASSERT_EQUAL(implementation(2, 4), 16);                                                             \
    ASSERT_EQUAL(implementation(4, 3), 64);                                                             \
    ASSERT_EQUAL(implementation(4, 8), 65'536);                                                         \
    ASSERT_EQUAL(implementation(10, 3), 1'000);                                                         \
    ASSERT_EQUAL(implementation(10, 6), 1'000'000);                                                     \
}

#define TEST_IMPLEMENTATION(implementation) \
    TEST_ZERO_EXPONENT(implementation) \
    TEST_BASE_IS_ZERO(implementation) \
    TEST_BASE_IS_ONE(implementation) \
    TEST_REGULAR_CASES(implementation)

TEST_IMPLEMENTATION(powerIterative)
TEST_IMPLEMENTATION(powerRecursive)
TEST_IMPLEMENTATION(powerNaiive)
