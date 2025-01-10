#include "win_system.h"
#include "win_entity.h"
#include <GLFW/glfw3.h>
#include "../../opengl/error.h"
#include "../measurement/size.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool _window_inactive_shutdown_system (eng_context* ctx) {
    ecs_system* win_system = eng_find_system(ctx, WINDOW_SYSTEM);
    return win_system == NULL || !win_system->active;
}

void _win_start_system (eng_context* ctx) {

    gl_start_default_error_callback();

    if (!glfwInit()) {
        gl_default_error_callback(-100, "Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // FIXME: Resizing freezes the game loop 👀
    glfwWindowHint(GLFW_RESIZABLE, TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ecs_entity* window_entity = eng_find_entity(ctx, WINDOW_ENTITY);

    if (window_entity == NULL) {
        return;
    }

    ecs_component* win_size_comp = eng_find_component(window_entity, WINDOW_SIZE_COMPONENT);

    measure_size* size = (measure_size*) win_size_comp->data;

    ecs_component* win_title_comp = eng_find_component(window_entity, WINDOW_TITLE_COMPONENT);

    char* title = (char*) win_title_comp->data;

    ecs_component* win_fullscreen_comp = eng_find_component(window_entity, WINDOW_FULLSCREEN_COMPONENT);

    bool is_fullscreen = *((bool*) win_fullscreen_comp->data);

    ecs_component* win_instance_comp = eng_find_component(window_entity, WINDOW_INSTANCE_COMPONENT);

    GLFWwindow* window = (GLFWwindow*) win_instance_comp->data;

    if (window == NULL) {
        window = glfwCreateWindow(
            size->width, 
            size->height, 
            title,
            is_fullscreen ? glfwGetPrimaryMonitor() : NULL,
            NULL
        );

        if (window == NULL) {
            gl_default_error_callback(-101, "Failed to open GLFW window");
            glfwTerminate();
            return;
        }

        win_instance_comp->data = window;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void _win_update_system (eng_context* ctx, float delta_time) {

    ecs_entity* window_entity = eng_find_entity(ctx, WINDOW_ENTITY);

    if (window_entity == NULL) {
        return;
    }

    ecs_component* win_size_comp = eng_find_component(window_entity, WINDOW_SIZE_COMPONENT);

    measure_size* size = (measure_size*) win_size_comp->data;

    ecs_component* win_title_comp = eng_find_component(window_entity, WINDOW_TITLE_COMPONENT);

    char* title = (char*) win_title_comp->data;

    int title_index = (int) strtol(title + 11, NULL, 10);
    title_index++;
    if (title_index > 999) {
        title_index = 0;
    }
    char title_prefix[11];
    strncpy(title_prefix, title, 11);
    title_prefix[11] = '\0';
    char* new_title[15];
    sprintf(new_title, "%s%d", title_prefix, title_index);
    win_title_comp->data = new_title;

    ecs_component* win_fullscreen_comp = eng_find_component(window_entity, WINDOW_FULLSCREEN_COMPONENT);

    int is_fullscreen = *((int*) win_fullscreen_comp->data);

    ecs_component* win_instance_comp = eng_find_component(window_entity, WINDOW_INSTANCE_COMPONENT);

    GLFWwindow* window = (GLFWwindow*) win_instance_comp->data;

    if (window != NULL && !glfwWindowShouldClose(window)) {
        
        glfwSetWindowTitle(window, title);
        
        int current_width, current_height;
        glfwGetWindowSize(window, &current_width, &current_height);
        if (current_width != size->width || current_height != size->height) {
            printf("[DEBUG] Size changed to (w: %d, h: %d)! Resizing based on the (w: %d, h: %d) size\n",current_width, current_height, size->width, size->height);
            glfwSetWindowSize(window, size->width, size->height);
        }

        int current_fullscreen = glfwGetWindowMonitor(window) != NULL;
        if (current_fullscreen != is_fullscreen) {
            
            GLFWmonitor* monitor = NULL;
            
            if (is_fullscreen) {
                monitor = glfwGetPrimaryMonitor();
            }

            glfwSetWindowMonitor(window, monitor, 0, 0, size->width, size->height, GLFW_DONT_CARE);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);

    } else {
        glfwTerminate();
        ecs_system* win_system = eng_find_system(ctx, WINDOW_SYSTEM);
        if (win_system != NULL) { 
            win_system->active = false;
        }
    }

}

void win_create_system (
    bool active,
    eng_context* ctx
) {
    ecs_system* window_system = ecs_create_system("window_system", &_win_start_system, &_win_update_system, active);
    eng_add_shutdown_function(ctx, &_window_inactive_shutdown_system);
    eng_add_system(ctx, window_system);
}