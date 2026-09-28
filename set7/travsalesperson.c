#include <stdio.h>
#include <limits.h>

#define MAX_N 12

int minCost = INT_MAX;
int bestPath[MAX_N];

void tspRecursive(int curr, int count, int cost, int visited[], int n, int dist[MAX_N][MAX_N], int currPath[])
{
    currPath[count - 1] = curr;

    if (count == n)
    {
        if (dist[curr][0] > 0 && (cost + dist[curr][0] < minCost))
        {
            minCost = cost + dist[curr][0];
        }
        return;
    }

    if (cost >= minCost)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[curr][i] > 0)
        {
            visited[i] = 1;
            tspRecursive(i, count + 1, cost + dist[curr][i], visited, n, dist, currPath);
            visited[i] = 0; // Backtrack
        }
    }
}

int solveTSP(int n, int dist[MAX_N][MAX_N])
{
    int visited[MAX_N] = {0};
    int currPath[MAX_N];

    minCost = INT_MAX;
    visited[0] = 1;

    tspRecursive(0, 1, 0, visited, n, dist, currPath);

    return minCost;
}

int main()
{
    int n = 4;

    int dist[MAX_N][MAX_N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};

    printf("Calculating Optimal TSP Tour for %d cities...\n", n);
    int optimalCost = solveTSP(n, dist);

    printf("Minimum Tour Cost = %d\n", optimalCost);

    return 0;
}