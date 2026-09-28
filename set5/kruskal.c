#include <stdio.h>
#include <stdlib.h>

int comparator(const void *p1, const void *p2)
{
    const int *a = (const int *)p1;
    const int *b = (const int *)p2;
    return (a[2] > b[2]) - (a[2] < b[2]);
}

void makeSet(int parent[], int rank[], int V)
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int x)
{
    if (parent[x] != x)
        parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

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
        {
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
    FILE *file = fopen("edges.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int V;
    if (fscanf(file, "%d", &V) != 1)
    {
        printf("Error reading vertex count.\n");
        fclose(file);
        return 1;
    }

    int adj[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            fscanf(file, "%d", &adj[i][j]);
        }
    }
    fclose(file);

    int maxEdges = V * (V - 1) / 2;
    int edge[maxEdges][3];
    int E = 0;

    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (adj[i][j] != 0)
            {
                edge[E][0] = i;
                edge[E][1] = j;
                edge[E][2] = adj[i][j];
                E++;
            }
        }
    }

    int cost = kruskalAlgo(V, E, edge);
    if (cost < 0)
        printf("Graph is disconnected; no spanning tree exists.\n");
    else
        printf("Minimum cost: %d\n", cost);

    return 0;
}