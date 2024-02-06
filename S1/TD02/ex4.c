#include <stdio.h>
#include <stdlib.h>

// Compile : gcc ex4.c

typedef struct Stack
{
    char data;
    struct Stack *next;
} stack_t;

stack_t *stack_push(stack_t *top, char ch)
{
    stack_t *node_new = malloc(sizeof(stack_t));
    if (node_new == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node_new->data = ch;
    node_new->next = top;

    return node_new;
}

void stack_pop(stack_t **top)
{
    if (*top == NULL)
    {
        fprintf(stderr, "Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    stack_t *temp = *top;
    *top = (*top)->next;
    free(temp);
}

int is_empty(stack_t *top)
{
    return top == NULL;
}

int is_matching(char opening, char closing)
{
    return (opening == '(' && closing == ')') || (opening == '[' && closing == ']') || (opening == '{' && closing == '}');
}

int is_balanced(char *expression)
{
    stack_t *stack = NULL;

    for (int i = 0; expression[i] != '\0'; i++)
    {
        char current_char = expression[i];

        if (current_char == '(' || current_char == '[')
        {
            stack = stack_push(stack, current_char);
        }
        else if (current_char == ')' || current_char == ']')
        {
            if (is_empty(stack) || !is_matching(stack->data, current_char))
            {
                return 0;
            }
            stack_pop(&stack);
        }
    }

    return is_empty(stack);
}

int main(void)
{
    char expression[100];

    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);

    if (is_balanced(expression))
    {
        printf("The expression is balanced.\n");
    }
    else
    {
        printf("The expression is not balanced.\n");
    }

    return 0;
}
