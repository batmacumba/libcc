/*
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
    Queue *s = (Queue*) malloc(sizeof(Queue));
    if (!s) {
        fprintf(stderr, "Queue_new: Cannot create new queue!\n");
        return NULL;
    }
    s -> first = NULL;
    s -> last = NULL;
    s -> size = 0;
    return s;
}

/*
 * Queue_isEmpty(): returns 1 if this queue is empty, 0 if it's not.
 */
int Queue_isEmpty(Queue *s) {
    if (s -> first == NULL) return 1;
    else return 0;
}

/*
 * Queue_size(): returns the number of items on this queue.
 */
int Queue_size(Queue *s) {
    return s -> size;
}

/*
 * Item_new(): initializes an empty Item.
 */
Item *Item_new() {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Item_new: Cannot create new item!\n");
        return NULL;
    }
    i -> data = NULL;
    i -> next = NULL;
    return i;
}

/*
 * Queue_enqueue(): adds the item to the end of the queue.
 */
void Queue_enqueue(Queue *s, void *new_data) {
    Item *old_last = s -> last;
    s -> last = Item_new();
    s -> last -> data = new_data;
    if (Queue_isEmpty(s) == 1) s -> first = s -> last;
    else old_last -> next = s -> last;
    s -> size++;
}

/*
 * Queue_dequeue(): removes the item from the first spot and returns it.
 */
void *Queue_dequeue(Queue *s) {
    if (Queue_isEmpty(s) == 1) {
        fprintf(stderr, "Queue_dequeue: Queue is empty!\n");
        return NULL;
    }
    void *data = s -> first -> data;
    s -> first = s -> first -> next;
    s -> size--;
    if (Queue_isEmpty(s) == 1) s -> last = NULL;
    return data;
}

/*
 * Queue_peek(): returns the item on the first spot of the queue w/o removing
 */
void *Queue_peek(Queue *s) {
    if (Queue_isEmpty(s) == 1) {
        fprintf(stderr, "Queue_peek: Queue is empty!\n");
        return NULL;
    }
    return s -> first -> data;
}

/**
 * Queue_iterator(): copies all the items on the queue and returns an array.
 */
void **Queue_iterator(Queue *s) {
    if (Queue_isEmpty(s) == 1) {
        fprintf(stderr, "Queue_iterator: Queue is empty!\n");
        return NULL;
    }
    void **queue_items = (malloc(sizeof(void*) * s -> size));
    Item *current_item = s -> first;
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
    Queue_enqueue(queue, "teste1");
    Queue_enqueue(queue, "teste2");
    Queue_enqueue(queue, "teste3");
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
}
