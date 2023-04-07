#include <stdlib.h>

#include "./system.h"

System *ecs_create_system (ecs_system_function execute)
{
    System *system = malloc(sizeof(System));
    system->execute = execute;
    return system;
}

void ecs_free_system (System *system) 
{
    free(system);
}