#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex2.c

typedef struct Pancake
{
    int diameter;
    struct Pancake *next;
} pancake_t;

pancake_t *pancake_create(int diameter)
{
    pancake_t *pancake_new = malloc(sizeof(pancake_t));
    if (pancake_new == NULL)
    {
        perror("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    pancake_new->diameter = diameter;
    pancake_new->next = NULL;

    return pancake_new;
}

pancake_t *push(pancake_t *stack, pancake_t *pancake)
{
    pancake->next = stack;
    return pancake;
}

pancake_t *pop(pancake_t *stack, pancake_t **pancake_t)
{
    if (stack == NULL)
    {
        *pancake_t = NULL;
        return NULL;
    }
    *pancake_t = stack;
    stack = stack->next;
    (*pancake_t)->next = NULL;
    return stack;
}

void stack_display(pancake_t *stack)
{
    pancake_t *current = stack;
    while (current != NULL)
    {
        printf("%d\n", current->diameter);
        current = current->next;
    }
    printf("____\n");
}

void pancake_sort(pancake_t **stack)
{
    pancake_t *sorted_stack = NULL;

    while (*stack != NULL)
    {
        pancake_t *current_pancake;
        *stack = pop(*stack, &current_pancake);

        if (sorted_stack == NULL || current_pancake->diameter < sorted_stack->diameter)
        {
            sorted_stack = push(sorted_stack, current_pancake);
        }
        else
        {
            pancake_t *temp_stack = NULL;
            while (sorted_stack != NULL && current_pancake->diameter > sorted_stack->diameter)
            {
                pancake_t *temp_pancake;
                sorted_stack = pop(sorted_stack, &temp_pancake);
                temp_stack = push(temp_stack, temp_pancake);
            }
            sorted_stack = push(sorted_stack, current_pancake);
            while (temp_stack != NULL)
            {
                pancake_t *temp_pancake;
                temp_stack = pop(temp_stack, &temp_pancake);
                sorted_stack = push(sorted_stack, temp_pancake);
            }
        }
    }

    *stack = sorted_stack;
}

int main(void)
{
    pancake_t *stack = NULL;
    int num_pancakes;

    printf("Enter the number of pancake_ts: ");
    scanf("%d", &num_pancakes);

    if (num_pancakes <= 0)
    {
        printf("Invalid input. The number of pancake_ts should be greater than 0.\n");
        return 1;
    }

    printf("Enter the diameter of each pancake_t:\n");
    for (int i = 0; i < num_pancakes; i++)
    {
        int diameter;
        scanf("%d", &diameter);
        pancake_t *pancake_t = pancake_create(diameter);
        stack = push(stack, pancake_t);
    }

    printf("Initial stack of pancake_ts:\n");
    stack_display(stack);

    pancake_sort(&stack);

    printf("Sorted stack of pancake_ts:\n");
    stack_display(stack);

    return 0;
}
