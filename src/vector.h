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
Vector *Vector_new();                                               // construct
int Vector_pushBack(Vector *v, void *new_data, size_t dataSize);    // pushes
int Vector_popBack(Vector *v);                                      // pops
void Vector_destroy(Vector *v);                                     // free
void Vector_unitTest();                                             // test

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write Vector_pushBack(v, data) and this macro will expand sizeof.
 */
#define Vector_pushBack(v, data) Vector_pushBack(v, data, sizeof(data))

#endif /* _VECTOR_H_ */
