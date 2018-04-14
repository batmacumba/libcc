/******************************************************************************
 *  Dependencies: stdio.h, stdlib.h, string.h
 ******************************************************************************/

/* ifndef guard */
#ifndef _BAG_H_
#define _BAG_H_

/* DATA STRUCTURE */
typedef struct Bag Bag;

/* FUNCTIONS */
Bag *Bag_new();
int Bag_isEmpty(Bag *b);
int Bag_size(Bag *b);
void Bag_add(Bag *b, void *data, size_t dataSize);
void **Bag_iterator(Bag *b);
void  Bag_unitTest();

// Macro to avoid typing sizeof:
#define Bag_add(b, data) Bag_add(b, data, sizeof(data))

#endif /* _BAG_H_ */
