#include <stdlib.h>

#include "entity.h"

ecs_entity *ecs_create_entity (int id) 
{
    ecs_entity *entity = malloc(sizeof(ecs_entity));
    entity->id = id;
    return entity;
}

void ecs_free_entity (ecs_entity *entity) 
{
    free(entity);
}