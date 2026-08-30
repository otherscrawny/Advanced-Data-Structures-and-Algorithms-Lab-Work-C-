#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    int top;
    unsigned capacity;
    int *array;
} Stack;

typedef struct
{
    int top;
    unsigned capacity;
    char *array;
} StringStack;
int tokenize(char *line, char *arr[], int max)
{
    int n = 0;
    int len = strlen(line);
    int i = 0;

    while (i < len && n < max)
    {
        char c = line[i];

        if (isspace((unsigned char)c))
        {
            i++;
            continue;
        }

        if (isdigit((unsigned char)c))
        {
            int start = i;
            while (i < len && isdigit((unsigned char)line[i]))
                i++;
            int tokLen = i - start;
            char *tok = (char *)malloc(tokLen + 1);
            strncpy(tok, line + start, tokLen);
            tok[tokLen] = '\0';
            arr[n++] = tok;
        }
        else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            char *tok = (char *)malloc(2);
            tok[0] = c;
            tok[1] = '\0';
            arr[n++] = tok;
            i++;
        }
        else
        {
            i++;
        }
    }
    return n;
}

int applyOperation(int a, int b, char *op)
{
    if (strcmp(op, "+") == 0)
        return a + b;
    if (strcmp(op, "-") == 0)
        return a - b;
    if (strcmp(op, "*") == 0)
        return a * b;

    if (strcmp(op, "/") == 0)
    {
        if (a * b < 0 && a % b != 0)
            return (a / b) - 1;
        return a / b;
    }

    if (strcmp(op, "^") == 0)
        return (int)pow(a, b);
    return 0;
}

int precedence(char *op)
{
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    if (strcmp(op, "^") == 0)
        return 3;
    return 0;
}

bool isRightAssociative(char *op)
{
    return (strcmp(op, "^") == 0);
}

bool isNumber(char *token)
{
    if (token == NULL || *token == '\0')
        return false;
    int start = (token[0] == '-') ? 1 : 0;
    if (start == 1 && strlen(token) == 1)
        return false;
    for (int i = start; token[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)token[i]))
            return false;
    }
    return true;
}

Stack *createStack(unsigned capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

StringStack *createStringStack(unsigned capacity)
{
    StringStack *stack = (StringStack *)malloc(sizeof(StringStack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char *)malloc(stack->capacity * sizeof(char) * MAX);
    return stack;
}

void push(Stack *stack, int item)
{
    stack->array[++stack->top] = item;
}

void pushString(StringStack *stack, char *item)
{
    strcpy(stack->array + (stack->top + 1) * MAX, item);
    stack->top++;
}

int pop(Stack *stack)
{
    return stack->array[stack->top--];
}

char *popString(StringStack *stack)
{
    char *item = (char *)malloc(MAX * sizeof(char));
    strcpy(item, stack->array + stack->top * MAX);
    stack->top--;
    return item;
}

int peek(Stack *stack)
{
    return stack->array[stack->top];
}

char *peekString(StringStack *stack)
{
    char *item = (char *)malloc(MAX * sizeof(char));
    strcpy(item, stack->array + stack->top * MAX);
    return item;
}

bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

bool isEmptyString(StringStack *stack)
{
    return stack->top == -1;
}

int evaluateInfix(char **arr, int n)
{
    Stack *values = createStack(n);
    StringStack *ops = createStringStack(n);

    for (int i = 0; i < n; i++)
    {

        // printf("token: '%s'\n", arr[i]);
        if (isNumber(arr[i]))
        {
            push(values, atoi(arr[i]));
        }

        else if (strcmp(arr[i], "(") == 0)
        {
            pushString(ops, arr[i]);
        }

        else if (strcmp(arr[i], ")") == 0)
        {
            while (!isEmptyString(ops) && strcmp(peekString(ops), "(") != 0)
            {
                int val2 = pop(values);
                int val1 = pop(values);
                char *op = popString(ops);
                push(values, applyOperation(val1, val2, op));
            }
            popString(ops);
        }

        else
        {
            while (!isEmptyString(ops) && strcmp(peekString(ops), "(") != 0 &&
                   (precedence(peekString(ops)) > precedence(arr[i]) ||
                    (precedence(peekString(ops)) == precedence(arr[i]) && !isRightAssociative(arr[i]))))
            {
                int val2 = pop(values);
                int val1 = pop(values);
                char *op = popString(ops);
                push(values, applyOperation(val1, val2, op));
            }
            pushString(ops, arr[i]);
        }
    }

    while (!isEmptyString(ops))
    {
        int val2 = pop(values);
        int val1 = pop(values);
        char *op = popString(ops);
        push(values, applyOperation(val1, val2, op));
    }

    return peek(values);
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

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        if (strlen(line) == 0)
        {
            continue;
        }

        char *arr[MAX];
        int n = tokenize(line, arr, MAX);

        if (n == 0)
        {
            continue;
        }
        printf("Input: %s\t", line);
        printf("Result: %d\n", evaluateInfix(arr, n));
    }

    fclose(fp);
    return 0;
}