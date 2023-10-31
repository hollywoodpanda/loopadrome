#include <stdlib.h>
#include <stdio.h>

#include "./system.h"

ecs_system *ecs_create_system (
    ecs_system_start_function start,
    ecs_system_function execute
) {
    ecs_system *system = malloc(sizeof(ecs_system));
    system->start = start;
    system->execute = execute;
    return system;
}

void ecs_free_system (ecs_system *system) 
{
    printf("[Loopadrome][System] Freeing system\r\n");
    free(system);
}