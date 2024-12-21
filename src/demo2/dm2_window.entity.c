#include "dm2_window_entity.h"
#include "dm2_window_component.h"

ecs_entity* dm2_create_entity (void) {
    ecs_entity* entity = ecs_create_entity(0);
    ecs_component* window_component = dm2_create_window_component(
        "Loopadrome",
        800,
        600,
        0
    );
    ecs_add_component(entity, window_component);
    return entity;
}