// Circular Queue using array
#include <stdio.h>
#include <stdlib.h>

#define N 7
int queue[N];
int front = -1;
int rear = -1;

void enqueue()
{
    int x;
    printf("Enter enqueue value: ");
    scanf("%d", &x);
    if (front == -1 && rear == -1)
    {
        front = rear = 0;
        queue[rear] = x;
    }
    else if ((rear + 1) % N == front)
    {
        printf("Queue is full\n");
    }
    else
    {
        rear = (rear + 1) % N;
        queue[rear] = x;
    }
}

void dequeue()
{
    if ((front == -1) && (rear == -1))
    {
        printf("\nQueue underflow\n");
    }
    else if (front == rear)
    {
        printf("\nDequeued element:%d\n", queue[front]);
        front = -1;
        rear = -1;
    }
    else
    {
        printf("\nDequeued element:%d\n", queue[front]);
        front = (front + 1) % N;
    }
}

void display()
{
    int i = front;
    if (front == -1 && rear == -1)
    {
        printf("Queue Empty\n");
    }
    else
    {
        while (i != rear)
        {
            printf("%d ", queue[i]);
            i = (i + 1) % N;
        }
        printf("%d ", queue[rear]);
    }
    printf("\n");
}

void peek()
{
    if (front == -1 && rear == -1)
    {
        printf("Queue Empty\n");
    }
    else
    {
        printf("Front: %d", queue[front]);
    }
}
int main()
{
    int ch;
    int x;

    while (1)
    {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Peek\n5.Exit");
        printf("\nEnter choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            peek();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\nInvalid Choice");
        }
    }
}