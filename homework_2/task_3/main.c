#include <stdio.h>

#include "power.h"

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value = -1;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
    return value;
}

// for some reason migw requires %llu format specifier for uint64_t, and gcc requires %lu,
// so either in CI or on local machine with mingw there would be a format warning,
// because of that %lu will be used here for uint64_t, and when compiling with mingw just suppress format warnings
#ifdef __MINGW64__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

int main(void) {
    int base = readValue("enter base: ", "incorrect value: base cannot be less than zero; try again: ");
    int exponent = readValue("enter exponent: ", "incorrect value: exponent cannot be less than zero; try again: ");

    printf("%d ^ %d = %lu (recursive: O(log n))\n", base, exponent, powerRecursive(base, exponent));
    printf("%d ^ %d = %lu (iterative: O(log n))\n", base, exponent, powerIterative(base, exponent));
    printf("%d ^ %d = %lu (naive: O(n))\n", base, exponent, powerNaive(base, exponent));
}

#ifdef __MINGW64__
// #pragma GCC diagnostic pop
#endif
