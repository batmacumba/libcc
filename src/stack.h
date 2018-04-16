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
Stack *Stack_new();                                         // constructor
int Stack_isEmpty(Stack *s);                                // is stack empty?
int Stack_size(Stack *s);                                   // return stck size
int Stack_push(Stack *s, void *new_data, size_t dataSize);  // pushes an item
void *Stack_pop(Stack *s);                                  // pops an item
void *Stack_peek(Stack *s);                                 // returns top item
void **Stack_iterator(Stack *s);                            // iterator
void Stack_unitTest();                                      // test
void Stack_destroy(Stack *s);                               // frees memory

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write Stack_push(s, data) and this macro will expand sizeof.
 */
#define Stack_push(s, data) Stack_push(s, data, sizeof(data))

#endif /* _STACK_H_ */
