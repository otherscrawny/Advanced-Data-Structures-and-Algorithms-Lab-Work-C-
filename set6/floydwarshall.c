#include <stdio.h>

#define INF 999999
#define V 4

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

void floydWarshall(int graph[V][V])
{

    int dist[V][V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {

                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printSolution(dist);
}

int main()
{

    int graph[V][V] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 2},
        {INF, INF, INF, 0}};

    // Print the solution
    floydWarshall(graph);

    return 0;
}