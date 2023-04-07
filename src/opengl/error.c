#include <stdio.h>
#include <GLFW/glfw3.h>

void gl_error_callback (GLFWerrorfun error_callback)
{
    glfwSetErrorCallback(error_callback);
}

void gl_default_error_callback (int error, const char* description)
{
    fprintf(stderr, "[Loopadrome][OpenGL] Error[%d]: %s\r\n", error, description);
}

void gl_start_default_error_callback ()
{
    gl_error_callback(gl_default_error_callback);
}