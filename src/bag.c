/* includes & macros */
#include <stdio.h>
#include <stdlib.h>
#include "bag.h"

/* bag implementation (hidden from clients) */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Bag {
    Item *top;
    int size;
};

/* functions */

/**
 * Initializes an empty bag and returns a pointer to it.
 */
Bag *Bag_new() {
    Bag *s = (Bag*) malloc(sizeof(Bag));
    if (!s) {
        fprintf(stderr, "Bag_new: Cannot create new bag!\n");
        return NULL;
    }
    s -> top = NULL;
    s -> size = 0;
    return s;
}

/**
 * Returns 1 if this bag is empty, 0 if it's not.
 */
int Bag_isEmpty(Bag *s) {
    if (s -> top == NULL) return 1;
    else return 0;
}

/**
 * Returns the number of items on this bag.
 */
int Bag_size(Bag *s) {
    return s -> size;
}

/**
 * Initializes an empty Item.
 */
Item *Item_new() {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Item_new: Cannot create new item!\n");
        return NULL;
    }
    i -> data = NULL;
    i -> next = NULL;
    return i;
}

/**
 * Adds the item to the bag.
 */
void Bag_add(Bag *s, void *new_data) {
    Item *new_item = Item_new();
    new_item -> data = new_data;
    new_item -> next = s -> top;
    s -> top = new_item;
    s -> size++;
}

/**
 * Copies all the items in the bag and returns an array of items.
 */
void **Bag_iterator(Bag *s) {
    if (Bag_isEmpty(s) == 1) {
        fprintf(stderr, "Bag_iterator: Bag is empty!\n");
        return NULL;
    }
    void **bag_items = (malloc(sizeof(void*) * s -> size));
    Item *current_item = s -> top;
    int i = 0;
    while (current_item != NULL) {
        bag_items[i] = current_item -> data;
        current_item = current_item -> next;
        i++;
    }
    return bag_items;
}

/* test */
void  Bag_unitTest() {
    Bag *bag = Bag_new();
    int *pointer;
    int tmp1 = 1;
    int tmp2 = 2;
    int tmp3 = 3;
    pointer = &tmp1;
    Bag_add(bag, pointer);
    pointer = &tmp2;
    Bag_add(bag, pointer);
    pointer = &tmp3;
    Bag_add(bag, pointer);

    int **bag_items = (int**) Bag_iterator(bag);
    for (int i = 0; i < Bag_size(bag); i++) {
        printf("item %d = %d\n", i, *bag_items[i]);
    }
}
