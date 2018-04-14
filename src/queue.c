/* includes & macros */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* queue implementation (hidden from clients) */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Queue {
    Item *first;
    Item *last;
    int size;
};

/* functions */

/**
 * Initializes an empty queue and returns a pointer to it.
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

/**
 * Returns 1 if this queue is empty, 0 if it's not.
 */
int Queue_isEmpty(Queue *s) {
    if (s -> first == NULL) return 1;
    else return 0;
}

/**
 * Returns the number of items on this queue.
 */
int Queue_size(Queue *s) {
    return s -> size;
}

/**
 * Initializes an empty Item.
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

/**
 * Adds the item to the end of the queue.
 */
void Queue_enqueue(Queue *s, void *new_data) {
    Item *old_last = s -> last;
    s -> last = Item_new();
    s -> last -> data = new_data;
    if (Queue_isEmpty(s) == 1) s -> first = s -> last;
    else old_last -> next = s -> last;
    s -> size++;
}

/**
 * Removes the item from the first spot and returns it.
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

/**
 * Returns the item on the first spot of the queue without removing it.
 */
void *Queue_peek(Queue *s) {
    if (Queue_isEmpty(s) == 1) {
        fprintf(stderr, "Queue_peek: Queue is empty!\n");
        return NULL;
    }
    return s -> first -> data;
}

/**
 * Copies all the items on the queue and returns an array of items.
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

/* test */
int Queue_unitTest() {
    Queue *queue = Queue_new();
    Queue_enqueue(queue, "teste1");
    Queue_enqueue(queue, "teste2");
    Queue_enqueue(queue, "teste3");
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
    printf("retorno = %s\n", Queue_dequeue(queue));
}
