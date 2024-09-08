#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int allocatedLength, pointerPosition;
    char *array;
};

struct Stack *stackCreate()
{
    struct Stack *stack = malloc(sizeof(struct Stack));

    stack->allocatedLength = 4;
    stack->pointerPosition = -1;
    stack->array = malloc(sizeof(char) * stack->allocatedLength);

    return stack;
}

void stackGrow(struct Stack *stack)
{
    stack->allocatedLength *= 2;
    stack->array = realloc(stack->array, stack->allocatedLength);
}

void stackShrink(struct Stack *stack)
{
    stack->allocatedLength /= 2;
    stack->array = realloc(stack->array, stack->allocatedLength);
}

void stackPush(struct Stack *stack, char value)
{
    if (++stack->pointerPosition >= stack->allocatedLength)
        stackGrow(stack);

    stack->array[stack->pointerPosition] = value;
}

char stackPop(struct Stack *stack)
{
    char value = stack->array[stack->pointerPosition--];

    // if pointer is at third of entire allocated memory and allocated memory is pretty high, deallocate second half of it
    if (stack->pointerPosition * 3 < stack->allocatedLength && stack->allocatedLength > 1024)
        stackShrink(stack);

    return value;
}

char stackPeek(struct Stack *stack)
{
    return stack->array[stack->pointerPosition];
}

char stackDispose(struct Stack *stack)
{
    free(stack->array);
    free(stack);
}

int balance(char *string)
{
    struct Stack *stack = stackCreate();

    int result = 0, finished = 1;
    for (int i = 0; string[i] != 0; i++)
    {
        char value = string[i];

        if (value == '(' || value == '{' || value == '[')
            stackPush(stack, value);
        else if (value == ')' || value == '}' || value == ']')
        {
            if (stack->pointerPosition == -1)
            {
                finished = 0;
                break;
            }

            char last = stackPop(stack);

            // in ascii table open and closed braces are two characters apart, parentheses are just nex to each other
            if (value - last < 0 || value - last > 2)
            {
                finished = 0;
                break;
            }
        }
    }

    result = finished && stack->pointerPosition == -1;

    stackDispose(stack);
    return result;
}

int main()
{
    char input[256];

    printf("input string: ");
    scanf("%s", &input);

    printf("given string is %sbalanced\n", balance(input) ? "" : "un");
}
