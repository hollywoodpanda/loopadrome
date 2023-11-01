#ifndef DEMO_WINDOW_SYSTEM_H
#define DEMO_WINDOW_SYSTEM_H

#include "../ecs/system.h"
#include "../game/avl_tree.h"

ecs_system *dm_create_window_system(
    avl_node *dm_components
);

void dm_destroy_window_system (ecs_system *system);

#endif