/******************************************************************************
 * Dinamically resized array (C++-like vector)
 * Dependencies: none
 ******************************************************************************/

/* ifndef guard */
#ifndef _VECTOR_H_
#define _VECTOR_H_

/* DATA STRUCTURE */
typedef struct Vector Vector;

/* FUNCTIONS */
Vector *Vector_new();
int Vector_pushBack(Vector *v, void *new_data);
int Vector_popBack(Vector *v);
void Vector_destroy(Vector *v);
void Vector_unitTest();

#endif /* _VECTOR_H_ */
