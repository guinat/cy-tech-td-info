#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Compile : gcc ex3.c

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

void list_delete_first_match(node_t **head, int key)
{
    node_t *temp = *head, *prev;

    if (temp != NULL && temp->data == key)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;
    free(temp);
}

void list_delete_all_matches(node_t **head, int key)
{
    node_t *temp = *head, *prev;

    while (temp != NULL && temp->data == key)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }

    while (temp != NULL)
    {
        while (temp != NULL && temp->data != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;

        prev->next = temp->next;
        free(temp);

        temp = prev->next;
    }
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
    srand(time(0));
    node_t *head = NULL;
    for (int i = 0; i < 10; i++)
    {
        head = list_insert_start(head, rand() % 6);
    }

    printf("Original list: \n");
    list_display(head);

    list_delete_first_match(&head, 3);
    printf("List after deleting first occurrence of 3: \n");
    list_display(head);

    list_delete_all_matches(&head, 2);
    printf("List after deleting all occurrences of 2: \n");
    list_display(head);

    return 0;
}