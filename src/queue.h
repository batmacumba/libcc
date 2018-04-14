/******************************************************************************
 *  Dependencies: none
 ******************************************************************************/

/* ifndef guard */
#ifndef _QUEUE_H_
#define _QUEUE_H_

/* DATA STRUCTURE */
typedef struct Queue Queue;

/* FUNCTIONS */
Queue *Queue_new();
int Queue_isEmpty(Queue *s);
int Queue_size(Queue *s);
void Queue_enqueue(Queue *s, void *new_data);
void *Queue_dequeue(Queue *s);
void *Queue_peek(Queue *s);
void **Queue_iterator(Queue *s);
int Queue_unitTest();

#endif /* _QUEUE_H_ */
