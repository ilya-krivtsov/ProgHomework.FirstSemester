#include <stdio.h>

void flip(int *array, int length)
{
    for (int i = 0; i < (length + 1) / 2; i++)
    {
        int t = array[i];
        array[i] = array[length - i - 1];
        array[length - i - 1] = t;
    }
}

void swap(int *array, int firstLength, int secondLength)
{
    flip(array, firstLength);
    flip(&array[firstLength], secondLength);
    flip(array, firstLength + secondLength);
}

void printArray(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d", array[i]);
        if (i != length - 1)
            printf(", ");
    }
    printf("\n");
}

int main()
{
    int array[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    printArray(array, 16);
    swap(array, 9, 7);
    printArray(array, 16);
}
