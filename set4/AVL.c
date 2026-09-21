/* Menu-driven AVL tree implementation. */
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int item;
    int height;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTree(void)
{
    return NULL;
}

static int nodeHeight(const TreeNode *node)
{
    return node == NULL ? 0 : node->height;
}

static int max(int first, int second)
{
    return first > second ? first : second;
}

static void updateHeight(TreeNode *node)
{
    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
}

static int balanceFactor(const TreeNode *node)
{
    return node == NULL ? 0 : nodeHeight(node->left) - nodeHeight(node->right);
}

static TreeNode *rotateRight(TreeNode *root)
{
    TreeNode *newRoot = root->left;
    TreeNode *subtree = newRoot->right;

    newRoot->right = root;
    root->left = subtree;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

static TreeNode *rotateLeft(TreeNode *root)
{
    TreeNode *newRoot = root->right;
    TreeNode *subtree = newRoot->left;

    newRoot->left = root;
    root->right = subtree;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

static TreeNode *balanceTree(TreeNode *root)
{
    int balance = balanceFactor(root);

    if (balance > 1)
    {
        if (balanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    if (balance < -1)
    {
        if (balanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    return root;
}

TreeNode *insertItem(TreeNode *root, int item)
{
    if (root == NULL)
    {
        TreeNode *newNode = malloc(sizeof(*newNode));
        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            return NULL;
        }
        newNode->item = item;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (item < root->item)
    {
        root->left = insertItem(root->left, item);
    }
    else if (item > root->item)
    {
        root->right = insertItem(root->right, item);
    }
    else
    {
        return root;
    }

    updateHeight(root);
    return balanceTree(root);
}

static TreeNode *smallestNode(TreeNode *root)
{
    TreeNode *current = root;
    while (current != NULL && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

TreeNode *deleteItem(TreeNode *root, int item)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (item < root->item)
    {
        root->left = deleteItem(root->left, item);
    }
    else if (item > root->item)
    {
        root->right = deleteItem(root->right, item);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            TreeNode *child = root->left != NULL ? root->left : root->right;
            free(root);
            return child;
        }

        TreeNode *successor = smallestNode(root->right);
        root->item = successor->item;
        root->right = deleteItem(root->right, successor->item);
    }

    updateHeight(root);
    return balanceTree(root);
}

int searchItem(const TreeNode *root, int item)
{
    while (root != NULL)
    {
        if (item == root->item)
        {
            return 1;
        }
        root = item < root->item ? root->left : root->right;
    }
    return 0;
}

void deleteTree(TreeNode *root)
{
    if (root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

static void printInOrder(const TreeNode *root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->item);
        printInOrder(root->right);
    }
}

static void printPreOrder(const TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->item);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

static void printMenu(void)
{
    printf("\nAVL Tree Menu\n");
    printf("1. Insert item\n");
    printf("2. Delete item\n");
    printf("3. Search item\n");
    printf("4. Display in-order\n");
    printf("5. Display pre-order\n");
    printf("6. Delete tree\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

int main(void)
{
    TreeNode *root = createTree();
    int choice;
    int item;

    for (;;)
    {
        printMenu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice)
        {
        case 1:
            printf("Enter item: ");
            if (scanf("%d", &item) == 1)
            {
                root = insertItem(root, item);
                printf("Item inserted.\n");
            }
            break;
        case 2:
            printf("Enter item: ");
            if (scanf("%d", &item) == 1)
            {
                if (searchItem(root, item))
                {
                    root = deleteItem(root, item);
                    printf("Item deleted.\n");
                }
                else
                {
                    printf("Item not found.\n");
                }
            }
            break;
        case 3:
            printf("Enter item: ");
            if (scanf("%d", &item) == 1)
            {
                printf(searchItem(root, item) ? "Item found.\n" : "Item not found.\n");
            }
            break;
        case 4:
            printf("In-order: ");
            printInOrder(root);
            printf("\n");
            break;
        case 5:
            printf("Pre-order: ");
            printPreOrder(root);
            printf("\n");
            break;
        case 6:
            deleteTree(root);
            root = createTree();
            printf("Tree deleted.\n");
            break;
        case 0:
            deleteTree(root);
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }

    deleteTree(root);
    return 0;
}
