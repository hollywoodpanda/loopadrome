#include <stdio.h>
#include <stdlib.h>

#include "../opengl/window.h"
#include "../opengl/error.h"

#include "../ecs/system.h"
#include "../ecs/entity.h"
#include "../ecs/component.h"

#include "../constants.h"

#include "../game/avl_tree.h"

void print_init_system_fn  (void) {
    printf("[Loopadrome][System] Initializing system\r\n");
} 

void print_system_fn (float delta_time)
{
    printf("[Loopadrome][System] Delta time is %f\r\n", delta_time);
}

void print_system_cool_fn (float delta_time) {
    printf("[Loopadrome][System] Hey, bro! Delta time is %f\r\n", delta_time);
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

    printf("[Loopadrome][AVL_TREE_TEST] root is %p with height %d\r\n", root->data, get_height(root));

    pre_order(root, NODE_TYPE_ROOT);

    printf("\r\n");

    int key_to_find = 3;

    avl_node *node_found = find(key_to_find, root, avl_tree_compare);

    if (node_found != NULL) {
        printf("[Loopadrome][AVL_TREE_TEST] Node '%d' found! It is %p.\r\n", key_to_find, node_found->data);
    } else {
        printf("[Loopadrome][AVL_TREE_TEST] Node '%d' not found\r\n", key_to_find);
    }

    root = delete(3, root, avl_tree_compare);
    root = delete(4, root, avl_tree_compare);

    printf("[Loopadrome][AVL_TREE_TEST] Without some nodes, root is %p with height %d\r\n", root->data, get_height(root));

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

    ecs_system *system = ecs_create_system(
        &print_init_system_fn,
        &print_system_cool_fn
    );

    if (system->start != NULL) {
        system->start();
    }

    system->execute(4.20f);
    system->execute(4.21f);

    ecs_free_system(system);

    ecs_system *simpler_system = ecs_create_system(
        &print_init_system_fn,
        &print_system_fn
    );

    if (simpler_system->start != NULL) {
        simpler_system->start();
    }

    simpler_system->execute(5.2f);

    ecs_free_system(simpler_system);

}
