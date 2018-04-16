/*******************************************************************************
 * Queue: FIFO collection of objects
 * Dependencies: stdio.h, stdlib.h, string.h
 * Compilation:
     $ make queue.o
     $ gcc file.c queue.o -o file
 * Include this header in your file
 ******************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue Queue;

/*
 * Available operations
 */
Queue *Queue_new();                                         // constructor
int Queue_isEmpty(Queue *s);                                // is queue empty?
int Queue_size(Queue *s);                                   // returns q size
int Queue_enqueue(Queue *q, void *data, size_t dataSize);   // enqueues
void *Queue_dequeue(Queue *s);                              // dequeues
void *Queue_peek(Queue *s);                                 // returns head of q
void **Queue_iterator(Queue *s);                            // iterator
void Queue_unitTest();                                      // test
void Queue_destroy(Queue *q);                               // frees memory

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write Queue_enqueue(q, data) and this macro will expand sizeof.
 */
#define Queue_enqueue(q, data) Queue_enqueue(q, data, sizeof(data))

#endif /* _QUEUE_H_ */
