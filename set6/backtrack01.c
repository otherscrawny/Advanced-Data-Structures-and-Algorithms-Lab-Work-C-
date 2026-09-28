#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int weight;
    int value;
    double ratio;
} Item;

int maxVal = 0;

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

double bound(int i, int currentWeight, int currentVal, int W, Item items[], int n)
{
    if (currentWeight >= W)
        return 0;

    double profitBound = currentVal;
    int totalWeight = currentWeight;

    while (i < n && totalWeight + items[i].weight <= W)
    {
        totalWeight += items[i].weight;
        profitBound += items[i].value;
        i++;
    }

    if (i < n)
        profitBound += (W - totalWeight) * items[i].ratio;

    return profitBound;
}

void knapsackBacktrack(int i, int currentWeight, int currentVal, int W, Item items[], int n)
{
    if (currentWeight > W)
        return;

    if (currentVal > maxVal)
        maxVal = currentVal;

    if (i < n)
    {

        if (bound(i, currentWeight, currentVal, W, items, n) > maxVal)
        {

            knapsackBacktrack(i + 1, currentWeight + items[i].weight, currentVal + items[i].value, W, items, n);

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

    qsort(items, n, sizeof(Item), compare);

    maxVal = 0;

    knapsackBacktrack(0, 0, 0, W, items, n);

    printf("Maximum value in Knapsack (Backtracking) = %d\n", maxVal);

    return 0;
}