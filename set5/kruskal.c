#include <stdio.h>
#include <stdlib.h>

// qsort comparator: sort edges by weight (ascending)
int comparator(const void *p1, const void *p2)
{
    const int *a = (const int *)p1;
    const int *b = (const int *)p2;
    return (a[2] > b[2]) - (a[2] < b[2]); // overflow-safe
}

void makeSet(int parent[], int rank[], int V)
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find with path compression
int findParent(int parent[], int x)
{
    if (parent[x] != x)
        parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

// Union by rank; u and v must be roots
void unionSet(int u, int v, int parent[], int rank[])
{
    if (rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

// V = number of vertices, E = number of edges
// edge[i] = {u, v, weight}
// Returns the MST cost, or -1 if the graph is disconnected
int kruskalAlgo(int V, int E, int edge[E][3])
{
    qsort(edge, E, sizeof(edge[0]), comparator);

    int parent[V];
    int rank[V];
    makeSet(parent, rank, V);

    int minCost = 0;
    int used = 0;

    for (int i = 0; i < E && used < V - 1; i++)
    {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2)
        { // different components -> no cycle
            unionSet(v1, v2, parent, rank);
            minCost += wt;
            used++;
            printf("Edge %d - %d  (weight %d)\n", edge[i][0], edge[i][1], wt);
        }
    }

    return (used == V - 1) ? minCost : -1;
}

int main(void)
{
    int edge[][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}};
    int E = sizeof(edge) / sizeof(edge[0]);
    int V = 4;

    int cost = kruskalAlgo(V, E, edge);
    if (cost < 0)
        printf("Graph is disconnected; no spanning tree exists.\n");
    else
        printf("Minimum cost: %d\n", cost);
    return 0;
}