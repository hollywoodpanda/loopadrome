#include <stdio.h>
#include <stdlib.h>

#include "opengl/window.h"
#include "opengl/error.h"

#include "ecs/system.h"
#include "ecs/entity.h"
#include "ecs/component.h"

#include "game/avl_tree.h"

void print_system_fn (float delta_time)
{
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
}

void print_delta_and_message (float delta_time, char *message)
{
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
    printf("[Loopadrome][System] Message is %s\r\n", message);
}

void window_test ()
{
    gl_start_default_error_callback();
    gl_open_window(
        "Loopadrome",
        1024,
        768
    );
}

void avl_tree_test ()
{

    Node *root = create_node(1);

    Node *first_child = insert(2, root);

    Node *second_child = insert(3, root);

    Node *third_child = insert(4, first_child);

    printf("[Loopadrome][AVL_TREE] root (%d) %d\r\n", root->key, get_height(root));

    destroy_tree(root);

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
    System *system = ecs_create_system(&print_delta_and_message);

    system->execute(4.20f, "Hello ECS World!");

    ecs_free_system(system);

    System *simpler_system = ecs_create_system(&print_system_fn);

    simpler_system->execute(5.2f);

    ecs_free_system(simpler_system);
}

int main(int argc, char const *argv[])
{

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    system_test();
    entity_test();
    component_test();

    avl_tree_test();

    window_test();

}
