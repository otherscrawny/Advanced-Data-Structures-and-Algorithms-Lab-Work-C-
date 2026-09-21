#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Graph representation using adjacency list
struct Node
{
    int dest;
    struct Node *next;
};

struct Graph
{
    int numVertices;
    struct Node *adjLists[MAX_NODES];
};

// Function to create a graph
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 1. Find Smallest Cycle (Girth) using BFS
int findSmallestCycle(struct Graph *graph)
{
    int minCycle = INT_MAX;

    for (int i = 0; i < graph->numVertices; i++)
    {
        int dist[MAX_NODES];
        int parent[MAX_NODES];
        for (int j = 0; j < graph->numVertices; j++)
        {
            dist[j] = -1;
            parent[j] = -1;
        }

        int queue[MAX_NODES];
        int front = 0, rear = 0;

        queue[rear++] = i;
        dist[i] = 0;

        while (front < rear)
        {
            int u = queue[front++];
            struct Node *temp = graph->adjLists[u];

            while (temp != NULL)
            {
                int v = temp->dest;
                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    queue[rear++] = v;
                }
                else if (parent[u] != v)
                {
                    // Back edge found, calculate cycle length
                    int cycleLen = dist[u] + dist[v] + 1;
                    if (cycleLen < minCycle)
                    {
                        minCycle = cycleLen;
                    }
                }
                temp = temp->next;
            }
        }
    }
    return (minCycle == INT_MAX) ? -1 : minCycle;
}

// 2. Find Largest Cycle using DFS Backtracking
void dfsLargest(struct Graph *graph, int curr, int start, int visited[], int depth, int *maxCycle)
{
    visited[curr] = 1;

    struct Node *temp = graph->adjLists[curr];
    while (temp != NULL)
    {
        int v = temp->dest;
        if (v == start && depth >= 3)
        {
            if (depth > *maxCycle)
            {
                *maxCycle = depth;
            }
        }
        else if (!visited[v])
        {
            dfsLargest(graph, v, start, visited, depth + 1, maxCycle);
        }
        temp = temp->next;
    }
    visited[curr] = 0;
}

int findLargestCycle(struct Graph *graph)
{
    int maxCycle = -1;
    int visited[MAX_NODES] = {0};

    for (int i = 0; i < graph->numVertices; i++)
    {
        dfsLargest(graph, i, i, visited, 1, &maxCycle);
    }
    return maxCycle;
}

int main()
{
    struct Graph *graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 0);
    addEdge(graph, 0, 2);

    int smallest = findSmallestCycle(graph);
    int largest = findLargestCycle(graph);

    printf("Smallest Cycle Length: %d\n", smallest);
    printf("Largest Cycle Length: %d\n", largest);

    return 0;
}