/*
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"

#undef bag_add

/*
 * Data Structures
 */
typedef struct Item {
    void *data;
    struct Item *next;
} Item;

struct Bag {
    Item *top;
    int size;
};

/*
 * bag_new():
 * Initializes an empty bag and returns a pointer to it.
 */
Bag *bag_new() {
    Bag *b = (Bag*) malloc(sizeof(Bag));
    if (!b) {
        fprintf(stderr, "bag_new: cannot create new bag!\n");
        return NULL;
    }
    b -> top = NULL;
    b -> size = 0;
    return b;
}

/*
 * bag_isEmpty():
 * Returns 1 if this bag is empty, 0 if it's not.
 */
int bag_isEmpty(Bag *b) {
    if (b -> top == NULL) return 1;
    else return 0;
}

/*
 * bag_size():
 * Returns the number of items on this bag.
 */
int bag_size(Bag *b) {
    return b -> size;
}

/*
 * B_Item_new():
 * Initializes an empty Item.
 */
Item *B_Item_new(size_t dataSize) {
    Item *i = (Item*) malloc(sizeof(Item));
    if (!i) {
        fprintf(stderr, "B_Item_new: cannot malloc new item!\n");
        return NULL;
    }
    i -> data = malloc(dataSize);
    if (!i -> data) {
        fprintf(stderr, "B_Item_new: cannot malloc space for data!\n");
        return NULL;
    }
    i -> next = NULL;
    return i;
}

/*
 * bag_add():
 * Copies the data and adds it to the bag.
 * Returns 0 if item was succesfully added or 1 otherwise.
 */
int bag_add(Bag *b, void *data, size_t dataSize) {
    Item *i = B_Item_new(dataSize);
    if (i == NULL) {
        fprintf(stderr, "bag_add: cannot create new item!\n");
        return 1;
    }
    memcpy(i -> data, data, dataSize);
    i -> next = b -> top;
    b -> top = i;
    b -> size++;
    return 0;
}

/*
 * bag_iterator():
 * Copies every item in the bag and returns an array of items.
 */
void **bag_iterator(Bag *b) {
    if (bag_isEmpty(b) == 1) {
        fprintf(stderr, "bag_iterator: bag is empty!\n");
        return NULL;
    }
    void **items = (malloc(sizeof(void*) * b -> size));
    Item *i = b -> top;
    int k = 0;
    while (k < b -> size) {
        items[k] = i -> data;
        i = i -> next;
        k++;
    }
    return items;
}

/*
 * bag_destroy():
 * Destroys a bag, freeing all it's allocated memory.
 */
void bag_destroy(Bag *b) {
    if (!bag_isEmpty(b)) {
        Item *i = b -> top;
        while (i != NULL) {
            /* top of the bag points to next element */
            b -> top = i -> next;
            free(i -> data);
            free(i);
            i = b -> top;
        }
    }
    free(b);
}

/*
 * bag_unitTest():
 * Unit test.
 */
void bag_unitTest() {
    puts("bag_unitTest()");
    Bag *bag = bag_new();
    int *pointer;
    int tmp1 = 1;
    int tmp2 = 2;
    int tmp3 = 3;
    pointer = &tmp1;
    bag_add(bag, pointer, sizeof(*pointer));
    pointer = &tmp2;
    bag_add(bag, pointer, sizeof(*pointer));
    pointer = &tmp3;
    bag_add(bag, pointer, sizeof(*pointer));

    int **bag_items = (int**) bag_iterator(bag);
    for (int i = 0; i < bag_size(bag); i++) {
        printf("item %d = %d\n", i, *bag_items[i]);
    }
    puts("");
    bag_destroy(bag);
}

