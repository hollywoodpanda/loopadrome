#include <stdio.h>
#include <stdlib.h>

#ifndef _glfw3_h_
    #include <GLFW/glfw3.h>
#endif

#include "window.h"
#include "error.h"
#include "../constants.h"

void gl_start_hints () {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
        
    glfwWindowHint(GLFW_RESIZABLE, TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void log(char *message) {
    printf("[LOOPADROME][WINDOW] %s\r\n", message);

}

gl_window *gl_create_window (
    char *title,
    int width,
    int height,
    int is_fullscreen,
    int is_resizable,
    gl_window_loop_function game_loop
) {

    log("Creating window");

    log("Setting error callback");
    // 1. The error callback function. All GLFW errors 
    // will be reported through the error callback function.
    gl_start_default_error_callback();

    log("Initializing GLFW");
    // 2. Initialize GLFW
    if (!glfwInit()) {
        gl_default_error_callback(-100, "Failed to initialize GLFW");
        // If not initialized, returning NULL
        // so that the caller can handle the error
        return NULL;
    }

    log("Setting window hints");
    // 3. Setting the window hints
    gl_start_hints();

    log("Creating GLFWwindow");
    // 4. Creating the window
    GLFWwindow *window = glfwCreateWindow(
        width, 
        height, 
        title,
        // NULL means windowed mode. We're also only considering the primary monitor here
        is_fullscreen ? glfwGetPrimaryMonitor() : NULL,
        NULL
    );

    log("Checking if the window was created");
    // 5. Checking if the window was created
    if (window == NULL) {
        gl_default_error_callback(-101, "Failed to open GLFW window");
        glfwTerminate();
        // If thew window is not created, returning NULL
        // so that the caller can handle the error
        return NULL;
    }

    log("Making the window's context current");
    // 6. Making the window's context current
    glfwMakeContextCurrent(window);

    log("Enabling sticky keys");
    // 7. Enabling sticky keys
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    log("Creating the window object");
    // 8. Creating the window object
    gl_window *gl_window_instance = (gl_window *) malloc(sizeof(gl_window));

    log("Setting the window object properties");
    gl_window_instance->title = title;
    gl_window_instance->instance = window;
    gl_window_instance->width = width;
    gl_window_instance->height = height;
    gl_window_instance->is_fullscreen = is_fullscreen;
    gl_window_instance->is_resizable = is_resizable;
    gl_window_instance->game_loop = game_loop;

    log("Returning the window object");
    return gl_window_instance;

}

int gl_open_window (
    char* window_title,
    int window_width,
    int window_height
) {

    // TODO: configure the error callback: https://www.glfw.org/docs/latest/quick_guide.html
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return OPENGL_INIT_ERROR;
    }

    gl_start_hints();

    GLFWwindow *window = glfwCreateWindow(
        window_width, 
        window_height, 
        window_title, 
        NULL, 
        NULL
    );

    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window");
        glfwTerminate();
        return OPENGL_WINDOW_ERROR;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return OPENGL_SUCCESS;

}