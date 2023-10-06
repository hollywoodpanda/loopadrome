#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "./entity.h"

typedef void (*ecs_system_function)(float delta_time, ...);

typedef struct ecs_system {
    ecs_system_function execute;
} ecs_system;

ecs_system *ecs_create_system (ecs_system_function execute);

void ecs_free_system (ecs_system *system);

#endif