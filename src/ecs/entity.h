#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

typedef struct ecs_entity {
    int id;
} ecs_entity;

ecs_entity *ecs_create_entity (int id);

void ecs_free_entity (ecs_entity *entity);

#endif