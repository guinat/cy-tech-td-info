#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Compile : gcc ex3.c

typedef struct Client
{
    int articles;
    struct Client *next;
} client_t;

typedef struct Queue
{
    client_t *front;
    client_t *rear;
} queue_t;

void queue_initialize(queue_t *queue)
{
    queue->front = queue->rear = NULL;
}

void enqueue(queue_t *queue, int articles)
{
    client_t *client_new = malloc(sizeof(client_t));
    if (client_new == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    client_new->articles = articles;
    client_new->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = queue->rear = client_new;
    }
    else
    {
        queue->rear->next = client_new;
        queue->rear = client_new;
    }
}

void dequeue(queue_t *queue)
{
    if (queue->front == NULL)
    {
        fprintf(stderr, "Error: Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    client_t *temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
}

void queue_display(queue_t *queue)
{
    if (queue->front == NULL)
    {
        printf("No clients in the queue\n");
        return;
    }

    printf("Clients in the queue (in order of arrival):\n");
    client_t *current = queue->front;
    while (current != NULL)
    {
        printf("Number of articles: %d\n", current->articles);
        current = current->next;
    }
}

int main(void)
{
    srand(time(NULL));

    queue_t checkout_queue;
    queue_initialize(&checkout_queue);

    for (int i = 0; i < 3; i++)
    {
        int articles = rand() % 50 + 1;
        enqueue(&checkout_queue, articles);
    }

    while (checkout_queue.front != NULL)
    {
        printf("Client with %d articles has paid\n", checkout_queue.front->articles);
        dequeue(&checkout_queue);

        if (rand() % 3 == 0)
        {
            int numNewClients = rand() % 3 + 1;
            for (int i = 0; i < numNewClients; i++)
            {
                int articles = rand() % 50 + 1;
                enqueue(&checkout_queue, articles);
            }
        }

        queue_display(&checkout_queue);
    }

    return 0;
}
