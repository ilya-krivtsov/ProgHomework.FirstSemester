#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int allocatedLength, pointerPosition;
    char *array;
} Stack;

Stack *stackCreate()
{
    Stack *stack = malloc(sizeof(Stack));

    stack->allocatedLength = 4;
    stack->pointerPosition = -1;
    stack->array = malloc(sizeof(char) * stack->allocatedLength);

    return stack;
}

void stackGrow(Stack *stack)
{
    stack->allocatedLength *= 2;
    stack->array = realloc(stack->array, stack->allocatedLength);
}

void stackShrink(Stack *stack)
{
    stack->allocatedLength /= 2;
    stack->array = realloc(stack->array, stack->allocatedLength);
}

void stackPush(Stack *stack, char value)
{
    ++stack->pointerPosition;
    if (stack->pointerPosition >= stack->allocatedLength)
        stackGrow(stack);

    stack->array[stack->pointerPosition] = value;
}

char stackPop(Stack *stack)
{
    --stack->pointerPosition;
    char value = stack->array[stack->pointerPosition];

    // if pointer is at third of entire allocated memory and allocated memory is pretty high, deallocate second half of it
    if (stack->pointerPosition * 3 < stack->allocatedLength && stack->allocatedLength > 1024)
        stackShrink(stack);

    return value;
}

char stackPeek(Stack *stack)
{
    return stack->array[stack->pointerPosition];
}

char stackDispose(Stack *stack)
{
    free(stack->array);
    free(stack);
}

int balance(char *string)
{
    Stack *stack = stackCreate();

    bool finished = true;
    for (int i = 0; string[i] != '\0'; i++)
    {
        char value = string[i];

        if (value == '(' || value == '{' || value == '[')
            stackPush(stack, value);
        else if (value == ')' || value == '}' || value == ']')
        {
            if (stack->pointerPosition == -1)
            {
                finished = false;
                break;
            }

            char last = stackPop(stack);

            if (!(last == '(' && value == ')') || (last == '{' && value == '}') || (last == '[' && value == ']'))
                break;
        }
    }

    bool result = finished && stack->pointerPosition == -1;

    stackDispose(stack);
    return result;
}

int main()
{
    char input[256];

    printf("input string: ");
    scanf("%s", input);

    printf("given string is %sbalanced\n", balance(input) ? "" : "un");
}
