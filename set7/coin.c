#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

void greedyCoinChange(int coins[], int n, int target)
{
    qsort(coins, n, sizeof(int), compare);

    int totalCoins = 0;
    int remainingTarget = target;

    printf("Target Amount: %d\n", target);
    printf("Coins used: ");

    for (int i = 0; i < n; i++)
    {
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
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 2000};
    int n = sizeof(coins) / sizeof(coins[0]);

    int target = 67;

    greedyCoinChange(coins, n, target);

    return 0;
}