#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char *data;
    int top;
} Stack;

int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int isRightAssociative(char c)
{
    return c == '^';
}

void push(Stack *s, char c)
{
    s->data[++(s->top)] = c;
}

char pop(Stack *s)
{
    return s->data[(s->top)--];
}

char stackTop(Stack *s)
{
    return s->data[s->top];
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int infixToPostfix(char *exp)
{
    int len = strlen(exp);
    char result[len + 1];
    char stackArr[len];

    Stack stack;
    stack.data = stackArr;
    stack.top = -1;

    int j = 0;

    for (int i = 0; i < len; i++)
    {
        char c = exp[i];

        if (isalnum(c))
        {
            result[j++] = c;
        }
        else if (c == '(')
        {
            push(&stack, '(');
        }
        else if (c == ')')
        {
            while (!isEmpty(&stack) && stackTop(&stack) != '(')
            {
                result[j++] = pop(&stack);
            }
            pop(&stack);
        }
        else
        {
            while (!isEmpty(&stack) && stackTop(&stack) != '(' &&
                   (precedence(stackTop(&stack)) > precedence(c) ||
                    (precedence(stackTop(&stack)) == precedence(c) && !isRightAssociative(c))))
            {
                result[j++] = pop(&stack);
            }
            push(&stack, c);
        }
    }

    while (!isEmpty(&stack))
    {
        result[j++] = pop(&stack);
    }

    result[j] = '\0';
    printf("Result: %s\n", result);
}

int main()
{
    char filename[] = "infixinput.txt";

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Strip trailing newline, if present
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Skip empty lines
        if (strlen(line) == 0)
        {
            continue;
        }
        printf("input: %s\t", line);
        infixToPostfix(line);
    }

    fclose(fp);
    return 0;
}