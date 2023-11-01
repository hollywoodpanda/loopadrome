#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dm_window_system.h"
#include "dm_window_component.h"

avl_node *dm_components_global = NULL;

int dm_window_component_compare (char *value_a, ecs_component *value_b) {
    return strcmp(value_a, value_b->name);
}

void dm_window_system_start (void) {

    printf("[LOOPADROME][DM_WINDOW_SYSTEM] Starting the system\r\n");

}

void dm_window_system_execute (float delta_time) {

    printf("[LOOPADROME][DM_WINDOW_SYSTEM] Executing the system\r\n");

    if (!dm_components_global) {
        printf("[LOOPADROME][DM_WINDOW_SYSTEM] Components are NULL\r\n");
        return;
    }

    printf("[LOOPADROME][DM_WINDOW_SYSTEM] Finding the window component\r\n");
    avl_node *window_component_node = find(
        DM_WINDOW_COMPONENT_NAME,
        dm_components_global,
        dm_window_component_compare
    );

    ecs_component *window_component = (ecs_component*) window_component_node->data;

    printf("[LOOPADROME][DM_WINDOW_SYSTEM] Getting the window data\r\n");
    gl_window *window = (gl_window*) window_component->data;

    if (window == NULL) {
        printf("[LOOPADROME][DM_WINDOW_SYSTEM] Window is NULL\r\n");
        return;
    }

    printf("[LOOPADROME][DM_WINDOW_SYSTEM] Calling the window's game loop\r\n");
    window->game_loop(delta_time);

}

ecs_system *dm_create_window_system(
    avl_node *dm_components
) {

    dm_components_global = dm_components;

    ecs_system *dm_window_system = ecs_create_system(
        &dm_window_system_start,
        &dm_window_system_execute
    );

    return dm_window_system;

}

void dm_destroy_window_system (ecs_system *system) {
    
        if (system == NULL) {
            printf("[LOOPADROME][DM_WINDOW_SYSTEM] System is NULL\r\n");
            return;
        }

        if (dm_components_global) {

            ecs_component *window_component = find(
                DM_WINDOW_COMPONENT_NAME,
                dm_components_global, 
                dm_window_component_compare
            );

            dm_destroy_window_component(window_component);

        }

        dm_components_global = NULL;

        ecs_free_system(system);

}
