#include <stdlib.h>

#include "../ecs/entity.h"
#include "../ecs/system.h"
#include "../ecs/component.h"

#include "hashmap.h"

#include "../constants.h"

HashMap *entities;

HashMap *systems;

HashMap *components;

void engine_start ()
{
    entities = hashmap_create(100);
    systems = hashmap_create(100);
    components = hashmap_create(100);
}

void engine_add_entity (Entity *entity)
{
    hashmap_put(entities, entity->id, entity);
}

Entity *engine_remove_entity (int id)
{
    Entity *saved_entity = hashmap_get(entities, &id);

    if (saved_entity == NULL) {
        return NULL;
    }

    Entity *return_entity = malloc(sizeof(Entity));
    return_entity->id = saved_entity->id;

    hashmap_remove(entities, &id);

    return return_entity;
}

void engine_add_system (System *system)
{
    hashmap_put(systems, system->name, system);
}

void engine_remove_system (char *name)
{
    hashmap_remove(systems, name);
}

void engine_start_system (char *name) 
{
    System *system = hashmap_get(systems, name);

    if (system == NULL) {
        return;
    }

    system->is_active = TRUE;

}

void engine_stop_system (char *name)
{

    System *system = hashmap_get(systems, name);

    if (system == NULL) {
        return;
    }

    system->is_active = FALSE;

}

void engine_add_component (int entity_id, Component *component)
{
    hashmap_put(components, entity_id, component);
}

void engine_remove_component (int entity_id, char *component_name)
{
    hashmap_remove(components, entity_id);
}

void *engine_remove_all_components (char *component_name)
{
    
}

Component **engine_get_components_by_name (char *component_name)
{

}

Component **engine_get_components_by_entity (int entity_id)
{

}

Component *engine_get_component (int entity_id, char *component_name)
{

}

void engine_update (float delta_time)
{

}