#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int number)
{
    int upperBound = (int)sqrt(number) + 1;
    for (int i = 2; i < upperBound; i++)
        if (number % i == 0)
            return false;

    return true;
}

int main()
{
    int input;

    printf("input a number: ");
    scanf("%d", &input);

    printf("all prime numbers that are less or equal to %d:\n", input);

    for (int i = 2; i <= input; i++)
        if (isPrime(i))
            printf("%d\n", i);

    if (input < 2)
        printf("note: there are no prime numbers that are less than 2");
}
