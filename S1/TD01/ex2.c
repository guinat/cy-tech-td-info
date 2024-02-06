#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex2.c

typedef struct Node
{
    int data;
    struct Node *next;
} node_t;

node_t *node_create(int x)
{
    node_t *node_new = malloc(sizeof(node_t));
    if (!node_new)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node_new->data = x;
    node_new->next = NULL;

    return node_new;
}

node_t *list_insert_sorted(node_t *head, int x)
{
    node_t *node_new = node_create(x);
    node_t *current = head;

    if (!head || x <= head->data)
    {
        node_new->next = head;
        return node_new;
    }

    while (current->next && current->next->data < x)
        current = current->next;

    node_new->next = current->next;
    current->next = node_new;

    return head;
}

void list_display(node_t *head)
{
    node_t *current = head;
    while (current != NULL)
    {
        printf("[%d]", current->data);
        if (current->next != NULL)
            printf(" -> ");
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    node_t *head = NULL;
    int value, num_elements;

    printf("Enter the number of elements in the sorted list: ");
    scanf("%d", &num_elements);

    printf("Enter %d sorted elements: ", num_elements);
    for (int i = 0; i < num_elements; i++)
    {
        scanf("%d", &value);
        head = list_insert_sorted(head, value);
    }

    printf("Sorted Linked List:\n");
    list_display(head);

    node_t *current = head;
    while (current)
    {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
