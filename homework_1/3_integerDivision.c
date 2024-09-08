#include <stdio.h>
#include <stdlib.h>

int integerDivision(int numerator, int denominator)
{
    if (denominator == 0)
    {
        printf("Denominator cannot be 0!\n");
        exit(1);
    }

    int quotient = 0, remainder = numerator, direction = numerator * denominator > 0 ? 1 : -1;

    denominator *= direction;

    while (numerator > 0 ? remainder >= denominator : remainder < 0)
    {
        quotient += direction;
        remainder -= denominator;
    }

    return quotient;
}

int main()
{
    int numeratorInput, denominatorInput;

    printf("input numerator: ");
    scanf("%d", &numeratorInput);

    printf("input denominator: ");
    scanf("%d", &denominatorInput);

    printf("integer division result: %d\n", integerDivision(numeratorInput, denominatorInput));
}
