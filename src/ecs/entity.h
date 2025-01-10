#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include "component.h"
#include "../data/list.h"

typedef struct ecs_entity {
    int id;
    list* components;
} ecs_entity;

ecs_entity *ecs_create_entity (int id);

void ecs_free_entity (ecs_entity *entity);

void ecs_add_component (ecs_entity* entity, ecs_component* component);
void ecs_remove_component (ecs_entity* entity, ecs_component* component);

#endif