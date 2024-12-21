#include <stdlib.h>
#include <stdio.h>
#include "list.h"

static inline int float_to_int (float value)
{
    return value >= 0 ? (int)(value + 0.5f) : (int)(value - 0.5f);
}

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
        printf("[Loopadrome][List] Resizing list with capacity %ld\r\n", list->capacity);
        list->capacity = float_to_int(list->capacity * CAPACITY_GROWTH_FACTOR);
        printf("[Loopadrome][List] New capacity: %ld\r\n", list->capacity);
        void** temp_data = (void**) realloc(list->data, sizeof(void*) * list->capacity);
        if (temp_data == NULL)
        {
            printf("[Loopadrome][List] Failed to reallocate memory for list\r\n");
            return;
        }
        list->data = temp_data;
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