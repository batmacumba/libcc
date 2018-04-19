/*******************************************************************************
 * Bag: collection of non-unique elements
 * Dependencies: stdio.h, stdlib.h, string.h
 * Compilation:
     $ make bag.o
     $ gcc file.c bag.o -o file
 * Include this header in your file
 ******************************************************************************/

#ifndef _BAG_H_
#define _BAG_H_

typedef struct Bag Bag;

/*
 * Available operations
 */
Bag *bag_new();                                         // constructor
int bag_isEmpty(Bag *b);                                // is bag empty?
int bag_size(Bag *b);                                   // returns bag's size
int bag_add(Bag *b, void *data, size_t dataSize);       // adds an item
void **bag_iterator(Bag *b);                            // iterator
void bag_unitTest();                                    // test
void bag_destroy(Bag *b);                               // frees memory

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write bag_add(b, data) and this macro will expand sizeof for you.
 */
#define bag_add(b, data) bag_add(b, data, sizeof(data))

#endif /* _BAG_H_ */
