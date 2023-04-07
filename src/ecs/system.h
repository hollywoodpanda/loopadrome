#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "./entity.h"

typedef void (*ecs_system_function)(float delta_time);

typedef struct System {
    ecs_system_function execute;
} System;

System *ecs_create_system (ecs_system_function execute);

void ecs_free_system (System *system);

#endif