#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dm_window_system.h"
#include "dm_window_component.h"

avl_node *dm_components_global = NULL;

int dm_window_component_compare (char *value_a, char *value_b) {
    return strcmp(value_a, value_b);
}

void dm_window_system_execute (float delta_time) {

    if (!dm_components_global) {
        printf("[LOOPADROME][DM_WINDOW_SYSTEM] Components are NULL\r\n");
        return;
    }

    ecs_component *window_component = find(
        dm_components_global, 
        DM_WINDOW_COMPONENT_NAME,
        dm_window_component_compare
    );

    if (!window_component) {
        printf("[LOOPADROME][DM_WINDOW_SYSTEM] Window component is NULL\r\n");
        return;
    }

    gl_window *window = (gl_window*) window_component->data;
    window->game_loop(delta_time);

}

ecs_system *dm_create_window_system(
    avl_node *dm_components
) {

    dm_components_global = dm_components;

    ecs_system *dm_window_system = ecs_create_system(
        NULL,
        &dm_window_system_execute
    );

}

void dm_destroy_window_system (ecs_system *system) {
    
        if (system == NULL) {
            printf("[LOOPADROME][DM_WINDOW_SYSTEM] System is NULL\r\n");
            return;
        }

        if (dm_components_global) {

            ecs_component *window_component = find(
                dm_components_global, 
                DM_WINDOW_COMPONENT_NAME,
                dm_window_component_compare
            );

            dm_destroy_window_component(window_component);

        }

        dm_components_global = NULL;

        ecs_free_system(system);

}
