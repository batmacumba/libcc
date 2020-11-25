/*******************************************************************************
 *  list.c
 *      A generic list implementation.
 ******************************************************************************/

/* Includes & Macros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#undef list_append
#undef list_prepend
#undef list_insert
#undef list_set

#define PREPEND     0
#define APPEND      1

/* Data Structure */
struct List {
    void **items;
    int allocated;                      // allocated storage capacity
    int n;                              // number of elements
    int zero;                           // index of the first element
};

/**
 *  list_new():
 *      Initializes an empty list and returns a pointer to it.
 */
List *
list_new() {
    List *this = (List*) malloc(sizeof(List));
    if (!this) {
        fprintf(stderr, "list_new: cannot create new list!\n");
        return NULL;
    }
    this -> items = NULL;
    this -> n = 0;
    this -> allocated = 0;
    this -> zero = 0;
    return this;
}

/**
 *  list_resize():
 *      Resizes the list to the given capacity.
 */
static int
list_resize(List *self, int new_allocated, int flag) {
    /* size of the new block of memory */
    size_t arraySize = new_allocated * sizeof(void *);
    void **new_items = NULL;
    
    /* append simply tries to allocate on the end of the current block */
    if (flag == APPEND) {
        new_items = (void**) realloc(self -> items, arraySize);
    }
    /* prepend allocates and copies to the middle of the new block */
    else if (flag == PREPEND) {
        new_items = (void**) malloc(arraySize);
        memcpy(new_items + new_allocated / 2, self -> items, arraySize / 2);
        /* important! offsets the "zero element" on the list */
        self -> zero = new_allocated / 2;
    }
    /* error checking and variable updating */
    else if(!new_items) {
        fprintf(stderr, "list_resize: cannot resize list\n");
        return -1;
    }
    self -> items = new_items;
    self -> allocated = new_allocated;
    return 0;
}

/**
 *  list_memHandler():
 *      Checks if the list needs to shrink or grow and acts accordingly.
 */
static int
list_memHandler(List *self, int flag) {
    int handler;
    /* full or empty */
    if (self -> n == self -> allocated) {
        if (self -> allocated == 0) handler = list_resize(self, 1, APPEND);
        else handler = list_resize(self, 2 * self -> allocated, flag);
    }
    /* very sparse */
    else if (self -> allocated / self -> n >= 4)
        handler = list_resize(self, self -> allocated / 2, flag);
    /* no empty space on the beggining */
    else if (self -> items[0] != NULL && flag == PREPEND) {
        handler = list_resize(self, 2 * self -> allocated, flag);
    }
    /* no resize needed, move along */
    else {
        puts("no resize");
        handler = 0;
    }
    /* error? */
    if (handler < 0)
        fprintf(stderr, "list_memHandler: error resizing list\n");
    return handler;
    
}

/**
 *  list_append():
 *      Adds an item to the end of the list.
 */
int
list_append(List *op, void *data, size_t dataSize) {
    if (list_memHandler(op, APPEND) < 0) {
        fprintf(stderr, "list_append: error handling memory\n");
        return -1;
    }
    /* allocates space on the heap and copies the data */
    op -> items[op -> n] = malloc(dataSize);
    memcpy(op -> items[op -> n++], data, dataSize);
    return 0;
}

/**
 *  list_prepend():
 *      Adds an item to the beggining of the list.
 */
int list_prepend(List *op, void *data, size_t dataSize) {
    if (list_memHandler(op, PREPEND) < 0) {
        fprintf(stderr, "list_prepend: error handling memory\n");
        return -1;
    }
      printf("op -> zero = %d\n", op -> zero);
    /* allocates space on the heap and copies the data */
    if (op -> zero > 0) op -> zero--;
    op -> items[op -> zero] = malloc(dataSize);
    memcpy(op -> items[op -> zero], data, dataSize);
    op -> n++;
  
    return 0;
}
//
///**
// *  list_insert():
// *      Inserts an item at the given index. Returns 0 if everything goes as
// *      expected and 1 otherwise.
// */
//int list_insert(List *l, int i, void *data, size_t dataSize) {
//    if (i > l -> n - 1) {
//        fprintf(stderr, "list_insert: index out of range!\n");
//        return -1;
//    }
//    /* inserting at the last index is equivalent to appending */
//    else if (i == l -> n) return list_append(l, data, dataSize);
//    /* inserting at the zero index is equivalent to prepending */
//    else if (i == 0) return list_prepend(l, data, dataSize);
//    /* otherwise, replace an existing value */
//    else {
//        memcpy(l -> items[i], data, dataSize);
//        return 0;
//    }
//}

/**
 *  list_get():
 *      Returns the item at the given index.
 */
void *
list_get(List *op, int i) {
    if (i > op -> n - 1) {
        fprintf(stderr, "list_get: index out of range\n");
        return NULL;
    }
    /* negative index returns n - i item */
    if (i < 0) {
        i += op -> n;
        if (i < 0) {
            fprintf(stderr, "list_get: index out of range\n");
            return NULL;
        }
    }
    printf("op -> zero = %d\n", op -> zero + i);
    return op -> items[op -> zero + i];
}

/**
 *  list_set():
 *      Sets the item at the given index to the given value.
 */
int
list_set(List *op, int i, void *data, size_t dataSize) {
    if (i > op -> n - 1) {
        fprintf(stderr, "list_set: index out of range\n");
        return -1;
    }
    /* negative index sets n - i item */
    if (i < 0) {
        i += op -> n;
        if (i < 0) {
            fprintf(stderr, "list_set: index out of range\n");
            return -1;
        }
    }
    
    op -> items[op -> zero + i] = malloc(dataSize);
    if (!op -> items[op -> zero + i]) {
        fprintf(stderr, "list_set: cannot allocate space\n");
        return -1;
    }
    /* finally copies the data and returns */
    free(op -> items[op -> zero + i]);
    op -> items[op -> zero + i] = malloc(dataSize);
    memcpy(op -> items[op -> zero + i], data, dataSize);
    return 0;
}

#define list_append(l, data) list_append(l, data, sizeof(data))
#define list_prepend(l, data) list_prepend(l, data, sizeof(data))
#define list_insert(l, i, data) list_append(l, i, data, sizeof(data))
#define list_set(l, i, data) list_set(l, i, data, sizeof(data))
