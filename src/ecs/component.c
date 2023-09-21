#include <stdlib.h>
#include <string.h>

#include "component.h"

Component *ecs_create_component (char *name, void *data) 
{
    Component *component = malloc(sizeof(Component));
    component->name = name;
    component->data = data;
    return component;
}

void ecs_free_component (Component *component)
{
    // Freeing the data is the responsability
    // of the user of the library, not the library itself.
    // We don't know the type of the data or if it is freeable at all.

    // free(component->data); //Causing "pointer being freed was not allocated"
    
    free(component);
}
