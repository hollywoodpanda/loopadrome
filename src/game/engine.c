#define _POSIX_C_SOURCE 199309L

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "list.h"

int compare_systems (ecs_system* system_a, ecs_system* system_b)
{
    return strcmp(system_a->name, system_b->name);
}

int compare_entities (ecs_entity* entity_a, ecs_entity* entity_b)
{
    if (entity_a->id > entity_b->id)
    {
        return 1;
    }
    else if (entity_a->id < entity_b->id)
    {
        return -1;
    }

    return 0;
}

int compare_components (ecs_component* component_a, ecs_component* component_b)
{
    return strcmp(component_a->name, component_b->name);
}

eng_context* eng_create_context (bool (*eng_shutdown_fn)(void))
{
    eng_context* ctx = malloc(sizeof(eng_context));
    ctx->systems = list_create();
    ctx->entities = list_create();
    ctx->eng_shutdown_fn = eng_shutdown_fn;

    return ctx;
}

void eng_destroy_context (eng_context* ctx)
{
    for (size_t i = 0; i < ctx->systems->size; i++)
    {
        ecs_system* system = list_get(i, ctx->systems);
        ecs_free_system(system);
    }

    for (size_t i = 0; i < ctx->entities->size; i++)
    {
        ecs_entity* entity = list_get(i, ctx->entities);
        ecs_free_entity(entity);
    }

    list_destroy(ctx->systems);
    list_destroy(ctx->entities);
    free(ctx);
}

void eng_add_system (eng_context* ctx, ecs_system* system)
{
    list_add(system, ctx->systems);
}

void eng_remove_system (eng_context* ctx, ecs_system* system)
{
    list_remove(system, ctx->systems, (int (*)(void*, void*)) &compare_systems);
}

void eng_update_systems (eng_context* ctx, float delta_time)
{
    for (size_t i = 0; i < ctx->systems->size; i++)
    {
        ecs_system* system = list_get(i, ctx->systems);
        if (system->active)
        {
            system->execute(ctx, delta_time);
        }
    }
}

ecs_system* eng_find_system (eng_context* ctx, char* name)
{
    for (size_t i = 0; i < ctx->systems->size; i++)
    {
        ecs_system* system = list_get(i, ctx->systems);
        if (strcmp(system->name, name) == 0)
        {
            return system;
        }
    }

    return NULL;
}

void eng_add_entity (eng_context* ctx, ecs_entity* entity)
{
    list_add(entity, ctx->entities);
}

void eng_remove_entity (eng_context* ctx, ecs_entity* entity)
{
    list_remove(entity, ctx->entities, (int (*)(void*, void*)) &compare_entities);
}

ecs_entity* eng_find_entity (eng_context* ctx, int id)
{
    for (size_t i = 0; i < ctx->entities->size; i++)
    {
        ecs_entity* entity = list_get(i, ctx->entities);
        if (entity->id == id)
        {
            return entity;
        }
    }

    return NULL;
}

void eng_add_component (ecs_entity* entity, ecs_component* component)
{
    list_add(component, entity->components);
}

void eng_remove_component (ecs_entity* entity, ecs_component* component)
{
    ecs_remove_component(entity, component);
    list_remove(component, entity->components, (int (*)(void*, void*)) &compare_components);
}

ecs_component* eng_find_component (ecs_entity* entity, char* name)
{
    for (size_t i = 0; i < entity->components->size; i++)
    {
        ecs_component* component = list_get(i, entity->components);
        if (strcmp(component->name, name) == 0)
        {
            return component;
        }
    }

    return NULL;
}

list* eng_find_components (eng_context* ctx, char* name)
{
    list* components = list_create();
    for (size_t i = 0; i < ctx->entities->size; i++)
    {
        ecs_entity* entity = list_get(i, ctx->entities);
        for (size_t j = 0; j < entity->components->size; j++)
        {
            ecs_component* component = list_get(j, entity->components);
            if (strcmp(component->name, name) == 0)
            {
                list_add(component, components);
            }
        }
    }

    return components;
}

void eng_start (eng_context* ctx)
{
    for (size_t i = 0; i < ctx->systems->size; i++)
    {
        ecs_system* system = list_get(i, ctx->systems);
        system->start();
    }
}

void eng_run (eng_context* ctx)
{
    struct timespec start, end;
    float delta_time;
    while (!ctx->eng_shutdown_fn())
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        eng_update_systems(ctx, delta_time);
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    }
}