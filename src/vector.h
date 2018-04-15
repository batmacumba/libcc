/*******************************************************************************
 * Vector: dinamically resized array (C++-like vector)
 * Dependencies: stdio.h, stdlib.h, string.h
 * Compilation:
     $ make vector.o
     $ gcc file.c vector.o -o file
 * Include this header in your file
 ******************************************************************************/

#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct Vector Vector;

/*
 * Available operations
 */
Vector *Vector_new();                                       // constructor
int Vector_pushBack(Vector *v, void *new_data);             // pushes an item
int Vector_popBack(Vector *v);                              // pops an item
void Vector_destroy(Vector *v);                             // free
void Vector_unitTest();                                     // test

#endif /* _VECTOR_H_ */
