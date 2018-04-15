/*******************************************************************************
 * Stack: LIFO collection of objects
 * Dependencies: stdio.h, stdlib.h, string.h
 * Compilation:
     $ make stack.o
     $ gcc file.c stack.o -o file
 * Include this header in your file
 ******************************************************************************/

#ifndef _STACK_H_
#define _STACK_H_

typedef struct Stack Stack;

/*
 * Available operations
 */
Stack *Stack_new();                                     // constructor
int Stack_isEmpty(Stack *s);                            // is stack empty?
int Stack_size(Stack *s);                               // return stack's size
void Stack_push(Stack *s, void *new_data);              // pushes an item
void *Stack_pop(Stack *s);                              // pops an item
void *Stack_peek(Stack *s);                             // returns item on top
void **Stack_iterator(Stack *s);                        // iterator
void Stack_unitTest();                                  // test

#endif /* _STACK_H_ */
