#ifndef DM_WINDOW_COMPONENT_H
#define DM_WINDOW_COMPONENT_H

#define DM_WINDOW_COMPONENT_NAME "dm_window_component"

#include "../ecs/component.h"
#include "../opengl/window.h"

ecs_component *dm_create_window_component (
    char *window_title,
    int window_width,
    int window_height,
    int is_fullscreen
);

void dm_destroy_window_component (ecs_component *component);

#endif