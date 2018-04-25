/*******************************************************************************
 * List: python-like implementation of a list.
 * Dependencies: stdio.h, stdlib.h, string.h
 * Compilation:
     $ make list.o
     $ gcc file.c list.o -o file
 * Include this header in your file
 ******************************************************************************/

#ifndef _LIST_H_
#define _LIST_H_

typedef struct List List;

/*
 * Available operations
 */
List *list_new();                                       // constructor
int list_append(List *l, void *data, size_t dataSize);  // appends data to list
int list_prepend(List *l, void *data, size_t dataSize); // prepends data to list
//List *list_extend();
int list_insert(List *l, int i,
                void *data, size_t dataSize)            // puts data at given i
//int list_get();
//int list_remove();
//int list_pop();
//int list_contains();
//int list_index();
//int list_count();
/* sort, reverse? */

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write list_append(l, data) and this macro will expand sizeof for you.
 */
#define list_append(l, data) list_append(l, data, sizeof(data))
#define list_prepend(l, data) list_prepend(l, data, sizeof(data))
#define list_insert(l, i, data) list_append(l, i, data, sizeof(data))

#endif /* _LIST_H_ */

