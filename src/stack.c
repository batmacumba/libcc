/*
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#undef Stack_push

/*
 * Data Structures
 */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Stack {
    Item *top;
    int size;
};

/*
 * Stack_new(): initializes an empty stack and returns a pointer to it.
 */
Stack *Stack_new() {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    if (!s) {
        fprintf(stderr, "Stack_new: Cannot create new stack!\n");
        return NULL;
    }
    s -> top = NULL;
    s -> size = 0;
    return s;
}

/*
 * Stack_isEmpty(): returns 1 if this stack is empty, 0 if it's not.
 */
int Stack_isEmpty(Stack *s) {
    if (s -> top == NULL) return 1;
    else return 0;
}

/*
 * Stack_size(): returns the number of items on this stack.
 */
int Stack_size(Stack *s) {
    return s -> size;
}

/*
 * Item_new(): initializes an empty Item.
 */
Item *Item_new(size_t dataSize) {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Item_new: Cannot create new item!\n");
        return NULL;
    }
    i -> data = malloc(dataSize);
    i -> next = NULL;
    return i;
}

/*
 * Stack_push(): copies the data and adds the item to the stack.
 */
void Stack_push(Stack *s, void *data, size_t dataSize) {
    Item *i = Item_new(dataSize);
    memcpy(i -> data, data, dataSize);
    i -> next = s -> top;
    s -> top = i;
    s -> size++;
}

/*
 * Stack_pop(): removes the item from the top of the stack and returns it.
 */
void *Stack_pop(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack_pop: Stack is empty!\n");
        return NULL;
    }
    void *data = s -> top -> data;
    s -> top = s -> top -> next;
    s -> size--;
    return data;
}

/*
 * Stack_peek(): returns the item on the top of the stack without removing it.
 */
void *Stack_peek(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack_peek: Stack is empty!\n");
        return NULL;
    }
    return s -> top -> data;
}

/*
 * Stack_iterator(): copies all the items on the stack and returns an array.
 */
void **Stack_iterator(Stack *s) {
    if (Stack_isEmpty(s) == 1) {
        fprintf(stderr, "Stack_iterator: Stack is empty!\n");
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

/*
 * Stack_unitTest(): unit test.
 */
void Stack_unitTest() {
    Stack *stack = Stack_new();
    Stack_push(stack, "teste3", sizeof("teste3"));
    Stack_push(stack, "teste2", sizeof("teste2"));
    Stack_push(stack, "teste1", sizeof("teste1"));
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
}
