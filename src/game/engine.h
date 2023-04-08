#ifndef engine_ENGINE_H
#define engine_ENGINE_H

#include "../ecs/entity.h"
#include "../ecs/system.h"
#include "../ecs/component.h"

void engine_start ();

void engine_add_entity (Entity *entity);
Entity *engine_remove_entity (int id);

void engine_add_system (System *system);
void engine_remove_system (char *name);
void engine_start_system (char *name);
void engine_stop_system (char *name);

void engine_add_component (int entity_id, Component *component);
void *engine_remove_component (int entity_id, char *component_name);
void *engine_remove_all_components (char *component_name);
Component **engine_get_components_by_name (char *component_name);
Component **engine_get_components_by_entity (int entity_id);
Component *engine_get_component (int entity_id, char *component_name);

void engine_update (float delta_time);

#endif