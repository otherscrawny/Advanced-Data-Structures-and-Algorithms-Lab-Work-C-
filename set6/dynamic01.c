#include <stdio.h>

// Utility function to find the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem
int knapsack(int W, int wt[], int val[], int n)
{
    // dp[n + 1][W + 1] stores the subproblem results
    int dp[n + 1][W + 1];

    // Build the table in a bottom-up manner
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // Base case: 0 items or 0 capacity means 0 value
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            // If the weight of the current item is less than or equal to current capacity 'w'
            else if (wt[i - 1] <= w)
            {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            }
            // If the weight of the current item is more than the current capacity 'w'
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right cell contains the maximum value for capacity W and all items
    return dp[n][W];
}

int main()
{
    // Sample weights and values of items
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};

    // Maximum capacity of the knapsack
    int W = 50;

    // Number of items
    int n = sizeof(val) / sizeof(val[0]);

    printf("Maximum value in Knapsack = %d\n", knapsack(W, wt, val, n));

    return 0;
}