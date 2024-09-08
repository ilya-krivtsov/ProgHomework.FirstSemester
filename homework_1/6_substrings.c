#include <stdio.h>

int countSubstrings(char *string, char *substring)
{
    int count = 0, skipToEnd = 0, skipIteration = 0;

    for (int i = 0; string[i] != 0; i++)
    {
        for (int j = 0; substring[j] != 0; j++)
        {
            char stringChar = string[i + j];

            if (stringChar == 0)
            {
                skipToEnd = 1;
                break;
            }

            if (stringChar != substring[j])
            {
                skipIteration = 1;
                break;
            }
        }

        if (skipToEnd)
            break;

        if (!skipIteration)
            count++;
    }

    return count;
}

int main()
{
    char first[256], second[256];

    printf("input first string: ");
    scanf("%s", &first);
    printf("input second string: ");
    scanf("%s", &second);

    printf("\"%s\" appears in \"%s\" %d times\n", second, first, countSubstrings(first, second));
}
