/* includes e macros */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* stack implementation (hidden from clients) */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Stack {
    Item *top;
    int size;
};

/* functions */

/**
 * Initializes an empty stack and returns a pointer to it.
 */
Stack *Stack_new() {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    if (!s) {
        fprintf(stderr, "Cannot create new stack!\n");
        return NULL;
    }
    s -> top = NULL;
    s -> size = 0;
    return s;
}

/**
 * Returns 1 if this stack is empty, 0 if it's not.
 */
int Stack_isEmpty(Stack *s) {
    if (s -> top == NULL) return 1;
    else return 0;
}

/**
 * Returns the number of items on this stack.
 */
int Stack_size(Stack *s) {
    return s -> size;
}

/**
 * Initializes an empty Item.
 */
Item *Item_new() {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Cannot create new item!\n");
        return NULL;
    }
    i -> data = NULL;
    i -> next = NULL;
    return i;
}

/**
 * Adds the item to the stack.
 */
void Stack_push(Stack *s, void *new_data) {
    Item *new_item = Item_new();
    new_item -> data = new_data;
    new_item -> next = s -> top;
    s -> top = new_item;
    s -> size++;
}

/**
 * Removes the item from the top of the stack and returns its content.
 */
void *Stack_pop(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    void *data = s -> top -> data;
    s -> top = s -> top -> next;
    s -> size--;
    return data;
}

/**
* Returns the item on the top of the stack without removing it.
*/
void *Stack_peek(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    return s -> top -> data;
}

/**
 * Copies all the items on the stack and returns an array of items.
 */
void **Stack_iterator(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    void **stack_items = (malloc(sizeof(void*) * s -> size));
    Item *current_item = s -> top;
    int i = 0;
    while (current_item != NULL) {
        stack_items[i] = current_item -> data;
        current_item = current_item -> next;
        i++;
    }
    return stack_items;
}

/* test */
int main() {
    Stack *stack = Stack_new();
    Stack_push(stack, "teste3");
    Stack_push(stack, "teste2");
    Stack_push(stack, "teste1");
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
    void *tmp = malloc(sizeof(*tmp));
    tmp = 1;
    Stack_push(stack, tmp);
    tmp = 2;
    Stack_push(stack, tmp);
    tmp = 3;
    Stack_push(stack, tmp);

    int **stack_items = (int**) Stack_iterator(stack);
    for (int i = 0; i < Stack_size(stack); i++) {
        printf("item %d = %d\n", i, stack_items[i]);
    }
    return 0;
}
