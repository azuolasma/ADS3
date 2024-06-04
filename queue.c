// Module owner: iesi9959
#include<stdlib.h>
#include<stdio.h>
#include "LOANS.h"

Queue* CreateQueue(int initialCapacity)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL)
    {
        printf("Memory allocation error!\n");
        exit(1);
    }

    queue->array = (PaymentNode **)malloc(initialCapacity*sizeof(PaymentNode *));
    if(queue->array == NULL)
    {
        printf("Memory allocation error!\n");
        free(queue);
        exit(1);
    }

    queue->front = -1;
    queue->tail = -1;
    queue->size = 0;
    queue->capacity = initialCapacity;

    return queue;
}

//returns 1 if queue is empty, returns 0 if queue has elements and returns 2, if there is no queue created
int isQueueEmpty(Queue *queue)
{
    if(queue == NULL)
    {
        return 2;
    }
    return queue->size == 0;
}

//returns 1 if queue is full, returns 0 if queue is available and returns 2, if there is no queue created
int isQueueFull(Queue *queue)
{
    if(queue == NULL)
    {
        return 2;
    }
    return (queue->tail == (queue->capacity - 1));
}

void Enqueue(Queue *queue, PaymentNode *data)
{
    if(queue == NULL)
    {
        printf("Queue was already destroyed or never created! Enqueuing failed.\n");
        return;
    }
    if(isQueueFull(queue))
    {
        queue->capacity *= 2;
        queue->array = (PaymentNode **)realloc(queue->array, queue->capacity * sizeof(PaymentNode *));
        if(queue->array == NULL) {
            printf("Memory allocation error during resize!\n");
            exit(1);
        }
    }
    if(isQueueEmpty(queue))
    {
        queue->front = 0;
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
    queue->array[queue->tail] = data;
}

PaymentNode* Dequeue(Queue *queue)
{
    if(queue == NULL)
    {
        printf("Queue was already destroyed or never created! Dequeuing failed.\n");
        return 0;
    }
    if(isQueueEmpty(queue) == 1)
    {
        printf("Queue is already empty!\n");
        exit(2);
    }

    PaymentNode  *element = queue->array[queue->front];
    queue->size--;
    queue->front = (queue->front + 1) % queue->capacity;

    return element;
}
PaymentNode* GetFrontData(Queue *queue)
{
    if(isQueueEmpty(queue))
    {
        printf("Queue is empty!\n");
        exit(3);
    }

    return queue->array[queue->front];
}

//returns -1 if queue was not found, otherwise returns size of the queue
int GetQueueSize(Queue *queue)
{
    if(queue == NULL)
    {
        printf("Queue was already destroyed or never created!\n");
        return -1;
    }
    return queue->size;
}

void DestroyQueue(Queue **queuePointer){
    if(queuePointer == NULL || *queuePointer == NULL){
        return;
    }

    Queue *queue = *queuePointer;

    free(queue->array);
    free(queue);

    *queuePointer = NULL;
}



