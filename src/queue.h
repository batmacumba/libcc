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
Queue *Queue_new();                                     // constructor
int Queue_isEmpty(Queue *s);                            // is queue empty?
int Queue_size(Queue *s);                               // returns queue's size
void Queue_enqueue(Queue *s, void *new_data);           // enqueues an item
void *Queue_dequeue(Queue *s);                          // dequeues first item
void *Queue_peek(Queue *s);                             // returns first item
void **Queue_iterator(Queue *s);                        // iterator
void Queue_unitTest();                                  // test

#endif /* _QUEUE_H_ */
