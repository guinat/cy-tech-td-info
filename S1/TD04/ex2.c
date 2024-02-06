#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex2.c

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node, *pNode;

pNode node_create(int data)
{
    pNode node_new = (pNode)malloc(sizeof(pNode));
    if (node_new == NULL)
    {
        perror("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node_new->data = data;
    node_new->left = NULL;
    node_new->right = NULL;
    return node_new;
}

int is_empty(pNode tree)
{
    return tree == NULL;
}

int is_leaf(pNode node)
{
    return node != NULL && node->left == NULL && node->right == NULL;
}

int get_node_data(pNode node)
{
    return node->data;
}

int has_left_child(pNode node)
{
    return node != NULL && node->left != NULL;
}

int has_right_child(pNode node)
{
    return node != NULL && node->right != NULL;
}

void add_left_child(pNode node, int data)
{
    if (node == NULL || node->left != NULL)
    {
        fprintf(stderr, "Error: Cannot add left child\n");
        exit(EXIT_FAILURE);
    }
    node->left = node_create(data);
}

void add_right_child(pNode node, int data)
{
    if (node == NULL || node->right != NULL)
    {
        fprintf(stderr, "Error: Cannot add right child\n");
        exit(EXIT_FAILURE);
    }
    node->right = node_create(data);
}

void pre_order_traversal(pNode tree)
{
    if (tree != NULL)
    {
        printf("%d ", tree->data);
        pre_order_traversal(tree->left);
        pre_order_traversal(tree->right);
    }
}

void post_order_traversal(pNode tree)
{
    if (tree != NULL)
    {
        post_order_traversal(tree->left);
        post_order_traversal(tree->right);
        printf("%d ", tree->data);
    }
}

void in_order_traversal(pNode tree)
{
    if (tree != NULL)
    {
        in_order_traversal(tree->left);
        printf("%d ", tree->data);
        in_order_traversal(tree->right);
    }
}

int count_leaves(pNode tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (is_leaf(tree))
    {
        return 1;
    }
    return count_leaves(tree->left) + count_leaves(tree->right);
}

int tree_size(pNode tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return 1 + tree_size(tree->left) + tree_size(tree->right);
}

int tree_height(pNode tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    int left_height = tree_height(tree->left);
    int right_height = tree_height(tree->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int main(void)
{
    pNode root = node_create(1);
    add_left_child(root, 2);
    add_left_child(root->left, 3);
    add_left_child(root->left->left, 4);
    add_right_child(root->left->left, 5);
    // ...
    printf("Pre-order traversal: ");
    pre_order_traversal(root);
    printf("\n");

    printf("Post-order traversal: ");
    post_order_traversal(root);
    printf("\n");

    printf("In-order traversal: ");
    in_order_traversal(root);
    printf("\n");

    printf("Number of leaf nodes: %d\n", count_leaves(root));
    printf("Size of the tree: %d\n", tree_size(root));
    printf("Height of the tree: %d\n", tree_height(root));

    return 0;
}
