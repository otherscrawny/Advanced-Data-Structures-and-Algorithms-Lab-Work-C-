#include <stdio.h>
#define SWAP(T, a, b) \
    do                \
    {                 \
        T tmp = a;    \
        a = b;        \
        b = tmp;      \
    } while (0)

int digit(int value, int bit)
{
    return (value >> bit) & 1;
}

int get_MSB(int arr[], int n)
{
    if (n <= 0)
        return -1;
    int max_val = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    int bit = 0;
    while (max_val >> 1)
    {
        bit++;
        max_val >>= 1;
    }
    return bit;
}

void radixExSort(int a[], int l, int r, int bit)
{
    if (r <= l || bit < 0)
        return;

    int i = l, j = r;
    while (j != i)
    {
        while (digit(a[i], bit) == 0 && (i < j))
            i++;
        while (digit(a[j], bit) == 1 && (j > i))
            j--;
        SWAP(int, a[i], a[j]);
    }
    if (digit(a[r], bit) == 0)
        j++;
    radixExSort(a, l, j - 1, bit - 1);
    radixExSort(a, j, r, bit - 1);
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
    radixExSort(arr, 0, n - 1, get_MSB(arr, n));
    printArray(arr, n);
    return 0;
}