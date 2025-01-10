#include "win_entity.h"
#include "../measurement/size.h"
#include "../../constants.h"
#include <GLFW/glfw3.h>

void win_create_entity (
    char *title,
    int width,
    int height,
    bool is_fullscreen,
    bool is_resizable,
    eng_context* ctx
) {
    measure_size* size = malloc(sizeof(measure_size));
    size->width = width;
    size->height = height;
    size->is_resizable = is_resizable;

    ecs_component* window_size_component = ecs_create_component(WINDOW_SIZE_COMPONENT, size);
    ecs_component* window_title_component = ecs_create_component(WINDOW_TITLE_COMPONENT, title);
    ecs_component* window_fullscreen_component = ecs_create_component(WINDOW_FULLSCREEN_COMPONENT, &is_fullscreen);

    GLFWwindow* window = NULL;

    ecs_component* window_instance_component = ecs_create_component(WINDOW_INSTANCE_COMPONENT, window);

    ecs_entity* window_entity = ecs_create_entity(WINDOW_ENTITY);
    ecs_add_component(window_entity, window_size_component);
    ecs_add_component(window_entity, window_title_component);
    ecs_add_component(window_entity, window_fullscreen_component);
    ecs_add_component(window_entity, window_instance_component);

    eng_add_entity(ctx, window_entity);
}