/* includes e macros */
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
        fprintf(stderr, "Cannot create new bag!\n");
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
        fprintf(stderr, "Cannot create new item!\n");
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
 * Returns an array of pointers to all the items on the bag.
 */
void **Bag_iterator(Bag *s) {
    if (Bag_isEmpty(s) == 1) {
        fprintf(stderr, "Bag is empty!\n");
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
int main() {
    Bag *bag = Bag_new();
    Bag_add(bag, "teste3");
    Bag_add(bag, "teste2");
    Bag_add(bag, "teste1");
    
    int **bag_items = malloc(sizeof(void*) * Bag_size(bag));
    bag_items = (int**) Bag_iterator(bag);
    for (int i = 0; i < Bag_size(bag); i++) {
        printf("item %d = %s\n", i, bag_items[i]);
    }
    return 0;
}

