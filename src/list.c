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

/* Data Structures */
struct List {
    void** items;
    int capacity;                       // allocated storage capacity
    int size;                           // number of inserted elements
    int zero;                           // offsets the beggining of the array
};

// testing
void print_list(List *l) {
    for (int i = 0; i < l -> capacity; i++) {
        int *ptr = (int*) l -> items[i];
        if (ptr != NULL)
            printf("%d = %d\n", i, ptr);
        else
            printf("%d = NULL\n", i);
    }
}
/**
 *  list_new():
 *      Initializes an empty list and returns a pointer to it.
 */
List *list_new()
{
    List *l = (List*) malloc(sizeof(List));
    if (!l) {
        fprintf(stderr, "list_new: cannot create new list!\n");
        return NULL;
    }
    l -> items = (void**) malloc(sizeof(void*));
    l -> size = 0;
    l -> capacity = 1;
    l -> zero = 0;
    return l;
}

/**
 *  list_upsize():
 *      Resizes the list to the given capacity argument.
 *      Returns 0 if the list was succesfully resized and 1 otherwise.
 *      If resizing is not successful, list remains unaltered.
 */
int list_upsize(List *l, int capacity, int prepend) {
    /* size of the new block of memory */
    size_t memSize = capacity * sizeof(void*);
    void **i;
    /* prepend allocates memory and copies data back into the second half */
    if (prepend) {
        i = (void**) malloc(memSize);
        memcpy(i + (capacity / 2) , l -> items, memSize / 2);
        /* important! offsets the "zero element" on the list */
        l -> zero = capacity / 2;
    }
    /* append simply tries to allocate more memory on the existing block */
    else {
        i = (void**) realloc(l -> items, memSize);
    }
    /* error checking and variable updating */
    if(!i) {
        fprintf(stderr, "list_upsize: cannot resize list!\n");
        return 1;
    }
    l -> items = i;
    l -> capacity = capacity;
    return 0;
}

/**
 *  list_append():
 *      Adds an item to the end of the list. Returns 0 if everything goes as
 *      expected and 1 otherwise.
 */
int list_append(List *l, void *data, size_t dataSize) {
    /* if the list is full, resize it to two times it's current capacity */
    if (l -> size == l -> capacity) {
        if (list_upsize(l, 2 * l -> capacity, 0)) {
            fprintf(stderr, "list_append: cannot append to list!\n");
            return 1;
        }
    }
    /* allocates space on the heap and copies the data */
    l -> items[l -> size] = malloc(dataSize);
    memcpy(l -> items[l -> size++], data, dataSize);
    return 0;
}

/**
 *  list_prepend():
 *      Adds an item to the beggining of the list. Returns 0 if everything goes
 *      as expected and 1 otherwise.
 */
int list_prepend(List *l, void *data, size_t dataSize) {
    /* if the list is full, resize it to two times it's current capacity */
    if (l -> size == l -> capacity || l -> zero == 0) {
        if (list_upsize(l, 2 * l -> capacity, 1)) {
            fprintf(stderr, "list_prepend: cannot prepend to list!\n");
            return 1;
        }
    }
    /* allocates space on the heap and copies the data */
    if (l -> zero > 0) l -> zero--;
    l -> items[l -> zero] = malloc(dataSize);
    memcpy(l -> items[l -> zero], data, dataSize);
    l -> size++;
    return 0;
}

/**
 *  list_insert():
 *      Inserts an item at the given index. Returns 0 if everything goes as
 *      expected and 1 otherwise.
 */
int list_insert(List *l, int i, void *data, size_t dataSize) {
    if (i > l -> size - 1) {
        fprintf(stderr, "list_insert: index out of range!\n");
        return 1;
    }
    /* inserting at the last index is equivalent to appending */
    else if (i == l -> size) return list_append(l, data, dataSize);
    /* inserting at the zero index is equivalent to prepending */
    else if (i == 0) return list_prepend(l, data, dataSize);
    /* otherwise, replace an existing value */
    else {
        memcpy(l -> items[i], data, dataSize);
        return 0;
    }
}

/**
 *  list_get():
 *      Copies the item at the given index and returns it.
 */
void *list_get(List *l, int i) {
    if (i > l -> size - 1) {
        fprintf(stderr, "list_get: index out of range!\n");
        return NULL;
    }
    /* TODO: copy data before returning? */
    return l -> items[l -> zero + i];
}

#define list_append(l, data) list_append(l, data, sizeof(data))
#define list_prepend(l, data) list_prepend(l, data, sizeof(data))
#define list_insert(l, i, data) list_append(l, i, data, sizeof(data))

int main() {
    List *l = list_new();
    int n = 4;
    for (int i = 0; i < n; i++)
        list_prepend(l, &i);
    print_list(l);
    return 0;
}

