#include <stdlib.h>

#include "./system.h"
#include "../constants.h"

System *ecs_create_system (char *name, ecs_update_system_function update)
{
    System *system = malloc(sizeof(System));
    system->name = name;
    system->is_active = TRUE;
    system->update = update;
    return system;
}

void ecs_free_system (System *system) 
{
    free(system);
}