#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 15

// Queue definition.
typedef struct queue {
    int size;
    int head;
    int tail;
    int array[SIZE];
} Queue;

// Queue operations.
void enqueue(Queue *queue, int data);
void dequeue(Queue *queue);
int front(Queue *queue);
int size(Queue *queue);
bool empty(Queue *queue);
bool full(Queue *queue);

int main(void)
{
    Queue queue = { .size = 0, .head = -1, .tail = -1 };

    printf("Queue size is: %i\n", size(&queue));
    printf("Is queue empty? %i\n", empty(&queue));

    for (int i = 0; i < SIZE; i++)
        enqueue(&queue, i + 1);
    printf("\nElements inserted into the queue!\n");

    printf("Queue size is: %i\n", size(&queue));
    printf("Is queue empty? %i\n", empty(&queue));

    printf("Position of head: %i\n", queue.head);
    printf("Position of tail: %i\n", queue.tail);

    printf("\nQueue elements: ");
    while (!empty(&queue)) {
        printf("%i ", front(&queue));
        dequeue(&queue);
    }
    printf("\n");
    printf("Queue size is: %i\n", size(&queue));
    printf("Is queue empty? %i\n", empty(&queue));
    printf("Position of head: %i\n", queue.head);
    printf("Position of tail: %i\n", queue.tail);

    // Insert 5 elements.
    for (int i = 0; i < 5; i++)
        enqueue(&queue, i * 3 + 5);
    printf("\nNew queue elements: ");
    for (int i = 0, index = queue.head; i < size(&queue);
         index = (index + 1) % SIZE, i++)
        printf("%i ", queue.array[index]);
    printf("\n");

    for (int i = 0; i < 2; i++)
        dequeue(&queue);
    printf("\nRemoved 2 previous elements\n");
    printf("Queue size is: %i\n", size(&queue));
    printf("Is queue empty? %i\n", empty(&queue));
    printf("Position of head: %i\n", queue.head);
    printf("Position of tail: %i\n", queue.tail);

    return 0;
}

void enqueue(Queue *queue, int data)
{
    if (full(queue)) {
        fprintf(stderr, "Queue is full!\n");
        return;
    }

    if (empty(queue))
        queue->head = (queue->head + 1) % SIZE;

    queue->tail               = (queue->tail + 1) % SIZE;
    queue->array[queue->tail] = data;
    queue->size++;
}

void dequeue(Queue *queue)
{
    if (empty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return;
    }

    if (size(queue) == 1)
        queue->tail = (queue->tail + 1) % SIZE;

    queue->head = (queue->head + 1) % SIZE;
    queue->size--;
}

int front(Queue *queue)
{
    if (empty(queue))
        return INT_MIN;

    return queue->array[queue->head];
}

int size(Queue *queue)
{
    return queue->size;
}

bool empty(Queue *queue)
{
    return !queue->size;
}

bool full(Queue *queue)
{
    return queue->size == SIZE;
}
