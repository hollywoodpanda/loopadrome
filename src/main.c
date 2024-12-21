#include <stdio.h>
#include <stdbool.h>
#include "game/engine.h"

#define WINDOW_ENTITY 1
#define SIZE_COMPONENT "size"
#define TITLE_COMPONENT "title"

typedef struct comp_size
{
    int width;
    int height;
} comp_size;

int iterations = 0;
bool already_iterated = false;

bool shutdown_game_engine (void)
{
    if (iterations < 10)
    {
        iterations++;
        return false;
    }
    printf("[Loopadrome][Engine] Shutting down engine\r\n");
    return true;
}

void start_window_system (void)
{
    printf("[Loopadrome][System] Starting window system\r\n");
}

void update_window_system (eng_context* ctx, float delta_time)
{

    if (ctx == NULL)
    {
        return;
    }

    if (iterations > 5)
    {
        ecs_entity* entity = eng_find_entity(ctx, WINDOW_ENTITY);

        if (entity != NULL)
        {

            ecs_component* component = eng_find_component(entity, TITLE_COMPONENT);

            if (component != NULL)
            {
                printf("[Loopadrome][System] Found window title component to remove from entity: \"%s\"\r\n", (char*)component->data);
                eng_remove_component(entity, component);
            }
        }        
    }

    list* found_size_comps = eng_find_components(ctx, SIZE_COMPONENT);

    if (found_size_comps != NULL)
    {
        for (size_t i = 0; i < found_size_comps->size; i++)
        {
            ecs_component* comp = list_get(i, found_size_comps);
            printf("[Loopadrome][System] Found window_size component in list: (w:%d,h:%d)\r\n", ((comp_size*)comp->data)->width, ((comp_size*)comp->data)->height);
        }
    }

    list* found_title_comps = eng_find_components(ctx, TITLE_COMPONENT);

    if (found_title_comps != NULL)
    {
        for (size_t i = 0; i < found_title_comps->size; i++)
        {
            ecs_component* comp = list_get(i, found_title_comps);
            printf("[Loopadrome][System] Found window_title component in list: \"%s\"\r\n", (char*)comp->data);
        }
    }

    ecs_entity* window_entity = eng_find_entity(ctx, WINDOW_ENTITY);

    if (window_entity != NULL)
    {
        printf("[Loopadrome][System] Found window entity %d with %ld component(s) in it\r\n", window_entity->id, window_entity->components->size);
    }

    printf("[Loopadrome][System] My wife is so dumb that delta_time %.10f is greater than her IQ!\r\n", delta_time);
}

int main(int argc, char const *argv[]) 
{
    printf("[Loopadrome][Main] Starting main\r\n");

    size_t argc_size = (size_t) argc;
    for (size_t i = 0; i < argc_size; i++)
    {
        printf("[Loopadrome][Main] argv[%ld] %s\r\n", i, argv[i]);
    }

    eng_context* ctx = eng_create_context(&shutdown_game_engine);

    comp_size* size = malloc(sizeof(comp_size));
    size->width = 800;
    size->height = 600;

    ecs_component* window_size_component = ecs_create_component(SIZE_COMPONENT, size);
    ecs_component* window_title_component = ecs_create_component(TITLE_COMPONENT, "Loopadrome");

    printf("[Loopadrome][Main] Window %d width and %d height\r\n", ((comp_size*)window_size_component->data)->width, ((comp_size*)window_size_component->data)->height);
    printf("[Loopadrome][Main] Window title %s\r\n", (char*)window_title_component->data);

    ecs_entity* window_entity = ecs_create_entity(WINDOW_ENTITY);
    printf("[Loopadrome][Main] Window entity id %d\r\n", window_entity->id);
    ecs_add_component(window_entity, window_size_component);
    ecs_add_component(window_entity, window_title_component);
    printf("[Loopadrome][Main] Window entity components %ld\r\n", window_entity->components->size);

    eng_add_entity(ctx, window_entity);
    printf("[Loopadrome][Main] Entities %ld\r\n", ctx->entities->size);

    ecs_system* window_system = ecs_create_system("window_system", &start_window_system, &update_window_system, true);

    eng_add_system(ctx, window_system);
    printf("[Loopadrome][Main] Systems %ld\r\n", ctx->systems->size);

    eng_start(ctx);
    eng_run(ctx);

    eng_destroy_context(ctx);

}
