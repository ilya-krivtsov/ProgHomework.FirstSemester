#include <stdio.h>

int countTickets()
{
    int sums[28] = {0}, count = 0;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                sums[i + j + k]++;

    for (int i = 0; i < 28; i++)
        count += sums[i] * sums[i];

    return count;
}

int main()
{
    printf("Total count of lucky tickets is %d\n", countTickets());
}
