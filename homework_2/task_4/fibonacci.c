#include "fibonacci.h"

uint64_t fibonacciIterative(uint64_t n) {
    if (n == 0) {
        return 0;
    }

    uint64_t secondToLast = 1;
    uint64_t last = 1;

    for (uint64_t i = 2; i < n; ++i) {
        uint64_t fib = secondToLast + last;
        secondToLast = last;
        last = fib;
    }

    return last;
}

uint64_t fibonacciRecursive(uint64_t n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1 || n == 2) {
        return 1;
    }

    return fibonacciRecursive(n - 2) + fibonacciRecursive(n - 1);
}
