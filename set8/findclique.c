#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

int n, e, m;
int adj[MAX_VERTICES][MAX_VERTICES];
int current_clique[MAX_VERTICES];

// Backtracking function to search for a clique of size m
bool find_clique(int start_vertex, int current_size)
{
    // Base case: if we have found a clique of size m
    if (current_size == m)
    {
        return true;
    }

    // Pruning: if remaining vertices are not enough to reach size m
    if (n - start_vertex < m - current_size)
    {
        return false;
    }

    for (int i = start_vertex; i < n; i++)
    {
        // Check if vertex i is connected to all vertices currently in the clique
        bool connected_to_all = true;
        for (int j = 0; j < current_size; j++)
        {
            if (!adj[i][current_clique[j]])
            {
                connected_to_all = false;
                break;
            }
        }

        // If it connects to all existing clique members, add it and recurse
        if (connected_to_all)
        {
            current_clique[current_size] = i;
            if (find_clique(i + 1, current_size + 1))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    // --- STATIC INPUT CONFIGURATION ---
    n = 4; // Number of vertices (0 to 3)
    m = 3; // Target clique size

    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }

    int edges[][2] = {
        {0, 1},
        {1, 2},
        {0, 2},
        {2, 3}};
    e = sizeof(edges) / sizeof(edges[0]);

    // Populate the adjacency matrix from the static edge list
    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1; // Undirected graph
    }
    // ------------------------------------

    printf("--- Static Graph Analysis ---\n");
    printf("Vertices (n): %d\n", n);
    printf("Edges (e): %d\n", e);
    printf("Target Clique Size (m): %d\n\n", m);

    // Search for the clique
    bool exists = find_clique(0, 0);

    if (exists)
    {
        printf("Result: Yes, the graph contains a clique of size %d.\n", m);
        printf("Vertices in the clique: ");
        for (int i = 0; i < m; i++)
        {
            printf("%d ", current_clique[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Result: No, the graph does NOT contain a clique of size %d.\n", m);
    }

    return 0;
}