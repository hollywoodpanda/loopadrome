#include <stdbool.h>
#include <stdio.h>
#include "dm2_window_system.h"

void dm2_window_system_start (void) {
    printf("[LOOPADROME][DM2_WINDOW_SYSTEM] Starting window system\r\n");
}

void dm2_window_system_execute (float delta_time) {
    printf("[LOOPADROME][DM2_WINDOW_SYSTEM] Executing window system %.2f\r\n", delta_time);
}

ecs_system *dm2_create_window_system (void) {
    return ecs_create_system(
        "dm2_window_system",
        &dm2_window_system_start,
        &dm2_window_system_execute,
        true
    );
}