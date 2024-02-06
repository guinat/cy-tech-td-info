#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex4.c

typedef struct Node
{
    int data;
    struct node_t *next;
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

node_t *list_insert_start(node_t *head, int data)
{
    node_t *newNode = node_create(data);
    newNode->next = head;
    return newNode;
}

node_t *list_reverse_with_new_list(node_t *head)
{
    node_t *head_new = NULL;
    node_t *current = head;
    while (current != NULL)
    {
        head_new = list_insert_start(head_new, current->data);
        current = current->next;
    }
    return head_new;
}

void list_reverse_in_place(node_t **head)
{
    node_t *prev = NULL;
    node_t *current = *head;
    node_t *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
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
    head = list_insert_start(head, 3);
    head = list_insert_start(head, 2);
    head = list_insert_start(head, 1);

    printf("Original list: \n");
    list_display(head);

    node_t *reversedList = list_reverse_with_new_list(head);
    printf("Reversed list with new list: \n");
    list_display(reversedList);

    list_reverse_in_place(&head);
    printf("Reversed list in place: \n");
    list_display(head);

    return 0;
}