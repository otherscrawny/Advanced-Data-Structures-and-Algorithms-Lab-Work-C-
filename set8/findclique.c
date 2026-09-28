#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

int n, e, m;
int adj[MAX_VERTICES][MAX_VERTICES];
int current_clique[MAX_VERTICES];

bool find_clique(int start_vertex, int current_size)
{
    if (current_size == m)
    {
        return true;
    }

    if (n - start_vertex < m - current_size)
    {
        return false;
    }

    for (int i = start_vertex; i < n; i++)
    {
        bool connected_to_all = true;
        for (int j = 0; j < current_size; j++)
        {
            if (!adj[i][current_clique[j]])
            {
                connected_to_all = false;
                break;
            }
        }

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
    n = 4;
    m = 3;

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

    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("--- Static Graph Analysis ---\n");
    printf("Vertices (n): %d\n", n);
    printf("Edges (e): %d\n", e);
    printf("Target Clique Size (m): %d\n\n", m);

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