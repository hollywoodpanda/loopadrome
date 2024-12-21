#include <stdio.h>
#include <stdbool.h>
#include "game/engine.h"

typedef struct comp_size
{
    int width;
    int height;
} comp_size;

int iterations = 0;
bool already_iterated = false;

bool shutdown_game_engine (void)
{
    if (iterations < 100)
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

void update_window_system (float delta_time)
{
    printf("[Loopadrome][System] Updating window system with delta time %.10f\r\n", delta_time);
}

int main(int argc, char const *argv[]) 
{

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    eng_context* ctx = eng_create_context(&shutdown_game_engine);

    comp_size* size = malloc(sizeof(comp_size));
    size->width = 800;
    size->height = 600;

    ecs_component* window_size = ecs_create_component("window_size", size);

    printf("[Loopadrome][Main] Window %d width and %d height\r\n", ((comp_size*)window_size->data)->width, ((comp_size*)window_size->data)->height);

    ecs_entity* window = ecs_create_entity(1);
    printf("[Loopadrome][Main] Window entity id %d\r\n", window->id);
    ecs_add_component(window, window_size);
    printf("[Loopadrome][Main] Window entity components %d\r\n", window->components->size);

    eng_add_entity(ctx, window);
    printf("[Loopadrome][Main] Entities %d\r\n", ctx->entities->size);

    eng_add_system(ctx, ecs_create_system("window", &start_window_system, &update_window_system, true));
    printf("[Loopadrome][Main] Systems %d\r\n", ctx->systems->size);

    eng_start(ctx);
    eng_run(ctx);

}
