#ifndef DEMO2_WINDOW_COMPONENT_H
#define DEMO2_WINDOW_COMPONENT_H

#include "../ecs/component.h"
#include "../opengl/gl_window.h"

ecs_component *dm2_create_window_component (
    char *window_title,
    int window_width,
    int window_height,
    int is_fullscreen
);

void dm2_destroy_window_component (ecs_component *component);

#endif