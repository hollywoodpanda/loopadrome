#ifndef OPENGL_ERROR_H
#define OPENGL_ERROR_H

#include <GLFW/glfw3.h>

void gl_error_callback (GLFWerrorfun error_callback);

void gl_default_error_callback (int error, const char* description);

void gl_start_default_error_callback ();

#endif