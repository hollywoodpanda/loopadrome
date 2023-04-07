#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "../constants.h"


void start_hints ()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
        
    glfwWindowHint(GLFW_RESIZABLE, TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int open_window (
    char* window_title,
    int window_width,
    int window_height
) 
{
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return OPENGL_INIT_ERROR;
    }

    start_hints();

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