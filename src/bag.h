/******************************************************************************
 *  Dependencies: none
 ******************************************************************************/

/* ifndef guard */
#ifndef _BAG_H_
#define _BAG_H_

/* DATA STRUCTURE */
typedef struct Bag Bag;

/* FUNCTIONS */
Bag *Bag_new();
int Bag_isEmpty(Bag *s);
int Bag_size(Bag *s);
void Bag_add(Bag *s, void *new_data);
void **Bag_iterator(Bag *s);
void  Bag_unitTest();

#endif /* _BAG_H_ */
