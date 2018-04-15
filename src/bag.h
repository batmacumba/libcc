/*******************************************************************************
 * Bag: collection of objects
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
Bag *Bag_new();                                         // constructor
int Bag_isEmpty(Bag *b);                                // is bag empty?
int Bag_size(Bag *b);                                   // returns bag's size
int Bag_add(Bag *b, void *data, size_t dataSize);       // adds an item
void **Bag_iterator(Bag *b);                            // iterator
void  Bag_unitTest();                                   // test

/* Let's avoid having to pass sizeof(x) as argument every time we add something.
 * Instead write Bag_add(b, data) and this macro will expand sizeof for you.
 */
#define Bag_add(b, data) Bag_add(b, data, sizeof(data))

#endif /* _BAG_H_ */
