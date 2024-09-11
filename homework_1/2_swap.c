#include <stdio.h>

void swap(int *left, int *right)
{
    if (*left == *right)
        return;

    *left ^= *right;
    *right ^= *left;
    *left ^= *right;
}

int main()
{
    int first, second;

    printf("input first number: ");
    scanf("%d", &first);

    printf("input second number: ");
    scanf("%d", &second);

    printf("this pair of numvers is (%d, %d)\n", first, second);

    swap(&first, &second);

    printf("and after swap it became (%d, %d)\n", first, second);
}
