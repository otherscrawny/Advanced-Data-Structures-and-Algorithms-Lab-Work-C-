#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

// Check if it's valid to place vertex at current position
bool isSafe(int vertex, int n, int adjMat[n][n], int path[], int pos)
{
    // The vertex must be adjacent to the previous vertex
    if (!adjMat[path[pos - 1]][vertex])
    {
        return false;
    }

    // The vertex must not already be in the path
    for (int i = 0; i < pos; i++)
    {
        if (path[i] == vertex)
        {
            return false;
        }
    }

    return true;
}

// Recursive backtracking to construct Hamiltonian Cycle
bool hamCycleUtil(int n, int adjMat[n][n], int path[], int pos)
{
    // Base case: all vertices are in the path
    if (pos == n)
    {
        // Check if there's an edge from last to first vertex
        return adjMat[path[pos - 1]][path[0]];
    }

    // Try all possible vertices as next candidate
    for (int v = 1; v < n; v++)
    {
        if (isSafe(v, n, adjMat, path, pos))
        {
            path[pos] = v;

            if (hamCycleUtil(n, adjMat, path, pos + 1))
            {
                return true;
            }

            // Backtrack if v doesn't lead to a solution
            path[pos] = -1;
        }
    }

    return false;
}

// Initialize path and invoke backtracking function
bool hamCycle(int n, int adjMat[n][n], int path[])
{
    for (int i = 0; i < n; i++)
    {
        path[i] = -1;
    }

    // Start path with vertex 0
    path[0] = 0;

    if (!hamCycleUtil(n, adjMat, path, 1))
    {
        return false;
    }

    return true;
}

int main()
{
    // --- STATIC INPUT CONFIGURATION ---
    int n = 5; // Number of vertices (0 to 4)

    // Adjacency matrix initialization
    int adjMat[5][5] = {0};

    // Predefined edges (e edges)
    int edges[][2] = {
        {0, 1}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}};
    int e = sizeof(edges) / sizeof(edges[0]);

    // Populate adjacency matrix from edges
    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adjMat[u][v] = 1;
        adjMat[v][u] = 1; // Undirected graph
    }
    // ------------------------------------

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
        printf("%d\n", path[0]); // Complete the cycle back to start
    }

    return 0;
}