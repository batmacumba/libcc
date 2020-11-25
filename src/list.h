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

/* Data Structure */
typedef struct List List;

/* Operations */
List*   list_new();
void*   list_get(List *l, int i);
int     list_set(List *l, int i, void *data, size_t dataSize);
int     list_append(List *l, void *data, size_t dataSize);
int     list_prepend(List *l, void *data, size_t dataSize);
// int     list_insert(List *l, int i, void *data, size_t dataSize);
int     list_del(List *l, int i);
int     list_remove(List *l, void *data, int (compare)(void *, void *));
//int list_pop();
int 	list_contains(List *l, void *data, int (compare)(void *, void *));
int 	list_is_empty();
int 	list_length();
//int list_index();
/* sort, reverse? List[]?*/

/* Macros */
#define list_append(l, data) list_append(l, data, sizeof(data))
#define list_prepend(l, data) list_prepend(l, data, sizeof(data))
// #define list_insert(l, i, data) list_insert(l, i, data, sizeof(data))
#define list_set(l, i, data) list_set(l, i, data, sizeof(data))

#endif /* _LIST_H_ */

