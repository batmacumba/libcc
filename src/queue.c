/*
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#undef Queue_enqueue

/*
 * Data Structures
 */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Queue {
    Item *first;
    Item *last;
    int size;
};

/*
 * Queue_new(): initializes an empty queue and returns a pointer to it.
 */
Queue *Queue_new() {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    if (!q) {
        fprintf(stderr, "Queue_new: Cannot create new queue!\n");
        return NULL;
    }
    q -> first = NULL;
    q -> last = NULL;
    q -> size = 0;
    return q;
}

/*
 * Queue_isEmpty(): returns 1 if this queue is empty, 0 if it's not.
 */
int Queue_isEmpty(Queue *q) {
    if (q -> first == NULL) return 1;
    else return 0;
}

/*
 * Queue_size(): returns the number of items on this queue.
 */
int Queue_size(Queue *q) {
    return q -> size;
}

/*
 * Q_Item_new(): initializes an empty Item.
 */
Item *Q_Item_new(size_t dataSize) {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Q_Item_new: Cannot create new item!\n");
        return NULL;
    }
    i -> data = malloc(dataSize);
    i -> next = NULL;
    return i;
}

/*
 * Queue_enqueue(): copies the data and adds the item to the end of the queue.
 */
void Queue_enqueue(Queue *q, void *data, size_t dataSize) {
    Item *old_last = q -> last;
    q -> last = Q_Item_new(dataSize);
    memcpy(q -> last -> data, data, dataSize);
    if (Queue_isEmpty(q) == 1) q -> first = q -> last;
    else old_last -> next = q -> last;
    q -> size++;
}

/*
 * Queue_dequeue(): removes the item from the first spot and returns it.
 */
void *Queue_dequeue(Queue *q) {
    if (Queue_isEmpty(q) == 1) {
        fprintf(stderr, "Queue_dequeue: Queue is empty!\n");
        return NULL;
    }
    void *data = q -> first -> data;
    q -> first = q -> first -> next;
    q -> size--;
    if (Queue_isEmpty(q) == 1) q -> last = NULL;
    return data;
}

/*
 * Queue_peek(): returns the item on the first spot of the queue w/o removing
 */
void *Queue_peek(Queue *q) {
    if (Queue_isEmpty(q) == 1) {
        fprintf(stderr, "Queue_peek: Queue is empty!\n");
        return NULL;
    }
    return q -> first -> data;
}

/**
 * Queue_iterator(): copies all the items on the queue and returns an array.
 */
void **Queue_iterator(Queue *q) {
    if (Queue_isEmpty(q) == 1) {
        fprintf(stderr, "Queue_iterator: Queue is empty!\n");
        return NULL;
    }
    void **queue_items = (malloc(sizeof(void*) * q -> size));
    Item *current_item = q -> first;
    int i = 0;
    while (current_item != NULL) {
        queue_items[i] = current_item -> data;
        current_item = current_item -> next;
        i++;
    }
    return queue_items;
}

/*
 * Queue_unitTest(): unit test.
 */
void Queue_unitTest() {
    Queue *queue = Queue_new();
    Queue_enqueue(queue, "teste1", sizeof("teste1"));
    Queue_enqueue(queue, "teste2", sizeof("teste2"));
    Queue_enqueue(queue, "teste3", sizeof("teste3"));
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
}
