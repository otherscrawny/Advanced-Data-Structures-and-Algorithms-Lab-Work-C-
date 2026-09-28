#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Node
{
    int dest;
    struct Node *next;
};

struct Graph
{
    int numVertices;
    struct Node *adjLists[MAX_VERTICES];
};

struct Node *createNode(int dest)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

int findSmallestCycle(struct Graph *graph)
{
    int minCycle = INT_MAX;

    for (int start = 0; start < graph->numVertices; start++)
    {
        int dist[MAX_VERTICES];
        for (int i = 0; i < graph->numVertices; i++)
        {
            dist[i] = -1;
        }

        int queue[MAX_VERTICES];
        int front = 0, rear = 0;

        struct Node *temp = graph->adjLists[start];
        while (temp != NULL)
        {
            int v = temp->dest;
            if (v == start)
                return 1;
            queue[rear++] = v;
            dist[v] = 1;
            temp = temp->next;
        }

        while (front < rear)
        {
            int u = queue[front++];
            if (u == start)
            {
                if (dist[u] < minCycle)
                    minCycle = dist[u];
                break;
            }

            temp = graph->adjLists[u];
            while (temp != NULL)
            {
                int v = temp->dest;
                if (v == start)
                {
                    int currentLength = dist[u] + 1;
                    if (currentLength < minCycle)
                        minCycle = currentLength;
                }
                else if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    queue[rear++] = v;
                }
                temp = temp->next;
            }
        }
    }

    return (minCycle == INT_MAX) ? -1 : minCycle;
}

void dfsLargest(struct Graph *graph, int curr, int start, int currentLength, int *maxCycle, int *visitedInPath)
{
    visitedInPath[curr] = 1;

    struct Node *temp = graph->adjLists[curr];
    while (temp != NULL)
    {
        int v = temp->dest;
        if (v == start)
        {
            if (currentLength > *maxCycle)
            {
                *maxCycle = currentLength;
            }
        }
        else if (!visitedInPath[v])
        {
            dfsLargest(graph, v, start, currentLength + 1, maxCycle, visitedInPath);
        }
        temp = temp->next;
    }

    visitedInPath[curr] = 0;
}

int findLargestCycle(struct Graph *graph)
{
    int maxCycle = -1;
    int visitedInPath[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->numVertices; i++)
    {
        dfsLargest(graph, i, i, 1, &maxCycle, visitedInPath);
    }

    return maxCycle;
}
int main()
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = 4;
    for (int i = 0; i < 4; i++)
        graph->adjLists[i] = NULL;

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 0);

    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);

    int smallest = findSmallestCycle(graph);
    int largest = findLargestCycle(graph);

    printf("Smallest cycle length: %d\n", smallest);
    printf("Largest cycle length: %d\n", largest);

    return 0;
}