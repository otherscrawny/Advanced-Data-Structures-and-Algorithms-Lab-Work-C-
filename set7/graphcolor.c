#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_V 100 // Maximum number of vertices allowed

/* A utility function to check if the current color assignment
   is safe for vertex v */
bool isSafe(int v, bool graph[MAX_V][MAX_V], int color[], int c, int V)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;

    return true;
}

/* A recursive utility function to solve m coloring problem */
bool graphColoringUtil(bool graph[MAX_V][MAX_V], int m, int color[], int v, int V)
{
    /* Base case: If all vertices are assigned a color then return true */
    if (v == V)
        return true;

    /* Consider this vertex v and try different colors */
    for (int c = 1; c <= m; c++)
    {
        /* Check if assignment of color c to v is fine */
        if (isSafe(v, graph, color, c, V))
        {
            color[v] = c;

            /* Recur to assign colors to rest of the vertices */
            if (graphColoringUtil(graph, m, color, v + 1, V) == true)
                return true;

            /* If assigning color c doesn't lead to a solution then remove it */
            color[v] = 0;
        }
    }

    /* If no color can be assigned to this vertex then return false */
    return false;
}

/* A utility function to print solution */
void printSolution(int color[], int V)
{
    printf("Solution Exists: Following are the assigned colors\n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);

    printf("\n");
}

/* This function solves the m Coloring problem using Backtracking */
bool graphColoring(bool graph[MAX_V][MAX_V], int m, int V)
{
    // Initialize all color values as 0
    int color[MAX_V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    // Call graphColoringUtil() for vertex 0
    if (graphColoringUtil(graph, m, color, 0, V) == false)
    {
        printf("Solution does not exist\n");
        return false;
    }

    // Print the solution
    printSolution(color, V);
    return true;
}

// Driver code
int main()
{
    FILE *file = fopen("graph.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open graph.txt\n");
        return 1;
    }

    int V;
    if (fscanf(file, "%d", &V) != 1 || V <= 0 || V > MAX_V)
    {
        printf("Error: Invalid or missing number of vertices in graph.txt\n");
        fclose(file);
        return 1;
    }

    bool graph[MAX_V][MAX_V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int val;
            if (fscanf(file, "%d", &val) != 1)
            {
                printf("Error: Invalid adjacency matrix data in graph.txt\n");
                fclose(file);
                return 1;
            }
            graph[i][j] = (val != 0);
        }
    }
    fclose(file);

    // Number of colors
    int m = 3;

    // Function call
    graphColoring(graph, m, V);

    return 0;
}