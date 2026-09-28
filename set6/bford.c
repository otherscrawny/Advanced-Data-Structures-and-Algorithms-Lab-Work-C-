#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct
{
    int source;
    int destination;
    int weight;
} Edge;

void bellmanFord(Edge edges[], int vertices, int edgeCount, int source)
{
    int distance[vertices];

    for (int i = 0; i < vertices; ++i)
        distance[i] = INF;

    distance[source] = 0;

    for (int i = 0; i < vertices - 1; ++i)
    {
        for (int j = 0; j < edgeCount; ++j)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int w = edges[j].weight;

            if (distance[u] != INF && distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
            }
        }
    }

    for (int i = 0; i < edgeCount; ++i)
    {
        int u = edges[i].source;
        int v = edges[i].destination;
        int w = edges[i].weight;

        if (distance[u] != INF && distance[v] > distance[u] + w)
        {
            printf("Negative cycle detected\n");
            return;
        }
    }

    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < vertices; ++i)
    {
        if (distance[i] == INF)
            printf("%d \t\t INF\n", i);
        else
            printf("%d \t\t %d\n", i, distance[i]);
    }
}

int main()
{
    int vertices = 6;
    int edgeCount = 8;

    Edge edges[8] = {
        {0, 1, 5},
        {0, 2, 7},
        {1, 2, 3},
        {1, 3, 4},
        {1, 4, 6},
        {3, 4, -1},
        {3, 5, 2},
        {4, 5, -3}};

    bellmanFord(edges, vertices, edgeCount, 0);

    return 0;
}