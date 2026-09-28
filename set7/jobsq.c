#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int profit;
    int deadline;
} Job;

int compare(const void *a, const void *b)
{
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return (j2->profit - j1->profit);
}

int jobSequencing(int deadline[], int profit[], int n)
{
    int totProfit = 0;

    Job jobs[n];
    for (int i = 0; i < n; i++)
    {
        jobs[i].profit = profit[i];
        jobs[i].deadline = deadline[i];
    }

    qsort(jobs, n, sizeof(Job), compare);

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