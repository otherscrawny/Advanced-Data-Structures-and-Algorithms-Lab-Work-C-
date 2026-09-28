#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_V 100

bool isSafe(int v, bool graph[MAX_V][MAX_V], int color[], int c, int V)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;

    return true;
}

bool graphColoringUtil(bool graph[MAX_V][MAX_V], int m, int color[], int v, int V)
{
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, graph, color, c, V))
        {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1, V) == true)
                return true;

            color[v] = 0;
        }
    }

    return false;
}

void printSolution(int color[], int V)
{
    printf("Solution Exists: Following are the assigned colors\n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);

    printf("\n");
}

bool graphColoring(bool graph[MAX_V][MAX_V], int m, int V)
{
    int color[MAX_V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(graph, m, color, 0, V) == false)
    {
        printf("Solution does not exist\n");
        return false;
    }

    printSolution(color, V);
    return true;
}

int main()
{
    FILE *file = fopen("graph.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open graph.txt\n");
        return 1;
    }

    int V;
    if (fscanf(file, "%d", &V) != 1 || V <= 0 || V > MAX_V)
    {
        printf("Error: Invalid or missing number of vertices in graph.txt\n");
        fclose(file);
        return 1;
    }

    bool graph[MAX_V][MAX_V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int val;
            if (fscanf(file, "%d", &val) != 1)
            {
                printf("Error: Invalid adjacency matrix data in graph.txt\n");
                fclose(file);
                return 1;
            }
            graph[i][j] = (val != 0);
        }
    }
    fclose(file);

    int m = 3;

    graphColoring(graph, m, V);

    return 0;
}