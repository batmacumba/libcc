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
 * Stack_new():
 * Initializes an empty stack and returns a pointer to it.
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
 * Stack_isEmpty():
 * Returns 1 if this stack is empty, 0 if it's not.
 */
int Stack_isEmpty(Stack *s) {
    if (s -> top == NULL) return 1;
    else return 0;
}

/*
 * Stack_size():
 * Returns the number of items on this stack.
 */
int Stack_size(Stack *s) {
    return s -> size;
}

/*
 * S_Item_new():
 * Initializes an empty Item.
 */
Item *S_Item_new(size_t dataSize) {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "S_Item_new: cannot malloc new item!\n");
        return NULL;
    }
    i -> data = malloc(dataSize);
    if (!i -> data) {
        fprintf(stderr, "S_Item_new: cannot malloc space for data!\n");
        return NULL;
    }
    i -> next = NULL;
    return i;
}

/*
 * Stack_push():
 * Copies the data and adds the item to the stack.
 * Returns 0 if item was succesfully pushed or 1 otherwise.
 */
int Stack_push(Stack *s, void *data, size_t dataSize) {
    Item *i = S_Item_new(dataSize);
    if (i == NULL) {
        fprintf(stderr, "Stack_push: cannot create new item!\n");
        return 1;
    }
    memcpy(i -> data, data, dataSize);
    i -> next = s -> top;
    s -> top = i;
    s -> size++;
    return 0;
}

/*
 * Stack_pop():
 * Removes the item from the top of the stack and returns it.
 */
void *Stack_pop(Stack *s) {
    if (Stack_isEmpty(s)) {
        fprintf(stderr, "Stack_pop: stack is empty!\n");
        return NULL;
    }
    void *data = s -> top -> data;
    s -> top = s -> top -> next;
    s -> size--;
    return data;
}

/*
 * Stack_peek():
 * Returns the item on the top of the stack without removing it.
 */
void *Stack_peek(Stack *s) {
    if (Stack_isEmpty(s)) {
        fprintf(stderr, "Stack_peek: stack is empty!\n");
        return NULL;
    }
    return s -> top -> data;
}

/*
 * Stack_iterator():
 * Copies all the items on the stack and returns an array.
 */
void **Stack_iterator(Stack *s) {
    if (Stack_isEmpty(s)) {
        fprintf(stderr, "Stack_iterator: stack is empty!\n");
        return NULL;
    }
    void **items = (malloc(sizeof(void*) * s -> size));
    Item *i = s -> top;
    int k = 0;
    while (k < s -> size) {
        items[k] = i -> data;
        i = i -> next;
        k++;
    }
    return items;
}

/*
 * Stack_destroy():
 * Destroys a stack, freeing all it's allocated memory.
 */
void Stack_destroy(Stack *s) {
    if (!Stack_isEmpty(s)) {
        Item *i = s -> top;
        while (i != NULL) {
            /* top of the stack points to next element */
            s -> top = i -> next;
            free(i -> data);
            free(i);
            i = s -> top;
        }
    }
    free(s);
}

/*
 * Stack_unitTest():
 * Unit test.
 */
void Stack_unitTest() {
    puts("Stack_unitTest()");
    Stack *stack = Stack_new();
    Stack_push(stack, "teste3", sizeof("teste3"));
    Stack_push(stack, "teste2", sizeof("teste2"));
    Stack_push(stack, "teste1", sizeof("teste1"));
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
    printf("retorno = %s\n", Stack_pop(stack));
    puts("");
    Stack_destroy(stack);
}
