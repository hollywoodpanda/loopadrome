#ifndef OPENGL_ERROR_H
#define OPENGL_ERROR_H

#include <GLFW/glfw3.h>

void error_callback (GLFWerrorfun error_callback);

void default_error_callback (int error, const char* description);

void start_default_error_callback ();

#endif