#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 20

typedef struct Stack
{
    int data[MAX];
    int top;
} Stack;

typedef struct Queue
{
    Stack s1, s2;
} Queue;

void initStack(Stack *s)
{
    s->top = -1;
}

bool isStackEmpty(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, int n)
{
    s->data[++(s->top)] = n;
}

int pop(Stack *s)
{
    return s->data[(s->top)--];
}

int peek(Stack *s)
{
    return s->data[s->top];
}
void initQueue(Queue *q)
{
    initStack(&(q->s1));
    initStack(&(q->s2));
}

void enqueue(Queue *q, int n)
{
    while (!isStackEmpty(&(q->s1)))
    {
        push(&q->s2, pop(&q->s1));
    }
    push(&q->s1, n);
    while (!isStackEmpty(&q->s2))
    {
        push(&q->s1, pop(&q->s2));
    }
}

int dequeue(Queue *q)
{
    if (isStackEmpty(&q->s1))
        return -1;
    return pop(&q->s1);
}

int front(Queue *q)
{
    if (isStackEmpty(&q->s1))
    {
        return -1;
    }
    return peek(&q->s1);
}

void display(Queue *q)
{
    if (isStackEmpty(&q->s1))
    {
        printf("\nQueue is empty!\n");
        return;
    }
    printf("\nQueue (front -> rear): ");
    for (int i = q->s1.top; i >= 0; i--)
    {
        printf("%d ", q->s1.data[i]);
    }
    printf("\n");
}

int main()
{
    int ch;
    Queue q;
    initQueue(&q);
    while (1)
    {

        printf("\n*** Queue Menu ***");
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Peek\n5.Exit");
        printf("\nEnter your choice(1-4):");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            int x;
            printf("Enter Data to be Enqueued\n");
            scanf("%d", &x);
            enqueue(&q, x);
            break;
        case 2:
            int d = dequeue(&q);
            if (d != -1)
                printf("\nDequeued: %d\n", d);
            break;
        case 3:
            display(&q);
            break;
        case 4:
            int f = front(&q);
            if (f != -1)
                printf("\nFront element: %d\n", f);
            else
                printf("\nQueue is empty!\n");
            break;
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\nWrong Choice!!");
        }
    }
    return 0;
}