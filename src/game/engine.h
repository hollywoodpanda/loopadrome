#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>
#include "../ecs/system.h"
#include "../ecs/entity.h"

typedef struct eng_context {
    list* systems;
    list* entities;
    bool (*eng_shutdown_fn)(void);
} eng_context;

eng_context* eng_create_context (bool (*)(void));
void eng_destroy_context (eng_context* ctx);

void eng_add_system (eng_context* ctx, ecs_system *system);
void eng_remove_system (eng_context* ctx, ecs_system *system);
void eng_update_systems (eng_context* ctx, float delta_time);
ecs_system* eng_find_system (eng_context* ctx, char* name);

void eng_start (eng_context* ctx);
void eng_run (eng_context* ctx);

void eng_add_entity (eng_context* ctx, ecs_entity *entity);
void eng_remove_entity (eng_context* ctx, ecs_entity *entity);
ecs_entity* eng_find_entity (eng_context* ctx, int id);

void eng_add_component (ecs_entity* entity, ecs_component* component);
void eng_remove_component (ecs_entity* entity, ecs_component* component);
ecs_component* eng_find_component (ecs_entity* entity, char* name);
list* eng_find_components (eng_context* ctx, char* name);

#endif