/*
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#undef list_append

/*
 * Data Structures
 */
struct List {
    void** items;
    int capacity;                       // allocated storage capacity
    int size;                           // number of inserted elements
    int offset;
};

/*
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
    return l;
}

/*
 *  list_resize():
 *      Resizes the list so its capacity is new_size.
 *      Returns 0 if item was succesfully resized and 1 otherwise.
 *      If resizing is not sucessfull, list remains unaltered.
 */
int list_resize(List *l, int n)
{
    void **i = (void**) realloc(l -> items, n * sizeof(void*));
    if(!i) {
        fprintf(stderr, "list_resize: cannot resize list!\n");
        return 1;
    }
    l -> items = i;
    l -> capacity = n;
    return 0;
}

/*
 *  list_append():
 *      Adds an item to the end of the list. Returns 0 if everything goes as
 *      expected and 1 otherwise.
 */
int list_append(List *l, void *data, size_t dataSize) {
    /* if the list is full, resize it to two times it's current capacity */
    if (l -> size == l -> capacity) {
        if (list_resize(l, 2 * l -> capacity)) {
            fprintf(stderr, "list_append: cannot append to list!\n");
            return 1;
        }
    }
    /* allocates space on the heap and copies the data */
    l -> items[l -> size] = malloc(dataSize);
    memcpy(l -> items[l -> size++], data, dataSize);
    return 0;
}

/*
 *  list_insert():
 *      Inserts an item at the given index. Returns 0 if everything goes as
 *      expected and 1 otherwise.
 */
int list_insert(List *l, int i, void *data, size_t dataSize) {
    if (i > l -> size) {
        fprintf(stderr, "list_insert: index out of range!\n");
        return 1;
    }
    /* inserting at the last index is equivalent to appending */
    else if (i == l -> size) list_append(l, data, dataSize);
    
    
    
}

