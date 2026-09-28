#include <stdio.h>
#include <stdlib.h>

// Structure for Adjacency List Node
struct Node
{
    int dest;
    struct Node *next;
};

// Structure for Queue implementation
struct Queue
{
    int *items;
    int front;
    int rear;
    int capacity;
};

// Queue helper functions
struct Queue *createQueue(int capacity)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->items = (int *)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}

void enqueue(struct Queue *q, int value)
{
    q->items[++(q->rear)] = value;
}

int dequeue(struct Queue *q)
{
    return q->items[(q->front)++];
}

int isEmpty(struct Queue *q)
{
    return q->front > q->rear;
}

void freeQueue(struct Queue *q)
{
    free(q->items);
    free(q);
}

// Topological Sort using Kahn's Algorithm
int *topoSort(struct Node *adj[], int n, int *returnSize)
{
    int *indegree = (int *)calloc(n, sizeof(int));
    struct Queue *q = createQueue(n);
    int *list = (int *)malloc(n * sizeof(int));
    int listIndex = 0;

    // Compute indegrees
    for (int i = 0; i < n; i++)
    {
        struct Node *temp = adj[i];
        while (temp != NULL)
        {
            indegree[temp->dest]++;
            temp = temp->next;
        }
    }

    // Add all nodes with indegree 0 into the queue
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            enqueue(q, i);
        }
    }

    // Kahn’s Algorithm (BFS)
    while (!isEmpty(q))
    {
        int top = dequeue(q);
        list[listIndex++] = top;

        struct Node *temp = adj[top];
        while (temp != NULL)
        {
            int next = temp->dest;
            indegree[next]--;
            if (indegree[next] == 0)
            {
                enqueue(q, next);
            }
            temp = temp->next;
        }
    }

    *returnSize = listIndex;
    free(indegree);
    freeQueue(q);
    return list;
}

void addEdge(struct Node *adj[], int u, int v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

int main()
{
    int n = 6;

    // Allocate adjacency list array
    struct Node **adj = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i = 0; i < n; i++)
    {
        adj[i] = NULL;
    }

    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 1);
    addEdge(adj, 5, 2);

    int returnSize = 0;
    int *res = topoSort(adj, n, &returnSize);

    // Print result
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    // Clean up graph memory
    for (int i = 0; i < n; i++)
    {
        struct Node *temp = adj[i];
        while (temp != NULL)
        {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adj);
    free(res);

    return 0;
}