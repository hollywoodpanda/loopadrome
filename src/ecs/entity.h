#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

typedef struct Entity {
    int id;
} Entity;

Entity *ecs_create_entity (int id);

void ecs_free_entity (Entity *entity);

#endif