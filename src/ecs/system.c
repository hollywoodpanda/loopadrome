#include <stdlib.h>

#include "system.h"

ecs_system *ecs_create_system (
    char* name,
    ecs_system_start_function start,
    ecs_system_function execute,
    bool active
) {
    ecs_system *system = malloc(sizeof(ecs_system));
    system->name = name;
    system->start = start;
    system->execute = execute;
    system->active = active;
    return system;
}

void ecs_free_system (ecs_system *system) 
{
    free(system);
}