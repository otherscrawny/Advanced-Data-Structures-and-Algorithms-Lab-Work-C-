/* Self-contained order-4 B+ tree implementation. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 4
#define MAX_KEYS (M - 1)
#define MIN_LEAF_KEYS ((MAX_KEYS + 1) / 2)
#define MIN_CHILDREN ((M + 1) / 2)

typedef struct BPlusTreeNode
{
    int num_keys;
    int keys[M];
    struct BPlusTreeNode *children[M + 1];
    struct BPlusTreeNode *next;
    bool is_leaf;
} BPlusTreeNode;

typedef struct
{
    bool split;
    int separator;
    BPlusTreeNode *right;
} SplitResult;

static BPlusTreeNode *createNode(bool is_leaf)
{
    BPlusTreeNode *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node->num_keys = 0;
    node->is_leaf = is_leaf;
    node->next = NULL;
    for (int i = 0; i <= M; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

BPlusTreeNode *createTree(void)
{
    return NULL;
}

static BPlusTreeNode *leftmostLeaf(BPlusTreeNode *root)
{
    while (root != NULL && !root->is_leaf)
    {
        root = root->children[0];
    }
    return root;
}

static int firstKey(const BPlusTreeNode *node)
{
    while (!node->is_leaf)
    {
        node = node->children[0];
    }
    return node->keys[0];
}

static void refreshSeparators(BPlusTreeNode *node)
{
    if (node == NULL || node->is_leaf)
    {
        return;
    }
    for (int i = 0; i <= node->num_keys; i++)
    {
        refreshSeparators(node->children[i]);
    }
    for (int i = 0; i < node->num_keys; i++)
    {
        node->keys[i] = firstKey(node->children[i + 1]);
    }
}

static SplitResult insertRecursive(BPlusTreeNode *node, int key)
{
    SplitResult result = {false, 0, NULL};
    int index;

    if (node->is_leaf)
    {
        int values[M];
        index = 0;
        while (index < node->num_keys && node->keys[index] < key)
        {
            index++;
        }
        for (int i = 0; i < index; i++)
        {
            values[i] = node->keys[i];
        }
        values[index] = key;
        for (int i = index; i < node->num_keys; i++)
        {
            values[i + 1] = node->keys[i];
        }

        if (node->num_keys < MAX_KEYS)
        {
            node->num_keys++;
            for (int i = 0; i < node->num_keys; i++)
            {
                node->keys[i] = values[i];
            }
            return result;
        }

        BPlusTreeNode *right = createNode(true);
        node->num_keys = M / 2;
        right->num_keys = M - node->num_keys;
        for (int i = 0; i < node->num_keys; i++)
        {
            node->keys[i] = values[i];
        }
        for (int i = 0; i < right->num_keys; i++)
        {
            right->keys[i] = values[node->num_keys + i];
        }
        right->next = node->next;
        node->next = right;
        result.split = true;
        result.separator = right->keys[0];
        result.right = right;
        return result;
    }

    index = 0;
    while (index < node->num_keys && key >= node->keys[index])
    {
        index++;
    }
    result = insertRecursive(node->children[index], key);
    if (!result.split)
    {
        return result;
    }

    if (node->num_keys < MAX_KEYS)
    {
        for (int i = node->num_keys; i > index; i--)
        {
            node->keys[i] = node->keys[i - 1];
            node->children[i + 1] = node->children[i];
        }
        node->keys[index] = result.separator;
        node->children[index + 1] = result.right;
        node->num_keys++;
        result.split = false;
        return result;
    }

    int keys[M];
    BPlusTreeNode *children[M + 1];
    for (int i = 0; i < index; i++)
    {
        keys[i] = node->keys[i];
    }
    keys[index] = result.separator;
    for (int i = index; i < node->num_keys; i++)
    {
        keys[i + 1] = node->keys[i];
    }
    for (int i = 0; i <= index; i++)
    {
        children[i] = node->children[i];
    }
    children[index + 1] = result.right;
    for (int i = index + 1; i <= node->num_keys; i++)
    {
        children[i + 1] = node->children[i];
    }

    BPlusTreeNode *right = createNode(false);
    int middle = M / 2;
    node->num_keys = middle;
    for (int i = 0; i < node->num_keys; i++)
    {
        node->keys[i] = keys[i];
        node->children[i] = children[i];
    }
    node->children[node->num_keys] = children[node->num_keys];
    right->num_keys = M - middle - 1;
    for (int i = 0; i < right->num_keys; i++)
    {
        right->keys[i] = keys[middle + 1 + i];
        right->children[i] = children[middle + 1 + i];
    }
    right->children[right->num_keys] = children[M];
    result.split = true;
    result.separator = keys[middle];
    result.right = right;
    return result;
}

void createElement(BPlusTreeNode **root, int key)
{
    if (*root == NULL)
    {
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }

    SplitResult result = insertRecursive(*root, key);
    if (result.split)
    {
        BPlusTreeNode *newRoot = createNode(false);
        newRoot->keys[0] = result.separator;
        newRoot->num_keys = 1;
        newRoot->children[0] = *root;
        newRoot->children[1] = result.right;
        *root = newRoot;
    }
    refreshSeparators(*root);
}

bool searchElement(const BPlusTreeNode *root, int key)
{
    while (root != NULL && !root->is_leaf)
    {
        int index = 0;
        while (index < root->num_keys && key >= root->keys[index])
        {
            index++;
        }
        root = root->children[index];
    }
    if (root == NULL)
    {
        return false;
    }
    for (int i = 0; i < root->num_keys; i++)
    {
        if (root->keys[i] == key)
        {
            return true;
        }
    }
    return false;
}

static void borrowLeafFromLeft(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *leaf = parent->children[index];
    BPlusTreeNode *left = parent->children[index - 1];
    for (int i = leaf->num_keys; i > 0; i--)
    {
        leaf->keys[i] = leaf->keys[i - 1];
    }
    leaf->keys[0] = left->keys[left->num_keys - 1];
    leaf->num_keys++;
    left->num_keys--;
}

static void borrowLeafFromRight(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *leaf = parent->children[index];
    BPlusTreeNode *right = parent->children[index + 1];
    leaf->keys[leaf->num_keys++] = right->keys[0];
    for (int i = 1; i < right->num_keys; i++)
    {
        right->keys[i - 1] = right->keys[i];
    }
    right->num_keys--;
}

static void mergeLeaf(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *left = parent->children[index];
    BPlusTreeNode *right = parent->children[index + 1];
    for (int i = 0; i < right->num_keys; i++)
    {
        left->keys[left->num_keys + i] = right->keys[i];
    }
    left->num_keys += right->num_keys;
    left->next = right->next;
    free(right);
    for (int i = index + 1; i < parent->num_keys; i++)
    {
        parent->children[i] = parent->children[i + 1];
    }
    parent->num_keys--;
}

static void borrowInternalFromLeft(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *node = parent->children[index];
    BPlusTreeNode *left = parent->children[index - 1];
    for (int i = node->num_keys; i > 0; i--)
    {
        node->keys[i] = node->keys[i - 1];
    }
    for (int i = node->num_keys + 1; i > 0; i--)
    {
        node->children[i] = node->children[i - 1];
    }
    node->children[0] = left->children[left->num_keys];
    node->keys[0] = parent->keys[index - 1];
    parent->keys[index - 1] = left->keys[left->num_keys - 1];
    left->num_keys--;
    node->num_keys++;
}

static void borrowInternalFromRight(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *node = parent->children[index];
    BPlusTreeNode *right = parent->children[index + 1];
    node->keys[node->num_keys] = parent->keys[index];
    node->children[node->num_keys + 1] = right->children[0];
    parent->keys[index] = right->keys[0];
    for (int i = 1; i < right->num_keys; i++)
    {
        right->keys[i - 1] = right->keys[i];
    }
    for (int i = 1; i <= right->num_keys; i++)
    {
        right->children[i - 1] = right->children[i];
    }
    right->num_keys--;
    node->num_keys++;
}

static void mergeInternal(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *left = parent->children[index];
    BPlusTreeNode *right = parent->children[index + 1];
    int offset = left->num_keys;
    left->keys[offset] = parent->keys[index];
    for (int i = 0; i < right->num_keys; i++)
    {
        left->keys[offset + 1 + i] = right->keys[i];
    }
    for (int i = 0; i <= right->num_keys; i++)
    {
        left->children[offset + 1 + i] = right->children[i];
    }
    left->num_keys += right->num_keys + 1;
    free(right);
    for (int i = index + 1; i < parent->num_keys; i++)
    {
        parent->children[i] = parent->children[i + 1];
    }
    parent->num_keys--;
}

static void rebalanceChild(BPlusTreeNode *parent, int index)
{
    BPlusTreeNode *child = parent->children[index];
    int minimum = child->is_leaf ? MIN_LEAF_KEYS : MIN_CHILDREN - 1;
    if (child->num_keys >= minimum || parent->num_keys == 0)
    {
        return;
    }

    if (index > 0 && parent->children[index - 1]->num_keys > minimum)
    {
        if (child->is_leaf)
        {
            borrowLeafFromLeft(parent, index);
        }
        else
        {
            borrowInternalFromLeft(parent, index);
        }
    }
    else if (index < parent->num_keys && parent->children[index + 1]->num_keys > minimum)
    {
        if (child->is_leaf)
        {
            borrowLeafFromRight(parent, index);
        }
        else
        {
            borrowInternalFromRight(parent, index);
        }
    }
    else if (index > 0)
    {
        if (child->is_leaf)
        {
            mergeLeaf(parent, index - 1);
        }
        else
        {
            mergeInternal(parent, index - 1);
        }
    }
    else
    {
        if (child->is_leaf)
        {
            mergeLeaf(parent, index);
        }
        else
        {
            mergeInternal(parent, index);
        }
    }
}

static bool deleteRecursive(BPlusTreeNode *node, int key)
{
    if (node->is_leaf)
    {
        int index = 0;
        while (index < node->num_keys && node->keys[index] < key)
        {
            index++;
        }
        if (index == node->num_keys || node->keys[index] != key)
        {
            return false;
        }
        for (int i = index + 1; i < node->num_keys; i++)
        {
            node->keys[i - 1] = node->keys[i];
        }
        node->num_keys--;
        return true;
    }

    int index = 0;
    while (index < node->num_keys && key >= node->keys[index])
    {
        index++;
    }
    if (!deleteRecursive(node->children[index], key))
    {
        return false;
    }
    rebalanceChild(node, index);
    return true;
}

void deleteElement(BPlusTreeNode **root, int key)
{
    if (*root == NULL || !searchElement(*root, key))
    {
        return;
    }
    deleteRecursive(*root, key);
    if (!(*root)->is_leaf && (*root)->num_keys == 0)
    {
        BPlusTreeNode *oldRoot = *root;
        *root = oldRoot->children[0];
        free(oldRoot);
    }
    if (*root != NULL)
    {
        refreshSeparators(*root);
    }
}

void deleteTree(BPlusTreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    if (!root->is_leaf)
    {
        for (int i = 0; i <= root->num_keys; i++)
        {
            deleteTree(root->children[i]);
        }
    }
    free(root);
}

static void traverse(BPlusTreeNode *root)
{
    BPlusTreeNode *leaf = leftmostLeaf(root);
    while (leaf != NULL)
    {
        for (int i = 0; i < leaf->num_keys; i++)
        {
            printf("%d ", leaf->keys[i]);
        }
        leaf = leaf->next;
    }
}

static void printMenu(void)
{
    printf("\nB+ Tree Menu\n");
    printf("1. Insert element\n");
    printf("2. Delete element\n");
    printf("3. Search element\n");
    printf("4. Display elements\n");
    printf("5. Delete tree\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

int main(void)
{
    BPlusTreeNode *root = createTree();
    int choice;
    int key;

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
            printf("Enter element: ");
            if (scanf("%d", &key) == 1)
            {
                createElement(&root, key);
                printf("Element inserted.\n");
            }
            break;
        case 2:
            printf("Enter element: ");
            if (scanf("%d", &key) == 1)
            {
                if (searchElement(root, key))
                {
                    deleteElement(&root, key);
                    printf("Element deleted.\n");
                }
                else
                {
                    printf("Element not found.\n");
                }
            }
            break;
        case 3:
            printf("Enter element: ");
            if (scanf("%d", &key) == 1)
            {
                printf(searchElement(root, key) ? "Element found.\n" : "Element not found.\n");
            }
            break;
        case 4:
            printf("Elements: ");
            traverse(root);
            printf("\n");
            break;
        case 5:
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
