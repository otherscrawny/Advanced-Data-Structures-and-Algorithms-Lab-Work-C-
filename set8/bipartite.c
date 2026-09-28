#include <stdio.h>
#include <stdbool.h>

// Function to check whether assigning the color is safe.
bool isSafe(int node, int clr, int V, int color[], int adjMat[V][V])
{
    // Check all adjacent vertices.
    for (int neigh = 0; neigh < V; neigh++)
    {
        if (adjMat[node][neigh] && color[neigh] == clr)
        {
            return false;
        }
    }
    return true;
}

// Backtracking function.
bool solve(int node, int V, int color[], int adjMat[V][V])
{
    // All vertices are colored.
    if (node == V)
        return true;

    // Skip already colored vertices.
    if (color[node] != -1)
        return solve(node + 1, V, color, adjMat);

    // Try both colors (0 and 1).
    for (int clr = 0; clr <= 1; clr++)
    {
        if (isSafe(node, clr, V, color, adjMat))
        {
            // Assign color.
            color[node] = clr;

            // Recur for next vertex.
            if (solve(node + 1, V, color, adjMat))
                return true;

            // Backtrack.
            color[node] = -1;
        }
    }

    return false;
}

// Function to check if graph is bipartite.
bool isBipartite(int V, int E, int edges[][2])
{
    // Create and initialize adjacency matrix with 0
    int adjMat[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            adjMat[i][j] = 0;
        }
    }

    // Populate adjacency matrix from edges
    for (int i = 0; i < E; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adjMat[u][v] = 1;
        adjMat[v][u] = 1; // Undirected graph
    }

    // -1 means vertex is uncolored.
    int color[V];
    for (int i = 0; i < V; i++)
    {
        color[i] = -1;
    }

    return solve(0, V, color, adjMat);
}

int main()
{
    int V = 5;
    int edges[][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 0}};

    int E = sizeof(edges) / sizeof(edges[0]);
    printf("Vertices (n): %d\n", V);
    printf("Edges (e): %d\n\n", E);
    if (isBipartite(V, E, edges))
        printf("true\n"); // Output: true
    else
        printf("false\n");

    return 0;
}

/*     int edges[][2] = {
        {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}};bipartite:
*/