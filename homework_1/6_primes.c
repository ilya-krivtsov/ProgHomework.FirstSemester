#include <stdio.h>
#include <math.h>

int main()
{
    int input, skip = 0;

    printf("input a number: ");
    scanf("%d", &input);
    printf("all prime numbers that are less or equal to %d:\n", input);

    for (int i = 2; i <= input; i++)
    {
        for (int j = 2; j < (int)sqrt(i) + 1; j++)
        {
            if (i % j == 0)
            {
                skip = 1;
                break;
            }
        }
        if (!skip)
            printf("%d\n", i);
    }
}
