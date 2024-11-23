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

int main(void) {
    int base = readValue("enter base: ", "incorrect value: base cannot be less than zero; try again: ");
    int exponent = readValue("enter exponent: ", "incorrect value: exponent cannot be less than zero; try again: ");

    printf("%d ^ %d = %lu (recursive: O(log n))\n", base, exponent, powerRecursive(base, exponent));
    printf("%d ^ %d = %lu (iterative: O(log n))\n", base, exponent, powerIterative(base, exponent));
    printf("%d ^ %d = %lu (naive: O(n))\n", base, exponent, powerNaive(base, exponent));
}
