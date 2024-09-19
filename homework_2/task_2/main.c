#include <stdio.h>

long long powerRecursive(long long base, long long exponent) {
    if (exponent == 0) {
        return 1;
    }

    long long result = powerRecursive(base, exponent / 2);
    result *= result;
    return exponent % 2 == 0 ? result : result * base;
}

long long powerIterative(long long base, long long exponent) {
    long long result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        exponent /= 2;
        base *= base;
    }

    return result;
}

long long powerNaiive(long long base, long long exponent) {
    long long result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

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
