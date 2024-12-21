#include <stdlib.h>
#include <stdio.h>
#include "list.h"

list* list_create (void)
{
    list* list = (struct list*) malloc(sizeof(struct list));
    list->data = (void**) malloc(sizeof(void*) * INITIAL_CAPACITY);
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;

    return list;
}

void list_destroy (list* list)
{
    free(list->data);
    free(list);
}

void list_add (void* data, list* list)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->data = (void**) realloc(list->data, sizeof(void*) * list->capacity);
    }

    list->data[list->size++] = data;
}

void list_remove (void* data, list* list, int (*compare_fn)(void* value_a, void* value_b))
{
    size_t i;
    for (i = 0; i < list->size; i++)
    {
        if (compare_fn(data, list->data[i]) == 0) {
            break;
        }
    }

    if (i == list->size)
    {
        return;
    }

    for (; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
}

void* list_get (size_t index, list* list)
{
    if (index >= list->size)
    {
        return NULL;
    }

    return list->data[index];
}