#include <stdlib.h>
#include <string.h>

#include "component.h"

ecs_component *ecs_create_component (char *name, void *data) 
{
    ecs_component *component = malloc(sizeof(ecs_component));
    component->name = name;
    component->data = data;
    return component;
}

void ecs_free_component (ecs_component *component)
{
    // Freeing the data is the responsability
    // of the user of the library, not the library itself.
    // We don't know the type of the data or if it is freeable at all.

    // free(component->data); //Causing "pointer being freed was not allocated"
    
    free(component);
}
