#ifndef GAME_LIST_H
#define GAME_LIST_H

#define INITIAL_CAPACITY 1
#define CAPACITY_GROWTH_FACTOR 1.5f

#include <stdlib.h>

typedef struct list {
    void** data;
    size_t size;
    size_t capacity;
} list;

list *list_create (void);
void list_destroy (list *list);

void list_add (void *data, list *list);
void list_remove (void *data, list *list, int (*compare_fn)(void *value_a, void *value_b));
void* list_get (size_t index, list* list);

#endif