// C Program to Implement Prim's Algorithm

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 5

int minweight(int weight[], bool visited[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false && weight[v] < min)
        {
            min = weight[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[V][V])
{
    int totalCost = 0;

    printf("MST for the graph:\n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i,
               graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("Total cost of MST: %d\n", totalCost);
}

void primMST(int graph[V][V])
{
    int parent[V];
    int weight[V];
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
        weight[i] = INT_MAX;
        visited[i] = false;
    }

    weight[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minweight(weight, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && visited[v] == false && graph[u][v] < weight[v])
            {
                parent[v] = u;
                weight[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main()
{
    int graph[V][V];

    FILE *file = fopen("graph.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file graph.txt\n");
        return 1;
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    primMST(graph);

    return 0;
}

/*  int graph[V][V] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0}};*/