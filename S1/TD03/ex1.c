#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compile : gcc ex1.c

#define MAX_WORD_LENGTH 20

typedef struct Node
{
    char word[MAX_WORD_LENGTH + 1];
    struct Node *next;
    struct Node *prev;
} node_t;

typedef struct LinkedList
{
    node_t *head;
    node_t *tail;
} linked_list_t;

int compare_words(const char *word1, const char *word2)
{
    return strcmp(word1, word2) < 0;
}

node_t *node_create(const char *word)
{
    node_t *node_new = malloc(sizeof(node_t));
    if (node_new == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(node_new->word, word, MAX_WORD_LENGTH);
    node_new->word[MAX_WORD_LENGTH] = '\0';
    node_new->next = NULL;
    node_new->prev = NULL;

    return node_new;
}

void list_insert(linked_list_t *list, const char *word)
{
    node_t *node_new = node_create(word);

    if (list->head == NULL)
    {
        list->head = node_new;
        list->tail = node_new;
    }
    else if (compare_words(word, list->head->word))
    {
        node_new->next = list->head;
        list->head->prev = node_new;
        list->head = node_new;
    }
    else
    {
        node_t *current = list->head;
        while (current->next != NULL && compare_words(current->next->word, word))
        {
            current = current->next;
        }
        node_new->next = current->next;
        node_new->prev = current;
        if (current->next != NULL)
        {
            current->next->prev = node_new;
        }
        else
        {
            list->tail = node_new;
        }
        current->next = node_new;
    }
}

void list_display(linked_list_t *list)
{
    node_t *current = list->head;
    while (current != NULL)
    {
        printf("%s", current->word);
        if (current->next != NULL)
        {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void list_display_reverse(linked_list_t *list)
{
    node_t *current = list->tail;
    while (current != NULL)
    {
        printf("%s", current->word);
        if (current->prev != NULL)
        {
            printf(" -> ");
        }
        current = current->prev;
    }
    printf("\n");
}

int main(void)
{
    linked_list_t list;
    list.head = NULL;
    list.tail = NULL;

    char words[][MAX_WORD_LENGTH + 1] = {"Ahello", "Zhello", "Chello", "Khello", "Bhello"};

    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        list_insert(&list, words[i]);
    }

    printf("Alphabetical Order:\n");
    list_display(&list);

    printf("\nReverse Alphabetical Order:\n");
    list_display_reverse(&list);

    return 0;
}
