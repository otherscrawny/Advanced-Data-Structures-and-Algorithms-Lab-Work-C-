#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int infixToPostfix(char *exp)
{
    int len = strlen(exp);
    char result[len + 1];
    char stack[len];
    int j = 0;
    int top = -1;
    printf("Stack init: %s\n", stack);
    for (int i = 0; i < len; i++)
    {
        char c = exp[i];

        if (isalnum(c))
        {
            result[j++] = c;
        }
        else if (c == '(')
        {
            stack[++top] = '(';
        }

        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                result[j++] = stack[top--];
            }
            top--;
        }
        else
        {
            while (top != -1 && stack[top] != '(' && (precedence(stack[top]) > precedence(c) || (precedence(stack[top]) == precedence(c) && !isRightAssociative(c))))
            {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
        printf("debug stack: %s\n", stack);
    }
    while (top != -1)
    {
        result[j++] = stack[top--];
    }

    result[j] = '\0';
    printf("%s\n", result);
}

int main()
{
    int test = 50;
    char exp1[test];
    scanf("%s", exp1);
    infixToPostfix(exp1);
    return 0;
}