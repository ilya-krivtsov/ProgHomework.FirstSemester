#include <stdio.h>

int main()
{
    int sums[28], count = 0;

    for (int i = 0; i < 28; i++)
        sums[i] = 0;

    for (int i = 0; i < 1000; i++)
        sums[((i / 100) % 10) + ((i / 10) % 10) + (i % 10)]++;

    for (int i = 0; i < 28; i++)
        count += sums[i] * sums[i];

    printf("Total count of lucky tickets is %d\n", count);
}
