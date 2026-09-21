#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 4 // Maximum degree of the B-tree

struct BTreeNode
{
    int num_keys;                  // Number of keys currently in the node
    int keys[M - 1];               // Array of keys
    struct BTreeNode *children[M]; // Array of child pointers
    bool is_leaf;                  // True if node is a leaf
};

// Function to create a new node
struct BTreeNode *createNode(bool is_leaf)
{
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    for (int i = 0; i < M; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to split a full child node
void splitChild(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);

    newNode->num_keys = M / 2 - 1;

    // Move keys and children to the new node
    for (int i = 0; i < M / 2 - 1; i++)
    {
        newNode->keys[i] = child->keys[i + M / 2];
    }

    if (!child->is_leaf)
    {
        for (int i = 0; i < M / 2; i++)
        {
            newNode->children[i] = child->children[i + M / 2];
        }
    }

    child->num_keys = M / 2 - 1;

    // Shift parent's children to make space for the new node
    for (int i = parent->num_keys; i > index; i--)
    {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    // Shift parent's keys to insert the middle key from the child
    for (int i = parent->num_keys - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[M / 2 - 1];
    parent->num_keys++;
}

// Function to insert a key into a non-full node
void insertNonFull(struct BTreeNode *node, int key)
{
    int i = node->num_keys - 1;

    if (node->is_leaf)
    {
        // Insert key into the sorted order
        while (i >= 0 && node->keys[i] > key)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    }
    else
    {
        // Find the child to insert the key
        while (i >= 0 && node->keys[i] > key)
        {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == M - 1)
        {
            // Split child if it's full
            splitChild(node, i);

            // Determine which of the two children is the new one
            if (node->keys[i] < key)
            {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(struct BTreeNode **root, int key)
{
    struct BTreeNode *node = *root;

    if (node == NULL)
    {
        // Create a new root node
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    }
    else
    {
        if (node->num_keys == M - 1)
        {
            // Split the root if it's full
            struct BTreeNode *new_root = createNode(false);
            new_root->children[0] = node;
            splitChild(new_root, 0);
            *root = new_root;
        }
        insertNonFull(*root, key);
    }
}

// Function to traverse and print the B-tree in-order
void traverse(struct BTreeNode *root)
{
    if (root != NULL)
    {
        int i;
        for (i = 0; i < root->num_keys; i++)
        {
            traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->children[i]);
    }
}

struct BTreeNode *createTree(void)
{
    return NULL;
}

static int findKey(struct BTreeNode *node, int key)
{
    int index = 0;
    while (index < node->num_keys && node->keys[index] < key)
    {
        index++;
    }
    return index;
}

static int getPredecessor(struct BTreeNode *node)
{
    while (!node->is_leaf)
    {
        node = node->children[node->num_keys];
    }
    return node->keys[node->num_keys - 1];
}

static int getSuccessor(struct BTreeNode *node)
{
    while (!node->is_leaf)
    {
        node = node->children[0];
    }
    return node->keys[0];
}

static void borrowFromPrevious(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *sibling = parent->children[index - 1];

    for (int i = child->num_keys; i > 0; i--)
    {
        child->keys[i] = child->keys[i - 1];
    }
    if (!child->is_leaf)
    {
        for (int i = child->num_keys + 1; i > 0; i--)
        {
            child->children[i] = child->children[i - 1];
        }
        child->children[0] = sibling->children[sibling->num_keys];
    }
    child->keys[0] = parent->keys[index - 1];
    parent->keys[index - 1] = sibling->keys[sibling->num_keys - 1];
    child->num_keys++;
    sibling->num_keys--;
}

static void borrowFromNext(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *sibling = parent->children[index + 1];

    child->keys[child->num_keys] = parent->keys[index];
    if (!child->is_leaf)
    {
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    parent->keys[index] = sibling->keys[0];
    for (int i = 1; i < sibling->num_keys; i++)
    {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->is_leaf)
    {
        for (int i = 1; i <= sibling->num_keys; i++)
        {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    child->num_keys++;
    sibling->num_keys--;
}

static void mergeChildren(struct BTreeNode *parent, int index)
{
    struct BTreeNode *left = parent->children[index];
    struct BTreeNode *right = parent->children[index + 1];
    int leftKeys = left->num_keys;

    left->keys[leftKeys] = parent->keys[index];
    for (int i = 0; i < right->num_keys; i++)
    {
        left->keys[leftKeys + 1 + i] = right->keys[i];
    }
    if (!left->is_leaf)
    {
        for (int i = 0; i <= right->num_keys; i++)
        {
            left->children[leftKeys + 1 + i] = right->children[i];
        }
    }
    left->num_keys += right->num_keys + 1;

    for (int i = index + 1; i < parent->num_keys; i++)
    {
        parent->keys[i - 1] = parent->keys[i];
        parent->children[i] = parent->children[i + 1];
    }
    parent->num_keys--;
    free(right);
}

static void fillChild(struct BTreeNode *parent, int index)
{
    if (index > 0 && parent->children[index - 1]->num_keys >= M / 2)
    {
        borrowFromPrevious(parent, index);
    }
    else if (index < parent->num_keys && parent->children[index + 1]->num_keys >= M / 2)
    {
        borrowFromNext(parent, index);
    }
    else if (index < parent->num_keys)
    {
        mergeChildren(parent, index);
    }
    else
    {
        mergeChildren(parent, index - 1);
    }
}

static void deleteKey(struct BTreeNode *node, int key)
{
    int index = findKey(node, key);

    if (index < node->num_keys && node->keys[index] == key)
    {
        if (node->is_leaf)
        {
            for (int i = index + 1; i < node->num_keys; i++)
            {
                node->keys[i - 1] = node->keys[i];
            }
            node->num_keys--;
            return;
        }

        if (node->children[index]->num_keys >= M / 2)
        {
            int predecessor = getPredecessor(node->children[index]);
            node->keys[index] = predecessor;
            deleteKey(node->children[index], predecessor);
        }
        else if (node->children[index + 1]->num_keys >= M / 2)
        {
            int successor = getSuccessor(node->children[index + 1]);
            node->keys[index] = successor;
            deleteKey(node->children[index + 1], successor);
        }
        else
        {
            mergeChildren(node, index);
            deleteKey(node->children[index], key);
        }
        return;
    }

    if (node->is_leaf)
    {
        return;
    }

    bool lastChild = index == node->num_keys;
    if (node->children[index]->num_keys < M / 2)
    {
        fillChild(node, index);
    }
    if (lastChild && index > node->num_keys)
    {
        deleteKey(node->children[index - 1], key);
    }
    else
    {
        deleteKey(node->children[index], key);
    }
}

void createElement(struct BTreeNode **root, int key)
{
    insert(root, key);
}

bool searchElement(const struct BTreeNode *root, int key)
{
    while (root != NULL)
    {
        int index = 0;
        while (index < root->num_keys && root->keys[index] < key)
        {
            index++;
        }
        if (index < root->num_keys && root->keys[index] == key)
        {
            return true;
        }
        root = root->is_leaf ? NULL : root->children[index];
    }
    return false;
}

void deleteElement(struct BTreeNode **root, int key)
{
    if (*root == NULL || !searchElement(*root, key))
    {
        return;
    }

    deleteKey(*root, key);
    if ((*root)->num_keys == 0)
    {
        struct BTreeNode *oldRoot = *root;
        *root = oldRoot->is_leaf ? NULL : oldRoot->children[0];
        free(oldRoot);
    }
}

void deleteTree(struct BTreeNode *root)
{
    if (root != NULL)
    {
        if (!root->is_leaf)
        {
            for (int i = 0; i <= root->num_keys; i++)
            {
                deleteTree(root->children[i]);
            }
        }
        free(root);
    }
}

static void printMenu(void)
{
    printf("\nB-tree Menu\n");
    printf("1. Insert element\n");
    printf("2. Delete element\n");
    printf("3. Search element\n");
    printf("4. Display in-order\n");
    printf("5. Delete tree\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

int main(void)
{
    struct BTreeNode *root = createTree();
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
            printf("In-order: ");
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