#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex2.c

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} node_t;

node_t *node_create(int data)
{
    node_t *node_new = malloc(sizeof(node_t));
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

int search(node_t *root, int data)
{
    if (root == NULL)
        return 0;
    if (root->data == data)
        return 1;
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

node_t *insert(node_t *root, int data)
{
    if (root == NULL)
        return node_create(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

node_t *insert_iterative(node_t *root, int data)
{
    node_t *new_node = node_create(data);
    if (root == NULL)
        return new_node;
    node_t *current = root;
    node_t *parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else
        {
            free(new_node);
            return root;
        }
    }
    if (data < parent->data)
        parent->left = new_node;
    else
        parent->right = new_node;
    return root;
}

node_t *minimum_data_node(node_t *node)
{
    node_t *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

node_t *delete_node(node_t *root, int data)
{
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = delete_node(root->left, data);
    else if (data > root->data)
        root->right = delete_node(root->right, data);
    else
    {
        if (root->left == NULL)
        {
            node_t *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node_t *temp = root->left;
            free(root);
            return temp;
        }
        node_t *temp = minimum_data_node(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

void display(node_t *root)
{
    if (root != NULL)
    {
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

int search_2(node_t *root, int data, int *node_count)
{
    if (root == NULL)
    {
        printf("The searched element does not exist. ");
        return *node_count;
    }
    (*node_count)++;
    if (root->data == data)
    {
        printf("Number of nodes visited: %d. ", *node_count);
        return *node_count;
    }
    if (data < root->data)
        return search_2(root->left, data, node_count);
    else
        return search_2(root->right, data, node_count);
}

int prefix_traversal_search(node_t *root, int data, int *node_count)
{
    if (root == NULL)
    {
        printf("The searched element does not exist. ");
        return *node_count;
    }
    (*node_count)++;
    if (root->data == data)
    {
        printf("Number of nodes visited: %d. ", *node_count);
        return *node_count;
    }
    int left = prefix_traversal_search(root->left, data, node_count);
    if (left != -1)
        return left;
    return prefix_traversal_search(root->right, data, node_count);
}

int is_binary_tree(node_t *root, node_t *minNode, node_t *maxNode)
{
    if (root == NULL)
        return 1;

    if ((minNode != NULL && root->data <= minNode->data) || (maxNode != NULL && root->data >= maxNode->data))
        return 0;

    return is_binary_tree(root->left, minNode, root) && is_binary_tree(root->right, root, maxNode);
}

int main(void)
{
    node_t *root = NULL;
    root = insert(root, 10);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 12);
    root = insert(root, 7);
    root = insert(root, 45);
    root = insert(root, 9);

    printf("Binary Search Tree: ");
    display(root);
    printf("\n");

    printf("Element 13 : %s\n", search(root, 13) ? "Present" : "Absent");
    printf("Element 12 : %s\n", search(root, 12) ? "Present" : "Absent");

    root = delete_node(root, 15);

    printf("Binary Search Tree after deletion of 15: ");
    display(root);
    printf("\n");

    return 0;
}
