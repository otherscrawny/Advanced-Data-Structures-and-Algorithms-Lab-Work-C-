#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define SIZE 10
// ==================== MACROS ====================
#define SWAP(T, a, b) \
    do                \
    {                 \
        T tmp = a;    \
        a = b;        \
        b = tmp;      \
    } while (0)

// ==================== UTILITY FUNCTIONS ====================
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// ==================== BUBBLE SORT ====================
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (arr[i] < arr[j])
                SWAP(int, arr[i], arr[j]);
        }
    }
}

// ==================== BUCKET SORT ====================
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

// ==================== COUNT SORT ====================
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

// ==================== HEAP SORT ====================
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        SWAP(int,arr[i],arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        SWAP(int,arr[0],arr[i]);
        heapify(arr, i, 0);
    }
}

// ==================== INSERTION SORT ====================
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ==================== QUICK SORT ====================
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            SWAP(int, arr[i], arr[j]);
        }
    }

    SWAP(int, arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==================== SELECTION SORT ====================
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

// ==================== RADIX EXCHANGE SORT ====================
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

// ==================== RADIX SORT ====================
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void radixCountSort(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n)
{
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        radixCountSort(arr, n, exp);
}

// ==================== SHELL SORT ====================
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
                    SWAP(int,arr[k+gap],arr[k]
                }
            }
        }
    }
}

typedef struct Node
{
    int data;
    struct Node *nextNode;
} Node;

typedef struct
{
    Node *head;
} LinkedList;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

LinkedList *createLinkedList(void)
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void insert(LinkedList *list, int data)
{
    Node *newNode = createNode(data);


    if (list->head == NULL || data < list->head->data)
    {
        newNode->nextNode = list->head;
        list->head = newNode;
    }
    else
    {
        Node *current = list->head;
        while (current->nextNode != NULL && current->nextNode->data < data)
        {
            current = current->nextNode;
        }

        newNode->nextNode = current->nextNode;
        current->nextNode = newNode;
    }
}

void freeLinkedList(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->nextNode;
        free(temp);
    }
    free(list);
}

int hashFunction(int num, int maximum)
{
    int address = (int)(((double)num / maximum) * (SIZE - 1));
    return address;
}

void addressCalculationSort(int arr[], int n)
{
    LinkedList *listOfLinkedLists[SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        listOfLinkedLists[i] = createLinkedList();
    }

    int maximum = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > maximum)
        {
            maximum = arr[i];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int address = hashFunction(arr[i], maximum);
        insert(listOfLinkedLists[address], arr[i]);
    }

    for (int i = 0; i < SIZE; ++i)
    {
        Node *current = listOfLinkedLists[i]->head;
        printf("ADDRESS %d: ", i);

        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->nextNode;
        }

        printf("\n");
    }

    int index = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        Node *current = listOfLinkedLists[i]->head;

        while (current != NULL)
        {
            arr[index] = current->data;
            index++;
            current = current->nextNode;
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        freeLinkedList(listOfLinkedLists[i]);
    }
}

// ==================== MAIN FUNCTION ====================
int main()
{
    FILE *file = fopen("array.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could not open array.txt\n");
        return 1;
    }

    // First, count the number of elements
    int n = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1)
    {
        n++;
    }

    if (n <= 0)
    {
        printf("Error: array.txt is empty or invalid.\n");
        fclose(file);
        return 1;
    }

    // Reset file pointer to beginning
    rewind(file);

    // Allocate memory for arrays
    int *arr = (int *)malloc(n * sizeof(int));
    int *test_arr = (int *)malloc(n * sizeof(int));

    // Read array elements from file
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    printf("=== Sorting Algorithm Demonstration ===\n");
    printf("Original array: ");
    printArray(arr, n);
    printf("\n");

    // Bubble Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    bubbleSort(test_arr, n);
    printf("Bubble Sort: ");
    printArray(test_arr, n);

    // Bucket Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    Bucket_Sort(test_arr, n);
    printf("Bucket Sort: ");
    printArray(test_arr, n);

    // Count Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    countsort(test_arr, n);
    printf("Count Sort: ");
    printArray(test_arr, n);

    // Heap Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    heapSort(test_arr, n);
    printf("Heap Sort: ");
    printArray(test_arr, n);

    // Insertion Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    insertionSort(test_arr, n);
    printf("Insertion Sort: ");
    printArray(test_arr, n);

    // Quick Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    quickSort(test_arr, 0, n - 1);
    printf("Quick Sort: ");
    printArray(test_arr, n);

    // Selection Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    selectionSort(test_arr, n);
    printf("Selection Sort: ");
    printArray(test_arr, n);

    // Radix Exchange Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    radixExSort(test_arr, 0, n - 1, get_MSB(test_arr, n));
    printf("Radix Exchange Sort: ");
    printArray(test_arr, n);

    // Radix Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    radixSort(test_arr, n);
    printf("Radix Sort: ");
    printArray(test_arr, n);

    // Shell Sort
    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    shellSort(test_arr, n);
    printf("Shell Sort: ");
    printArray(test_arr, n);

    for (int i = 0; i < n; i++)
        test_arr[i] = arr[i];
    addressCalculationSort(test_arr, n);
    printf("Address calculation Sort: ");
    printArray(test_arr, n);

    free(arr);
    free(test_arr);

    return 0;
}
