#include <stdio.h>

#include <limits.h>

int max_element(int array[], int size)

{

    int max = INT_MIN;

    for (int i = 0; i < size; i++)

    {
        if (array[i] > max)

            max = array[i];
    }
    return max;
}

void Bucket_Sort(int array[], int size)

{
    int max = max_element(array, size);

    int bucket[max + 1];

    for (int i = 0; i <= max; i++)
        bucket[i] = 0;

    for (int i = 0; i < size; i++)
        bucket[array[i]]++;

    int j = 0;

    for (int i = 0; i <= max; i++)
    {
        while (bucket[i] > 0)
        {
            array[j++] = i;
            bucket[i]--;
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
    int arr[] = {9, 4, 3, 8, 10, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    Bucket_Sort(arr, n);
    printArray(arr, n);

    return 0;
}
