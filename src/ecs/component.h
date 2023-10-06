#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

typedef struct ecs_component {
    char *name;
    void *data;
} ecs_component;

ecs_component *ecs_create_component (char *name, void *data);

void ecs_free_component (ecs_component *component);

#endif