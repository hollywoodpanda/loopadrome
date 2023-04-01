#include <stdlib.h>
#include <string.h>

#include "component.h"

Component *create_component (char *name, void *data) 
{
    Component *component = malloc(sizeof(Component));
    component->name = name;
    component->data = data;
    return component;
}

void free_component (Component *component)
{
    free(component->data); //Causing "pointer being freed was not allocated"
    free(component);
}
