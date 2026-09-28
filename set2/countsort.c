#include <stdio.h>
#include <stdlib.h>

void countsort(int arr[], int n)
{
    int maxval = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxval)
        {
            maxval = arr[i];
        }
    }

    int *cntArr = (int *)calloc(maxval + 1, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        cntArr[arr[i]]++;
    }

    for (int i = 1; i <= maxval; i++)
    {
        cntArr[i] += cntArr[i - 1];
    }

    int *ans = (int *)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--)
    {
        ans[cntArr[arr[i]] - 1] = arr[i];
        cntArr[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = ans[i];
    }

    free(cntArr);
    free(ans);
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {9, 4, 3, 8, 10, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    countsort(arr, n);
    printArray(arr, n);

    return 0;
}
