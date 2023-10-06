#include <stdio.h>
#include <stdlib.h>

#include "opengl/window.h"
#include "opengl/error.h"

#include "ecs/system.h"
#include "ecs/entity.h"
#include "ecs/component.h"

#include "./constants.h"

#include "game/avl_tree.h"

void print_system_fn (float delta_time)
{
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
}

void print_delta_and_message (float delta_time, char *message) {
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
    printf("[Loopadrome][System] Message is %s\r\n", message);
}

void window_test () {
    gl_start_default_error_callback();
    gl_open_window(
        "Loopadrome",
        1024,
        768
    );
}

int avl_tree_compare (int value_a, int value_b) {
    if (value_a < value_b) {
        return -1;
    } else if (value_a > value_b) {
        return 1;
    } else {
        return 0;
    }
}

void avl_tree_test () {

    avl_node *root = create_node(5);

    root = insert(2, root, avl_tree_compare);

    root = insert(6, root, avl_tree_compare);

    root = insert(4, root, avl_tree_compare);

    root = insert(1, root, avl_tree_compare);

    root = insert(3, root, avl_tree_compare);

    

    printf("[Loopadrome][AVL_TREE_TEST] root is %p with height %d\r\n", root->key, get_height(root));

    pre_order(root, NODE_TYPE_ROOT);

    printf("\r\n");

    root = delete(6, root, avl_tree_compare);

    printf("[Loopadrome][AVL_TREE_TEST] Without 6, root is %p with height %d\r\n", root->key, get_height(root));

    pre_order(root, NODE_TYPE_ROOT);

    printf("\r\n");

    destroy_tree(root);

}

void component_test () {
    ecs_component *component = ecs_create_component("Cool Component", "Value");

    printf("[Loopadrome][Component] Component name is %s\r\n", component->name);
    printf("[Loopadrome][Component] Component data is %s\r\n", (char*) component->data);

    ecs_free_component(component);
}

void entity_test () {
    ecs_entity *entity = ecs_create_entity(1);

    printf("[Loopadrome][Entity] Entity id is %d\r\n", entity->id);

    ecs_free_entity(entity);
}

void system_test () {
    ecs_system *system = ecs_create_system(&print_delta_and_message);

    system->execute(4.20f, "Hello ECS World!");

    ecs_free_system(system);

    ecs_system *simpler_system = ecs_create_system(&print_system_fn);

    simpler_system->execute(5.2f);

    ecs_free_system(simpler_system);
}

int main(int argc, char const *argv[]) {

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    system_test();
    entity_test();
    component_test();

    avl_tree_test();

    window_test();

}
