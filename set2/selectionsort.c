#include <stdio.h>

#define SWAP(T, a, b) \
    do                \
    {                 \
        T tmp = a;    \
        a = b;        \
        b = tmp;      \
    } while (0)
void selectionSort(int arr[], int n)
{
    int mindex = 0;
    for (int i = 0; i < n; i++)
    {
        mindex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[mindex] > arr[j])
                mindex = j;
        }
        SWAP(int, arr[mindex], arr[i]);
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

    selectionSort(arr, n);
    printArray(arr, n);

    return 0;
}