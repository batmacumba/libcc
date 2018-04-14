/* includes & macros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"

#undef Bag_add

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
    Bag *b = (Bag*) malloc(sizeof(Bag));
    if (!b) {
        fprintf(stderr, "Bag_new: Cannot create new bag!\n");
        return NULL;
    }
    b -> top = NULL;
    b -> size = 0;
    
    return b;
}

/**
 * Returns 1 if this bag is empty, 0 if it's not.
 */
int Bag_isEmpty(Bag *b) {
    if (b -> top == NULL) return 1;
    else return 0;
}

/**
 * Returns the number of items on this bag.
 */
int Bag_size(Bag *b) {
    return b -> size;
}

/**
 * Initializes an empty Item.
 */
Item *Item_new(size_t dataSize) {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "Item_new: Cannot create new item!\n");
        return NULL;
    }
    i -> data = malloc(dataSize);
    i -> next = NULL;
    return i;
}

/**
 * Copies the data and adds it to the bag.
 */
void Bag_add(Bag *b, void *data, size_t dataSize) {
    Item *i = Item_new(dataSize);
    memcpy(i -> data, data, dataSize);
    i -> next = b -> top;
    b -> top = i;
    b -> size++;
}

/**
 * Copies all the items in the bag and returns an array of items.
 */
void **Bag_iterator(Bag *b) {
    if (Bag_isEmpty(b) == 1) {
        fprintf(stderr, "Bag_iterator: Bag is empty!\n");
        return NULL;
    }
    void **bag_items = (malloc(sizeof(void*) * b -> size));
    Item *current_item = b -> top;
    int i = 0;
    while (current_item != NULL) {
        bag_items[i] = current_item -> data;
        current_item = current_item -> next;
        i++;
    }
    return bag_items;
}

/* test */
void Bag_unitTest() {
    Bag *bag = Bag_new();
    int *pointer;
    int tmp1 = 1;
    int tmp2 = 2;
    int tmp3 = 3;
    pointer = &tmp1;
    Bag_add(bag, pointer, sizeof(*pointer));
    pointer = &tmp2;
    Bag_add(bag, pointer, sizeof(*pointer));
    pointer = &tmp3;
    Bag_add(bag, pointer, sizeof(*pointer));

    int **bag_items = (int**) Bag_iterator(bag);
    for (int i = 0; i < Bag_size(bag); i++) {
        printf("item %d = %d\n", i, *bag_items[i]);
    }
}

