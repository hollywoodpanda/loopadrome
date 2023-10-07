#include <stdlib.h>

#include "./system.h"

ecs_system *ecs_create_system (ecs_system_function execute)
{
    ecs_system *system = malloc(sizeof(ecs_system));
    system->execute = execute;
    return system;
}

void ecs_free_system (ecs_system *system) 
{
    free(system);
}