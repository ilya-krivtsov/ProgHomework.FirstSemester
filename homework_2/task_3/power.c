#include "power.h"

uint64_t powerNaiive(uint64_t base, uint64_t exponent) {

    uint64_t result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }

    return result;
}

uint64_t powerRecursive(uint64_t base, uint64_t exponent) {
    if (exponent == 0) {
        return 1;
    }

    uint64_t result = powerRecursive(base, exponent / 2);
    result *= result;
    return exponent % 2 == 0 ? result : result * base;
}

uint64_t powerIterative(uint64_t base, uint64_t exponent) {
    uint64_t result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        exponent /= 2;
        base *= base;
    }

    return result;
}
