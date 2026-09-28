#include <stdio.h>

#define INF 999999 // Use a large value for infinity (avoiding overflow with INT_MAX)
#define V 4        // Number of vertices in the graph

// Function to print the solution matrix
void printSolution(int dist[V][V])
{
    printf("The following matrix shows the shortest distances between every pair of vertices:\n\n");
    printf("     ");
    for (int i = 0; i < V; i++)
        printf("%7d ", i);
    printf("\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < V; i++)
    {
        printf("%2d | ", i);
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s ", "INF");
            else
                printf("%7d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Implementing Floyd-Warshall algorithm
void floydWarshall(int graph[V][V])
{
    // dist[][] will be the output matrix that eventually has the shortest
    // distances between every pair
    int dist[V][V];

    // Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Add all vertices one by one to the set of intermediate vertices.
    // k is the intermediate vertex
    for (int k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the above source
            for (int j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                // Check for INF to prevent integer overflow
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

int main()
{
    /* Let us create the following weighted graph
          10
       (0)------->(3)
        |         /|\
       5|          | 2
        v          |
       (1)------->(2)
          3           */

    int graph[V][V] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 2},
        {INF, INF, INF, 0}};

    // Print the solution
    floydWarshall(graph);

    return 0;
}