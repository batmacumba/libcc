/******************************************************************************
 *  Compilation(test): gcc stack.c -o stack
 *  Execution(test): ./stack
 *  Dependencies: none
 ******************************************************************************/

/* ifndef guard */
#ifndef _STACK_H_
#define _STACK_H_

/* DATA STRUCTURE */
typedef struct Stack Stack;

/* FUNCTIONS */
Stack *Stack_new();
int Stack_isEmpty(Stack *s);
int Stack_size(Stack *s);
void Stack_push(Stack *s, void *new_data);
void *Stack_pop(Stack *s);
void *Stack_peek(Stack *s);
void **Stack_iterator(Stack *s);
void Stack_unitTest();

#endif /* _STACK_H_ */
