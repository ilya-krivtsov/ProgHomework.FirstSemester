#include <stdio.h>
#include <time.h>

#include "fibonacci.h"

// returns time in nanoseconds
uint64_t measureTime(uint64_t(*fib)(uint64_t), int n) {
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    fib(n);
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    return (endTime.tv_nsec - startTime.tv_nsec) + (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 * 1000;
}

int main(void) {
    const int maxIteration = 200;
    for (int i = 0; i <= maxIteration; ++i) {
        uint64_t n = i;

        double iterativeTimeMillis = measureTime(fibonacciIterative, n) / 1000.0 / 1000.0;
        double recursiveTimeMillis = measureTime(fibonacciRecursive, n) / 1000.0 / 1000.0;

        // consider that function A is noticeably slower than function B if
        // A executes more at least twice as slow as B and takes more than 500 ms
        if ((recursiveTimeMillis / iterativeTimeMillis) > 2 && recursiveTimeMillis > 500.0) {
            printf("recusive algorithm is noticeably slower than iterative at iteration %llu:\n", n);
            printf("fibonacciIterative took %.2f ms;\n", iterativeTimeMillis);
            printf("fibonacciRecursive took %.2f ms\n", recursiveTimeMillis);

            return 0;
        }
    }

    printf("recursive algorithm wasn't much slower than iterative in range of values [0, %d]\n", maxIteration);
}
