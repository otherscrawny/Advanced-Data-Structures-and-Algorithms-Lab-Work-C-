#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int x)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = x;
    node->left = node->right = NULL;
    return node;
}

typedef struct
{
    Node **items;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->items = (Node **)malloc(sizeof(Node *) * capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, Node *node)
{
    s->items[++(s->top)] = node;
}

Node *pop(Stack *s)
{
    return s->items[(s->top)--];
}

void preOrder(Node *root, int *result, int *resSize)
{
    *resSize = 0;
    if (root == NULL)
        return;

    Stack *s = createStack(MAX);
    push(s, root);

    while (!isEmpty(s))
    {
        Node *curr = pop(s);
        result[(*resSize)++] = curr->data;

        if (curr->right != NULL)
            push(s, curr->right);
        if (curr->left != NULL)
            push(s, curr->left);
    }

    free(s->items);
    free(s);
}

void insertNode(Node **root, int x)
{
    Node *newNode = createNode(x);

    if (*root == NULL)
    {
        *root = newNode;
        printf("Inserted %d as the root.\n", x);
        return;
    }

    Node *curr = *root;
    int choice;

    while (1)
    {
        printf("Currently at node with value %d.\n", curr->data);
        printf("  1. Go Left");
        if (curr->left != NULL)
            printf(" (occupied by %d)", curr->left->data);
        else
            printf(" (empty)");
        printf("\n  2. Go Right");
        if (curr->right != NULL)
            printf(" (occupied by %d)", curr->right->data);
        else
            printf(" (empty)");
        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            /* clear bad input */
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice == 1)
        {
            if (curr->left == NULL)
            {
                curr->left = newNode;
                printf("Inserted %d to the left of %d.\n", x, curr->data);
                return;
            }
            else
            {
                curr = curr->left;
            }
        }
        else if (choice == 2)
        {
            if (curr->right == NULL)
            {
                curr->right = newNode;
                printf("Inserted %d to the right of %d.\n", x, curr->data);
                return;
            }
            else
            {
                curr = curr->right;
            }
        }
        else
        {
            printf("Invalid choice, please enter 1 or 2.\n");
        }
    }
}

void freeTree(Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    Node *root = NULL;
    int menuChoice, value;

    while (1)
    {
        printf("\n===== Binary Tree Menu =====\n");
        printf("1. Insert a value\n");
        printf("2. Print Preorder traversal\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &menuChoice) != 1)
        {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (menuChoice)
        {
        case 1:
            printf("Enter value to insert: ");
            if (scanf("%d", &value) != 1)
            {
                printf("Invalid value.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            insertNode(&root, value);
            break;

        case 2:
        {
            int result[1000];
            int resSize = 0;
            preOrder(root, result, &resSize);
            printf("Preorder: ");
            for (int i = 0; i < resSize; i++)
            {
                printf("%d ", result[i]);
            }
            printf("\n");
            break;
        }

        case 3:
            freeTree(root);
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid menu choice.\n");
        }
    }

    return 0;
}
