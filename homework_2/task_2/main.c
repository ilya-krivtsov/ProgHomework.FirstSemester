#include <stdio.h>

#include "power.h"

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf(prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf(incorrectValueMessage);
    }
}

int main(void) {
    int base = readValue("enter base: ", "incorrect value: base cannot be less than zero; try again: ");
    int exponent = readValue("enter exponent: ", "incorrect value: exponent cannot be less than zero; try again: ");

    printf("%d ^ %d = %lld (recursive: O(log n))\n", base, exponent, powerRecursive(base, exponent));
    printf("%d ^ %d = %lld (iterative: O(log n))\n", base, exponent, powerIterative(base, exponent));
    printf("%d ^ %d = %lld (naiive: O(n))\n", base, exponent, powerNaiive(base, exponent));
}
