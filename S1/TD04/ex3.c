#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Compile : gcc ex3.c

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node, *pNode;

pNode node_create(int data)
{
    pNode node_new = malloc(sizeof(pNode));
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

int is_filiform(pNode tree)
{
    if (tree == NULL)
    {
        return 1;
    }
    if ((tree->left == NULL && tree->right != NULL) || (tree->left != NULL && tree->right == NULL))
    {
        return is_filiform(tree->left) && is_filiform(tree->right);
    }
    return 0;
}

int is_left_comb(pNode tree)
{
    if (tree == NULL)
    {
        return 1;
    }
    if (tree->right != NULL)
    {
        return 0;
    }
    return is_left_comb(tree->left);
}

void tree_display(pNode tree, int level)
{
    if (tree != NULL)
    {
        printf("%d (Level %d)\n", tree->data, level);
        tree_display(tree->left, level + 1);
        tree_display(tree->right, level + 1);
    }
}

pNode construct_left_comb(int height)
{
    if (height <= 0)
    {
        return NULL;
    }
    pNode node_new = node_create(rand() % 11);
    node_new->left = construct_left_comb(height - 1);
    return node_new;
}

int main(void)
{
    srand(time(NULL));

    pNode filiform_tree = node_create(1);
    filiform_tree->left = node_create(2);
    filiform_tree->left->left = node_create(3);

    printf("Is the tree filiform? %s\n", is_filiform(filiform_tree) ? "Yes" : "No");
    printf("Is the tree left comb? %s\n", is_left_comb(filiform_tree) ? "Yes" : "No");

    pNode left_comb_tree = construct_left_comb(5);
    printf("\nLeft Comb Tree:\n");
    tree_display(left_comb_tree, 0);

    printf("\nIs the tree filiform? %s\n", is_filiform(left_comb_tree) ? "Yes" : "No");
    printf("Is the tree left comb? %s\n", is_left_comb(left_comb_tree) ? "Yes" : "No");

    return 0;
}
