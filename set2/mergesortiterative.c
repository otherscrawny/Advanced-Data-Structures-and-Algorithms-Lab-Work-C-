#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    PROCESS,
    MERGE
} FrameType;

typedef struct
{
    int left;
    int right;
    FrameType type;
} Frame;

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *arr1 = malloc(n1 * sizeof(int));
    int *arr2 = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        arr1[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        arr2[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
        arr[k++] = (arr1[i] <= arr2[j]) ? arr1[i++] : arr2[j++];

    while (i < n1)
        arr[k++] = arr1[i++];

    while (j < n2)
        arr[k++] = arr2[j++];

    free(arr1);
    free(arr2);
}

void mergeSortStack(int arr[], int n)
{
    if (n <= 1)
        return;

    int capacity = 4 * n + 4;
    Frame *stack = malloc(capacity * sizeof(Frame));
    int top = 0;

    stack[top++] = (Frame){0, n - 1, PROCESS};

    while (top > 0)
    {
        Frame f = stack[--top]; /* pop */

        if (f.type == PROCESS)
        {
            if (f.left < f.right)
            {
                int mid = (f.left + f.right) / 2;

                stack[top++] = (Frame){f.left, f.right, MERGE};
                stack[top++] = (Frame){mid + 1, f.right, PROCESS};
                stack[top++] = (Frame){f.left, mid, PROCESS};
            }
        }
        else
        {
            int mid = (f.left + f.right) / 2;
            merge(arr, f.left, mid, f.right);
        }
    }

    free(stack);
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

    mergeSortStack(arr, n);
    printArray(arr, n);

    return 0;
}