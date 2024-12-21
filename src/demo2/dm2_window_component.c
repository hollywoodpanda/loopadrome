#include <stdbool.h>
#include <stdio.h>

#include "dm2_window_component.h"

#define DM2_WINDOW_COMPONENT_NAME "dm2_window_component"

GLFWwindow *glfw_window = NULL;

ecs_component* dm2_create_window_component (
    char* window_title,
    int window_width,
    int window_height,
    int is_fullscreen
) {

    gl_window* window = gl_create_window(
        window_title,
        window_width,
        window_height,
        is_fullscreen,
        false,
        NULL
    );

    glfw_window = window->instance;

    return ecs_create_component(
        DM2_WINDOW_COMPONENT_NAME,
        window
    );

}

void dm2_destroy_window_component (ecs_component* component) {

    if (component == NULL) {
        printf("[LOOPADROME][DM2_WINDOW_COMPONENT] Component is NULL\r\n");
        return;
    }

    ecs_free_component(component);

}