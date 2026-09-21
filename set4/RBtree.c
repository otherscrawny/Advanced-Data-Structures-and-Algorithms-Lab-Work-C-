/* Menu-driven Red-Black tree implementation. */
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct TreeNode
{
    int item;
    Color color;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

TreeNode *createTree(void)
{
    return NULL;
}

static Color colorOf(const TreeNode *node)
{
    return node == NULL ? BLACK : node->color;
}

static void setColor(TreeNode *node, Color color)
{
    if (node != NULL)
    {
        node->color = color;
    }
}

static TreeNode *newNode(int item)
{
    TreeNode *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    node->item = item;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

static void rotateLeft(TreeNode **root, TreeNode *node)
{
    TreeNode *right = node->right;
    node->right = right->left;
    if (right->left != NULL)
    {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL)
    {
        *root = right;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right;
    }
    else
    {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

static void rotateRight(TreeNode **root, TreeNode *node)
{
    TreeNode *left = node->left;
    node->left = left->right;
    if (left->right != NULL)
    {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL)
    {
        *root = left;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = left;
    }
    else
    {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

static void insertFixup(TreeNode **root, TreeNode *node)
{
    while (node->parent != NULL && colorOf(node->parent) == RED)
    {
        TreeNode *parent = node->parent;
        TreeNode *grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            TreeNode *uncle = grandparent->right;
            if (colorOf(uncle) == RED)
            {
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    node = parent;
                    rotateLeft(root, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                rotateRight(root, grandparent);
            }
        }
        else
        {
            TreeNode *uncle = grandparent->left;
            if (colorOf(uncle) == RED)
            {
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    node = parent;
                    rotateRight(root, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                rotateLeft(root, grandparent);
            }
        }
    }
    setColor(*root, BLACK);
}

TreeNode *insertItem(TreeNode *root, int item)
{
    TreeNode *parent = NULL;
    TreeNode *current = root;
    TreeNode *node;

    while (current != NULL)
    {
        parent = current;
        if (item < current->item)
        {
            current = current->left;
        }
        else if (item > current->item)
        {
            current = current->right;
        }
        else
        {
            return root;
        }
    }

    node = newNode(item);
    if (node == NULL)
    {
        return root;
    }
    node->parent = parent;
    if (parent == NULL)
    {
        root = node;
    }
    else if (item < parent->item)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }

    insertFixup(&root, node);
    return root;
}

static TreeNode *minimumNode(TreeNode *root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

static void transplant(TreeNode **root, TreeNode *oldNode, TreeNode *newNode)
{
    if (oldNode->parent == NULL)
    {
        *root = newNode;
    }
    else if (oldNode == oldNode->parent->left)
    {
        oldNode->parent->left = newNode;
    }
    else
    {
        oldNode->parent->right = newNode;
    }
    if (newNode != NULL)
    {
        newNode->parent = oldNode->parent;
    }
}

static void deleteFixup(TreeNode **root, TreeNode *node, TreeNode *parent)
{
    while (node != *root && colorOf(node) == BLACK)
    {
        if (node == (parent == NULL ? NULL : parent->left))
        {
            TreeNode *sibling = parent == NULL ? NULL : parent->right;
            if (colorOf(sibling) == RED)
            {
                setColor(sibling, BLACK);
                setColor(parent, RED);
                rotateLeft(root, parent);
                sibling = parent->right;
            }
            if (colorOf(sibling == NULL ? NULL : sibling->left) == BLACK &&
                colorOf(sibling == NULL ? NULL : sibling->right) == BLACK)
            {
                setColor(sibling, RED);
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (colorOf(sibling == NULL ? NULL : sibling->right) == BLACK)
                {
                    setColor(sibling == NULL ? NULL : sibling->left, BLACK);
                    setColor(sibling, RED);
                    if (sibling != NULL)
                    {
                        rotateRight(root, sibling);
                    }
                    sibling = parent->right;
                }
                setColor(sibling, colorOf(parent));
                setColor(parent, BLACK);
                setColor(sibling == NULL ? NULL : sibling->right, BLACK);
                rotateLeft(root, parent);
                node = *root;
                parent = NULL;
            }
        }
        else
        {
            TreeNode *sibling = parent == NULL ? NULL : parent->left;
            if (colorOf(sibling) == RED)
            {
                setColor(sibling, BLACK);
                setColor(parent, RED);
                rotateRight(root, parent);
                sibling = parent->left;
            }
            if (colorOf(sibling == NULL ? NULL : sibling->right) == BLACK &&
                colorOf(sibling == NULL ? NULL : sibling->left) == BLACK)
            {
                setColor(sibling, RED);
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (colorOf(sibling == NULL ? NULL : sibling->left) == BLACK)
                {
                    setColor(sibling == NULL ? NULL : sibling->right, BLACK);
                    setColor(sibling, RED);
                    if (sibling != NULL)
                    {
                        rotateLeft(root, sibling);
                    }
                    sibling = parent->left;
                }
                setColor(sibling, colorOf(parent));
                setColor(parent, BLACK);
                setColor(sibling == NULL ? NULL : sibling->left, BLACK);
                rotateRight(root, parent);
                node = *root;
                parent = NULL;
            }
        }
    }
    setColor(node, BLACK);
}

TreeNode *deleteItem(TreeNode *root, int item)
{
    TreeNode *target = root;
    TreeNode *replacement;
    TreeNode *replacementParent;
    Color removedColor;

    while (target != NULL && target->item != item)
    {
        target = item < target->item ? target->left : target->right;
    }
    if (target == NULL)
    {
        return root;
    }

    replacement = target;
    removedColor = replacement->color;
    if (target->left == NULL)
    {
        replacement = target->right;
        replacementParent = target->parent;
        transplant(&root, target, target->right);
    }
    else if (target->right == NULL)
    {
        replacement = target->left;
        replacementParent = target->parent;
        transplant(&root, target, target->left);
    }
    else
    {
        TreeNode *successor = minimumNode(target->right);
        removedColor = successor->color;
        replacement = successor->right;
        if (successor->parent == target)
        {
            replacementParent = successor;
            if (replacement != NULL)
            {
                replacement->parent = successor;
            }
        }
        else
        {
            replacementParent = successor->parent;
            transplant(&root, successor, successor->right);
            successor->right = target->right;
            successor->right->parent = successor;
        }
        transplant(&root, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
        successor->color = target->color;
    }
    free(target);

    if (removedColor == BLACK)
    {
        deleteFixup(&root, replacement, replacement == NULL ? replacementParent : replacement->parent);
    }
    return root;
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
        printf("%d(%c) ", root->item, root->color == RED ? 'R' : 'B');
        printInOrder(root->right);
    }
}

static void printPreOrder(const TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d(%c) ", root->item, root->color == RED ? 'R' : 'B');
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

static void printMenu(void)
{
    printf("\nRed-Black Tree Menu\n");
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
