#include <stdio.h>

#include "bracketsBalance.h"

int main(void) {
    printf("input string: ");
    char buffer[1024] = { 0 };

    if (scanf("%1023s", buffer) != 1) {
        printf("reading string failed\n");
        return 1;
    }

    switch (checkIfBracketsBalanced(buffer))
    {
    case BALANCED:
        printf("brackets are balanced\n");
        break;

    case UNBALANCED:
        printf("brackets are unbalanced\n");
        break;

    case ALLOCATION_FAILED:
        printf("allocation failed\n");
        return 1;
    }
}
