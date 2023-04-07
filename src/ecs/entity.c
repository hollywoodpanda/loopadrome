#include <stdlib.h>

#include "entity.h"

Entity *ecs_create_entity (int id) 
{
    Entity *entity = malloc(sizeof(Entity));
    entity->id = id;
    return entity;
}

void ecs_free_entity (Entity *entity) 
{
    free(entity);
}