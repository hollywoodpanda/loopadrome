#include <stdio.h>
#include <GLFW/glfw3.h>

void error_callback (GLFWerrorfun error_callback)
{
    glfwSetErrorCallback(error_callback);
}

void default_error_callback (int error, const char* description)
{
    fprintf(stderr, "[Loopadrome][OpenGL] Error[%d]: %s\r\n", error, description);
}

void start_default_error_callback ()
{
    error_callback(default_error_callback);
}