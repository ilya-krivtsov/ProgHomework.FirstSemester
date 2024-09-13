#include <stdio.h>
#include <stdbool.h>

int countSubstrings(char *string, char *substring)
{
    int count = 0;
    bool skipToEnd = false, skipIteration = false;

    for (int i = 0; string[i] != '\0'; i++)
    {
        skipIteration = false;

        for (int j = 0; substring[j] != '\0'; j++)
        {
            char stringChar = string[i + j];

            if (stringChar == '\0')
            {
                skipToEnd = true;
                break;
            }

            if (stringChar != substring[j])
            {
                skipIteration = true;
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
    scanf("%s", first);
    printf("input second string: ");
    scanf("%s", second);

    printf("\"%s\" appears in \"%s\" %d times\n", second, first, countSubstrings(first, second));
}
