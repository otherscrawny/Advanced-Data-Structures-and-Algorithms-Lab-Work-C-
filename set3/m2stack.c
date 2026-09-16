#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 20
#define SWAP(T, a, b) \
    do                \
    {                 \
        T tmp = a;    \
        a = b;        \
        b = tmp;      \
    } while (0)
typedef struct Queue
{
    int data[MAX];
    int front;
    int rear;
} Queue;

typedef struct Stack
{
    Queue q1, q2;
} Stack;

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

bool isQueueEmpty(Queue *q)
{
    return q->rear < q->front;
}

bool isQueueFull(Queue *q)
{
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int n)
{
    if (isQueueFull(q))
    {
        printf("\nQueue Overflow!\n");
        return;
    }
    q->data[++(q->rear)] = n;
}

int dequeue(Queue *q)
{
    if (isQueueEmpty(q))
        return -1;
    int val = q->data[q->front];
    (q->front)++;
    if (q->front > q->rear)
    {
        q->front = 0;
        q->rear = -1;
    }
    return val;
}

void initStack(Stack *s)
{
    initQueue(&s->q1);
    initQueue(&s->q2);
}

bool isStackEmpty(Stack *s)
{
    return isQueueEmpty(&s->q1);
}

void push(Stack *s, int n)
{
    enqueue(&s->q1, n);
}

int pop(Stack *s)
{
    if (isQueueEmpty(&s->q1))
        return -1;

    while (s->q1.front < s->q1.rear)
    {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int topVal = dequeue(&s->q1);

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return topVal;
}

void display(Stack *s)
{
    if (isQueueEmpty(&s->q1))
    {
        printf("\nStack is empty!\n");
        return;
    }
    printf("\nStack (top -> bottom): ");
    for (int i = s->q1.rear; i >= s->q1.front; i--)
    {
        printf("%d ", s->q1.data[i]);
    }
    printf("\n");
}

int main()
{
    int ch;
    Stack s;
    initStack(&s);

    while (1)
    {
        printf("\n*** Stack (2-Queue, M1) Menu ***");
        printf("\n1.Push\n2.Pop\n3.Display\n4.Peek\n5.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
        {
            int x;
            printf("Enter data to push: ");
            scanf("%d", &x);
            push(&s, x);
            break;
        }
        case 2:
        {
            int d = pop(&s);
            if (d != -1)
                printf("\nPopped: %d\n", d);
            else
                printf("\nStack is empty!\n");
            break;
        }
        case 3:
            display(&s);
            break;
        case 4:
        {
            int f = peek(&s);
            if (f != -1)
                printf("\nTop element: %d\n", f);
            else
                printf("\nStack is empty!\n");
            break;
        }
        case 5:
            exit(0);
        default:
            printf("\nWrong Choice!!\n");
        }
    }
    return 0;
}
