#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

bool isSafe(int vertex, int n, int adjMat[n][n], int path[], int pos)
{
    if (!adjMat[path[pos - 1]][vertex])
    {
        return false;
    }

    for (int i = 0; i < pos; i++)
    {
        if (path[i] == vertex)
        {
            return false;
        }
    }

    return true;
}

bool hamCycleUtil(int n, int adjMat[n][n], int path[], int pos)
{
    if (pos == n)
    {
        return adjMat[path[pos - 1]][path[0]];
    }

    for (int v = 1; v < n; v++)
    {
        if (isSafe(v, n, adjMat, path, pos))
        {
            path[pos] = v;

            if (hamCycleUtil(n, adjMat, path, pos + 1))
            {
                return true;
            }

            path[pos] = -1;
        }
    }

    return false;
}

bool hamCycle(int n, int adjMat[n][n], int path[])
{
    for (int i = 0; i < n; i++)
    {
        path[i] = -1;
    }

    path[0] = 0;

    if (!hamCycleUtil(n, adjMat, path, 1))
    {
        return false;
    }

    return true;
}

int main()
{
    int n = 5;

    int adjMat[5][5] = {0};

    int edges[][2] = {
        {0, 1}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}};
    int e = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adjMat[u][v] = 1;
        adjMat[v][u] = 1;
    }

    printf("--- Hamiltonian Cycle Check ---\n");
    printf("Vertices (n): %d\n", n);
    printf("Edges (e): %d\n\n", e);

    int path[MAX_VERTICES];

    if (!hamCycle(n, adjMat, path))
    {
        printf("Result: Hamiltonian Cycle does not exist.\n");
    }
    else
    {
        printf("Result: Hamiltonian Cycle exists!\nPath: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d -> ", path[i]);
        }
        printf("%d\n", path[0]);
    }

    return 0;
}