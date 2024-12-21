#include <stdlib.h>
#include "string.h"

#include "entity.h"

int ecs_compare_components (ecs_component* a, ecs_component* b)
{
    return strcmp(a->name, b->name);
}

ecs_entity *ecs_create_entity (int id) 
{
    ecs_entity *entity = malloc(sizeof(ecs_entity));
    entity->id = id;
    entity->components = list_create();
    return entity;
}

void ecs_free_entity (ecs_entity *entity) 
{
    for (size_t i = 0; i < entity->components->size; i++)
    {
        ecs_component* component = list_get(i, entity->components);
        ecs_free_component(component);
    }
    list_destroy(entity->components);
    free(entity);
}

void ecs_add_component (ecs_entity *entity, ecs_component* component)
{
    list_add(component, entity->components);
}

void ecs_remove_component (ecs_entity *entity, ecs_component* component)
{
    list_remove(component, entity->components, (int (*)(void*, void*)) &ecs_compare_components);
}
