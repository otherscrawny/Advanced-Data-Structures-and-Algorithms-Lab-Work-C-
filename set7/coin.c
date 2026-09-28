#include <stdio.h>
#include <stdlib.h>

// Comparison function to sort coins in descending order
int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

// Function to find minimum coins using greedy approach
void greedyCoinChange(int coins[], int n, int target)
{
    // Sort coins in descending order (largest first)
    qsort(coins, n, sizeof(int), compare);

    int totalCoins = 0;
    int remainingTarget = target;

    printf("Target Amount: %d\n", target);
    printf("Coins used: ");

    for (int i = 0; i < n; i++)
    {
        // Pick the largest coin as many times as possible
        while (remainingTarget >= coins[i])
        {
            remainingTarget -= coins[i];
            totalCoins++;
            printf("%d ", coins[i]);
        }
    }

    printf("\nTotal coins required (Greedy) = %d\n", totalCoins);
}

int main()
{
    // Standard coin denominations (e.g., Indian Rupee system)
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 2000};
    int n = sizeof(coins) / sizeof(coins[0]);

    int target = 67; // Amount to change

    greedyCoinChange(coins, n, target);

    return 0;
}