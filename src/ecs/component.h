#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

typedef struct Component {
    char *name;
    void *data;
} Component;

Component *ecs_create_component (char *name, void *data);

void ecs_free_component (Component *component);

#endif