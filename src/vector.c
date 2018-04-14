/* includes & macros */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct Vector {
    void** items;
    int capacity; //allocated storage capacity
    int size; //number of inserted elements
};

/**
 * Initializes an empty vector and returns a pointer to it.
 */
Vector *Vector_new()
{
    Vector *v = (Vector*) malloc(sizeof(Vector));
    if (!v) {
        fprintf(stderr, "Vector_new: Cannot create new vector!\n");
        return NULL;
    }
    v->items = (void**)malloc(sizeof(void*));
    v->size = 0;
    v->capacity = 1;
    return v;
}

/**
 * Resizes the vector so its capacity is new_size.
 * Returns 0 if item was succesfully resized and 1 otherwise.
 * If resizing is not sucessfull, vector remains unaltered.
 */
int Vector_resize(Vector *v, int new_size)
{
    void** items_tmp = (void**)realloc(v->items, new_size*sizeof(void*));
    if(!items_tmp) {
        fprintf(stderr, "Vector_resize: Cannot resize vector!\n");
        return 1;
    }
    v->items = items_tmp;
    v->capacity = new_size;
    return 0;
}

/**
 * Adds the item to the end of the vector.
 * Returns 0 if item was succesfully added and 1 otherwise.
 */
int Vector_pushBack(Vector *v, void *new_data) {
    if(v->size == v->capacity) {
        if (Vector_resize(v, 2*v->capacity)) {
            fprintf(stderr, "Vector_pushBack: Cannot append to vector!\n");
            return 1;
        }
    }
    v->items[v->size++] = new_data;
    return 0;
}

/**
 * Removes the item at the end of the vector.
 * Returns 0 if item was succesfully removed and 1 otherwise.
 */
int Vector_popBack(Vector *v) {
    if(v->size == 0) {
        fprintf(stderr, "Vector_popBack: vector is already empty!\n");
        return 1;
    }
    v->size--;
    return 0;
}

/**
 * Destroys a vector, freeing all the allocated memory it is using
 */
void Vector_destroy(Vector *v) {
        free(v->items);
        free(v);
        v = NULL;
}

void Vector_unitTest() {
    Vector *v = Vector_new();
    int *pointer;
    int tmp1 = 1;
    int tmp2 = 2;
    int tmp3 = 3;
    int tmp4 = 4;
    int tmp5 = 5;
    pointer = &tmp1;
    Vector_pushBack(v, pointer);
    pointer = &tmp2;
    Vector_pushBack(v, pointer);
    pointer = &tmp3;
    Vector_pushBack(v, pointer);
    pointer = &tmp4;
    Vector_pushBack(v, pointer);
    pointer = &tmp5;
    Vector_pushBack(v, pointer);

    printf("After 5 pushBack calls: \n");
    printf("Size: %d\n", v->size);
    printf("Capacity: %d\n", v->capacity);

    printf("Vector items: [");
    printf("%d", *(int*)(v->items[0]));
    for(int i = 1; i < v->size; i++) {
        printf(", %d", *(int*)(v->items[i]));
    }
    printf("]\n");

    Vector_popBack(v);
    Vector_popBack(v);

    printf("\nAfter 2 popBack calls: \n");
    printf("Size: %d\n", v->size);
    printf("Capacity: %d\n", v->capacity);

    printf("Vector items: [");
    printf("%d", *(int*)(v->items[0]));
    for(int i = 1; i < v->size; i++) {
        printf(", %d", *(int*)(v->items[i]));
    }
    printf("]\n");

    Vector_destroy(v);
}
