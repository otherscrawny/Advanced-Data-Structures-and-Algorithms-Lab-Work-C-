#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct
{
    int weight;
    int value;
    double ratio;
} Item;

// Global variable to store the maximum value found so far
int maxVal = 0;

// Comparison function to sort items by value-to-weight ratio in descending order
int compare(const void *a, const void *b)
{
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item2->ratio > item1->ratio)
        return 1;
    if (item2->ratio < item1->ratio)
        return -1;
    return 0;
}

// Bounding function to estimate the upper bound of potential value from current node
double bound(int i, int currentWeight, int currentVal, int W, Item items[], int n)
{
    if (currentWeight >= W)
        return 0;

    double profitBound = currentVal;
    int totalWeight = currentWeight;

    // Greedily include remaining items as much as possible (fractionally)
    while (i < n && totalWeight + items[i].weight <= W)
    {
        totalWeight += items[i].weight;
        profitBound += items[i].value;
        i++;
    }

    // If there is still capacity, take a fraction of the next item
    if (i < n)
        profitBound += (W - totalWeight) * items[i].ratio;

    return profitBound;
}

// Backtracking (Branch and Bound) recursive function
void knapsackBacktrack(int i, int currentWeight, int currentVal, int W, Item items[], int n)
{
    // If weight exceeds capacity, stop this branch
    if (currentWeight > W)
        return;

    // Update maxVal if the current value is higher
    if (currentVal > maxVal)
        maxVal = currentVal;

    // If there are still items left to consider
    if (i < n)
    {
        // OPTIMIZATION (Branch & Bound): Check if the upper bound of this branch
        // can beat the current maxVal. If not, prune (skip) this branch.
        if (bound(i, currentWeight, currentVal, W, items, n) > maxVal)
        {

            // Choice 1: Include the current item
            knapsackBacktrack(i + 1, currentWeight + items[i].weight, currentVal + items[i].value, W, items, n);

            // Choice 2: Exclude the current item
            knapsackBacktrack(i + 1, currentWeight, currentVal, W, items, n);
        }
    }
}

int main()
{
    int wt[] = {10, 20, 30};
    int val[] = {30, 80, 120};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    Item items[n];
    for (int i = 0; i < n; i++)
    {
        items[i].weight = wt[i];
        items[i].value = val[i];
        items[i].ratio = (double)val[i] / wt[i];
    }

    // Sort items by ratio descending (crucial for efficient bounding)
    qsort(items, n, sizeof(Item), compare);

    // Reset maxVal
    maxVal = 0;

    // Start backtracking from index 0
    knapsackBacktrack(0, 0, 0, W, items, n);

    printf("Maximum value in Knapsack (Backtracking) = %d\n", maxVal);

    return 0;
}