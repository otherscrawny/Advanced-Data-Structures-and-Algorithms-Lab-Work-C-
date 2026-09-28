#include <stdio.h>
#include <stdlib.h>

// Structure to pair profit and deadline together
typedef struct
{
    int profit;
    int deadline;
} Job;

// Comparison function to sort jobs in descending order of profit
int compare(const void *a, const void *b)
{
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return (j2->profit - j1->profit); // Descending order
}

// Function now returns just the total profit (int)
int jobSequencing(int deadline[], int profit[], int n)
{
    int totProfit = 0;

    // Pair the profit and deadline of all the jobs together
    Job jobs[n];
    for (int i = 0; i < n; i++)
    {
        jobs[i].profit = profit[i];
        jobs[i].deadline = deadline[i];
    }

    // Sort the jobs based on profit in decreasing order
    qsort(jobs, n, sizeof(Job), compare);

    // Slot array initialized to 0 (meaning empty)
    int slot[n];
    for (int i = 0; i < n; i++)
    {
        slot[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int limit = (jobs[i].deadline < n) ? jobs[i].deadline : n;
        for (int j = limit - 1; j >= 0; j--)
        {
            // If slot is empty
            if (slot[j] == 0)
            {
                slot[j] = 1;
                totProfit += jobs[i].profit;
                break;
            }
        }
    }

    return totProfit;
}

int main()
{
    int deadline[] = {2, 1, 2, 1, 1};
    int profit[] = {100, 19, 27, 25, 15};
    int n = sizeof(deadline) / sizeof(deadline[0]);

    int maxProfit = jobSequencing(deadline, profit, n);
    printf("Total Profit: %d\n", maxProfit);

    return 0;
}