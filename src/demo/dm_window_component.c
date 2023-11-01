#include <stdio.h>
#include <stdlib.h>

#include "dm_window_component.h"

#ifndef CONSTANTS_H
    #include "../constants.h"
#endif

GLFWwindow *glfw_window = NULL;


void dm_window_component_loop_function (float delta_time) {

    if (glfw_window == NULL) {
        printf("[LOOPADROME][DM_WINDOW_COMPONENT] Window is NULL\r\n");
        return;
    }

    glfwSwapBuffers(glfw_window);
    glfwPollEvents();

}

void destroy_gl_window_component (gl_window *window) {

    if (window == NULL) {
        printf("[LOOPADROME][DM_WINDOW_COMPONENT] Window is NULL\r\n");
        return;
    }

    glfwDestroyWindow(window->instance);
    glfw_window = NULL;
    glfwTerminate();

    free(window);

}

gl_window *dm_create_gl_window_component_data(
    char *window_title,
    int window_width,
    int window_height,
    int is_fullscreen
) {

    gl_window *window = gl_create_window(
        window_title,
        window_width,
        window_height,
        is_fullscreen,
        FALSE,
        NULL
    );

    glfw_window = window->instance;

    window->game_loop = &dm_window_component_loop_function;

    return window;

}

ecs_component *dm_create_window_component(
    char *window_title,
    int window_width,
    int window_height,
    int is_fullscreen
) {

    return ecs_create_component(
        DM_WINDOW_COMPONENT_NAME,
        dm_create_gl_window_component_data(
            window_title,
            window_width,
            window_height,
            is_fullscreen
        )
    );

}

void dm_destroy_window_component (ecs_component *component) {

    if (component == NULL) {
        printf("[LOOPADROME][DM_WINDOW_COMPONENT] Component is NULL\r\n");
        return;
    }

    destroy_gl_window_component((gl_window*) component->data);
    ecs_free_component(component);

}