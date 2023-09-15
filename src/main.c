#include <stdio.h>
#include <stdlib.h>

#include "opengl/window.h"
#include "opengl/error.h"

#include "ecs/system.h"
#include "ecs/entity.h"
#include "ecs/component.h"

void window_test ()
{
    gl_start_default_error_callback();
    gl_open_window(
        "Loopadrome",
        1024,
        768
    );
}

void print_system_fn (float delta_time)
{
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
}

void component_test ()
{
    Component *component = ecs_create_component("Cool Component", "Value");

    printf("[Loopadrome][Component] Component name is %s\r\n", component->name);
    printf("[Loopadrome][Component] Component data is %s\r\n", (char*) component->data);

    ecs_free_component(component);
}

void entity_test ()
{
    Entity *entity = ecs_create_entity(1);

    printf("[Loopadrome][Entity] Entity id is %d\r\n", entity->id);

    ecs_free_entity(entity);
}

void system_test ()
{
    System *system = ecs_create_system(&print_system_fn);

    system->execute(4.20f);

    ecs_free_system(system);
}

int main(int argc, char const *argv[])
{

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    //window_test();
    system_test();
    entity_test();
    component_test();

}
