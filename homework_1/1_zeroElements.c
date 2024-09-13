#include <stdio.h>

int countZeroElements(int *array, int length)
{
    int count = 0;
    for (int i = 0; i < length; i++)
        count += array[i] == 0;
    return count;
}

int main()
{
    int array[16] = {0, 1, 2, 3, 0, 0, 8, 9, 0, 0, 0, 1, 2, 3, 4, 0};

    printf("count of zero elements in array is %d\n", countZeroElements(array, 16));
}
