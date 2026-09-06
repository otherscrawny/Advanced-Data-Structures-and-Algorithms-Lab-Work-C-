#include <stdio.h>
#include <math.h>
int min(int a, int b)
{
    return a < b ? a : b;
}
void merge(int arr[], int left, int mid, int right)
{

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int arr1[n1], arr2[n2];

    for (int i = 0; i < n1; i++)
        arr1[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        arr2[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (arr1[i] <= arr2[j])
        {
            arr[k] = arr1[i];
            i++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n)
{

    for (int currSize = 1; currSize <= n - 1;
         currSize = 2 * currSize)
    {

        for (int leftStart = 0; leftStart < n - 1;
             leftStart += 2 * currSize)
        {

            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);

            merge(arr, leftStart, mid, rightEnd);
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
    mergeSort(arr, n);
    printArray(arr, n);
    return 0;
}