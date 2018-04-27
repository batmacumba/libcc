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
 *      Resizes the list to the given argument.
 */
static int
list_resize(List *l, int allocated, int prepend) {
    /* size of the new block of memory */
    size_t memSize = allocated * sizeof(void*);
    void **i;
    /* prepend allocates memory and copies data back into the second half */
    if (prepend) {
        i = (void**) malloc(memSize);
        memcpy(i + (allocated / 2) , l -> items, memSize / 2);
        /* important! offsets the "zero element" on the list */
        l -> zero = allocated / 2;
    }
    /* append simply tries to allocate more memory on the existing block */
    else {
        i = (void**) realloc(l -> items, memSize);
    }
    /* error checking and variable updating */
    if(!i) {
        fprintf(stderr, "list_resize: cannot resize list!\n");
        return -1;
    }
    l -> items = i;
    l -> allocated = allocated;
    return 0;
}

/**
 *  list_memHandler():
 *      Checks if the list needs to shrink or grow and acts accordingly.
 */
static int
list_memHandler(List *self, int flag) {
    /* if full, resizes it to 1.5x it's currently allocated capacity */
    if (self -> n == self -> allocated) {
        if (list_resize(self, 1.5 * self -> allocated, 0) < 0) {
            fprintf(stderr, "list_memHandler: cannot append to list!\n");
            return -1;
        }
    }
}
///**
// *  list_append():
// *      Adds an item to the end of the list.
// */
//int
//list_append(List *l, void *data, size_t dataSize) {
//
//    /* allocates space on the heap and copies the data */
//    l -> items[l -> n] = malloc(dataSize);
//    memcpy(l -> items[l -> n++], data, dataSize);
//    return 0;
//}
//
///**
// *  list_prepend():
// *      Adds an item to the beggining of the list. Returns 0 if everything goes
// *      as expected and 1 otherwise.
// */
//int list_prepend(List *l, void *data, size_t dataSize) {
//    /* if the list is full, resize it to two times it's current allocated */
//    if (l -> n == l -> allocated || l -> zero == 0) {
//        if (list_resize(l, 2 * l -> allocated, 1)) {
//            fprintf(stderr, "list_prepend: cannot prepend to list!\n");
//            return -1;
//        }
//    }
//    /* allocates space on the heap and copies the data */
//    if (l -> zero > 0) l -> zero--;
//    l -> items[l -> zero] = malloc(dataSize);
//    memcpy(l -> items[l -> zero], data, dataSize);
//    l -> n++;
//    return 0;
//}
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
    memcpy(op -> items[op -> zero + i], data, dataSize);
    return 0;
}

#define list_append(l, data) list_append(l, data, sizeof(data))
#define list_prepend(l, data) list_prepend(l, data, sizeof(data))
#define list_insert(l, i, data) list_append(l, i, data, sizeof(data))
#define list_set(l, i, data) list_set(l, i, data, sizeof(data))

int main() {
    List *l = list_new();
    int n = 4;
//    for (int i = 0; i < n; i++)
//        list_prepend(l, &i);
//    print_list(l);
    return 0;
}

