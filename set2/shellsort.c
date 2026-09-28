#include <stdio.h>

void shellSort(int arr[], int n)
{
    int gap, j, k;
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (j = gap; j < n; j++)
        {
            for (k = j - gap; k >= 0; k -= gap)
            {
                if (arr[k + gap] >= arr[k])
                    break;
                else
                {
                    int temp;
                    temp = arr[k + gap];
                    arr[k + gap] = arr[k];
                    arr[k] = temp;
                }
            }
        }
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    shellSort(arr, n);
    printArray(arr, n);

    return 0;
}