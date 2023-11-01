#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#ifndef _glfw3_h_
    #include <GLFW/glfw3.h>
#endif

#include "../constants.h"

typedef void (*gl_window_loop_function)(float delta_time);

typedef struct gl_window {
    char *title;
    GLFWwindow *instance;
    int width;
    int height;
    int is_fullscreen;
    int is_resizable;
    gl_window_loop_function game_loop;
} gl_window;

/** @deprecated */
int gl_open_window ();

gl_window *gl_create_window (
    char *title,
    int width,
    int height,
    int is_fullscreen,
    int is_resizable,
    gl_window_loop_function game_loop
);

#endif