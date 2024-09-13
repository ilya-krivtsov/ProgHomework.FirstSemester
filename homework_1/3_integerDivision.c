#include <stdio.h>
#include <stdbool.h>

bool integerDivision(int numerator, int denominator, int *quotient)
{
    if (denominator == 0)
        return false;

    int remainder = numerator, direction = numerator * denominator > 0 ? 1 : -1;

    *quotient = 0;
    denominator *= direction;

    while (numerator > 0 ? remainder >= denominator : remainder < 0)
    {
        *quotient += direction;
        remainder -= denominator;
    }

    return true;
}

int main()
{
    int numeratorInput, denominatorInput, divisionResult;

    printf("input numerator: ");
    scanf("%d", &numeratorInput);

    printf("input denominator: ");
    scanf("%d", &denominatorInput);

    if (integerDivision(numeratorInput, denominatorInput, &divisionResult))
        printf("integer division result: %d\n", divisionResult);
    else
        printf("division failed: denominator was 0\n");
}
