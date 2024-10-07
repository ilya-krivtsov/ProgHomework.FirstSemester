#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "fibonacci.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

typedef uint64_t(*fib)(uint64_t);

void test(fib fib) {
    ASSERT_EQUAL(fib(0), 0);
    ASSERT_EQUAL(fib(1), 1);
    ASSERT_EQUAL(fib(2), 1);
    ASSERT_EQUAL(fib(3), 2);
    ASSERT_EQUAL(fib(4), 3);
    ASSERT_EQUAL(fib(5), 5);
    ASSERT_EQUAL(fib(6), 8);
    ASSERT_EQUAL(fib(7), 13);
    ASSERT_EQUAL(fib(8), 21);
    ASSERT_EQUAL(fib(9), 34);
    ASSERT_EQUAL(fib(10), 55);
}

CTEST(powerTests, fibonacciIterativeTest) {
    test(fibonacciIterative);
}

CTEST(powerTests, fibonacciRecursiveTest) {
    test(fibonacciRecursive);
}
