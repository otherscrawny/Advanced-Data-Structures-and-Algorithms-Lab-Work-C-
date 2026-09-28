
#include <limits.h>
#include <stdio.h>

#define V 5

int findminDistance(int dist[], int included[])
{
    int min = INT_MAX, min_index;

    // Traverse all vertices to find the vertex with the
    // minimum distance value
    for (int v = 0; v < V; v++)
    {
        if (included[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[])
{
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void DijkstrasAlgo(int graph[V][V], int src)
{

    int dist[V];

    int included[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        included[i] = 0;
    }

    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {

        int u = findminDistance(dist, included);

        included[u] = 1;

        for (int v = 0; v < V; v++)
        {

            if (!included[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist);
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

    DijkstrasAlgo(graph, 0);
    return 0;
}
