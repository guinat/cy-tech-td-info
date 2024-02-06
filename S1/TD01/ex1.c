#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Compile : gcc ex1.c -lm

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

node_t *list_insert_start(node_t *head, int data)
{
    node_t *newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

node_t *list_insert_end(node_t *head, int x)
{
    node_t *node_new = node_create(x);
    node_t *current = head;

    if (head == NULL)
        return node_new;

    while (current->next != NULL)
        current = current->next;

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
    int size;

    printf("Enter the size of the list of powers of two: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        head = list_insert_end(head, pow(2, i));
    }

    printf("List of powers of two:\n");
    list_display(head);

    char choice;
    printf("Do you want to see the next power of two (y/n)? ");
    scanf(" %c", &choice);

    while (choice == 'y' || choice == 'Y')
    {
        head = list_insert_end(head, pow(2, size));
        size++;
        printf("List of powers of two:\n");
        list_display(head);
        printf("Do you want to see the next power of two (y/n)? ");
        scanf(" %c", &choice);
    }

    node_t *current = head;
    while (current != NULL)
    {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}