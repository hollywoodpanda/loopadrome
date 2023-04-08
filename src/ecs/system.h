#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "./entity.h"

typedef void (*ecs_update_system_function)(float delta_time);

typedef struct System {
    char *name;
    int is_active;
    ecs_update_system_function update;
} System;

System *ecs_create_system (char *name, ecs_update_system_function update);

void ecs_free_system (System *system);

#endif