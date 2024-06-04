// Module owner: azma9922
#include "LOANS.H"
#include <stdio.h>   // For fprintf and stderr
#include <stdlib.h>  // For malloc, free, and NULL
#include <stddef.h>  // For NULL (if not included through stdlib)
#include <limits.h>  // For INT_MAX
#define MAX_CAPACITY 10000
PriorityQueue* createPriorityQueue(int initialCapacity) {
    // Check if initialCapacity is allowed
    if(!(initialCapacity <= MAX_CAPACITY) || initialCapacity <= 0) {
        fprintf(stderr, "Invalid capacity. Please choose in the range from 1 to %d", MAX_CAPACITY);
        return NULL;
    }

    // Attempt to allocate memory for the PriorityQueue struct
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        fprintf(stderr, "Memory allocation failed for priority queue structure.\n");
        return NULL;
    }

    // Attempt to allocate memory for data array
    (*pq).data = (PaymentNode **)malloc(sizeof(PaymentNode *) * initialCapacity);
    if ((*pq).data == NULL) {
        fprintf(stderr, "Memory allocation failed for data array.\n");
        free(pq); // Clean up previously allocated memory for the struct
        return NULL;
    }

    // Attempt to allocate memory for the priorities array
    (*pq).priorities = (int *)malloc(sizeof(int) * initialCapacity);
    if ((*pq).priorities == NULL) {
        fprintf(stderr, "Memory allocation failed for priorities array.\n");
        free((*pq).data); //Clean up previously allocated memory for priorities array
        free(pq); // Clean up previously allocated memory for the struct
        return NULL;
    }

    // Initialize the size and capacity
    (*pq).size = 0;
    (*pq).capacity = initialCapacity;

    return pq;
}

int isEmpty(PriorityQueue *pq) {
    return (*pq).size == 0;
}

int isFull(PriorityQueue *pq) {
    return (*pq).size == (*pq).capacity;
}

void enqueue(PriorityQueue *pq, PaymentNode *element, int priority) {
    // Check if priority queue is already full
    if(isFull(pq)) {
        fprintf(stderr, "Error: Queue is full.\n");
        return;
    }

    // Shift elements to the right until the correct spot is found
    int i = (*pq).size - 1;
    while(i>=0 && (*pq).priorities[i] > priority) {
        (*pq).data[i+1] = (*pq).data[i];
        (*pq).priorities[i+1]  = (*pq).priorities[i];
        i--;
    }

    // Insert the new element at the found position
    (*pq).data[i+1] = element;
    (*pq).priorities[i+1] = priority;
    (*pq).size++;

    return;
}

PaymentNode* dequeue(PriorityQueue *pq) {
    // Check if priority queue is empty
    if(isEmpty(pq)) {
        fprintf(stderr, "Error: Queue is empty.\n");
        return NULL;
    }

    // The element with the highest priority is always at index 0, due to FIFO implementation of the enqueue method
    PaymentNode* highestPriorityElement = (*pq).data[0];

    // Shift all elements one position to the left to fill the empty space
    for(int i=1; i<(*pq).size; i++) {
        (*pq).data[i-1] = (*pq).data[i];
        (*pq).priorities[i-1] = (*pq).priorities[i];
    }

    // Clean up the priority queue
    (*pq).size--;
    (*pq).data[(*pq).size] = NULL; // Nullifying the pointer
    (*pq).priorities[(*pq).size] = INT_MAX; // Setting the element to lowest priority possible

    return highestPriorityElement;
}

PaymentNode* peek(PriorityQueue *pq) {
    if(isEmpty(pq)) {
        fprintf(stderr, "Error: Queue is empty.\n");
        return NULL;
    }

    return (*pq).data[0];
}

void destroyPriorityQueue(PriorityQueue *pq) {
    if(pq != NULL) {
        free((*pq).data);
        free((*pq).priorities);
        free(pq);
        pq = NULL;
    }

    return;
}
