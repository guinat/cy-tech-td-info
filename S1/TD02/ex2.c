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

node_t *stack_push(node_t *top, int x)
{
    node_t *node_new = node_create(x);
    node_new->next = top;
    top = node_new;
    return top;
}

void stack_pop(node_t **top, int *x)
{
    if (*top == NULL)
    {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    node_t *temp = *top;
    *x = temp->data;
    *top = (*top)->next;
    free(temp);
}

void stack_display(node_t *top)
{
    node_t *current = top;
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
    node_t *st_1 = NULL;
    for (int i = 1; i <= 10; i++)
    {
        st_1 = stack_push(st_1, i);
    }
    printf("Top of st_1: %d\n", st_1->data);

    printf("\nst_1: ");
    stack_display(st_1);
    printf("\n");

    node_t *st_even = NULL;
    node_t *st_odd = NULL;

    while (st_1 != NULL)
    {
        int value;
        stack_pop(&st_1, &value);
        if (value % 2 == 0)
        {
            st_even = stack_push(st_even, value);
        }
        else
        {
            st_odd = stack_push(st_odd, value);
        }
    }

    printf("Even stack: ");
    stack_display(st_even);
    printf("\n");

    printf("Odd stack: ");
    stack_display(st_odd);
    printf("\n");

    while (st_1 != NULL)
    {
        int value;
        stack_pop(&st_1, &value);
    }

    while (st_even != NULL)
    {
        int value;
        stack_pop(&st_even, &value);
    }

    while (st_odd != NULL)
    {
        int value;
        stack_pop(&st_odd, &value);
    }

    return 0;
}
