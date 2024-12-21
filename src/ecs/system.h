#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include <stdbool.h>
#include "entity.h"

typedef struct eng_context eng_context; // Forward declaration

typedef void (*ecs_system_start_function)(void);

typedef void (*ecs_system_function)(eng_context* ctx, float delta_time);

typedef struct ecs_system {
    char* name;
    ecs_system_start_function start;
    ecs_system_function execute;
    bool active;
} ecs_system;

ecs_system *ecs_create_system (
    char* name,
    ecs_system_start_function start,
    ecs_system_function execute,
    bool active
);

void ecs_free_system (ecs_system *system);

#endif