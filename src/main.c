#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "test/raw_testing.h"
#include "ecs/system.h"
#include "ecs/component.h"
#include "game/avl_tree.h"
#include "demo/dm_window_component.h"
#include "demo/dm_window_system.h"
#include "constants.h"

// TODO: We should adopt other strategy in windows systems: https://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c
#include <sys/time.h>

void test_md_window_system () {

    // 1. Create the component
    ecs_component *window_component = dm_create_window_component(
        "Loopadrome",
        1024,
        768,
        FALSE
    );

    if (window_component == NULL) {
        printf("[Loopadrome][Main] Window component is NULL\r\n");
        return;
    }

    // 2. The components tree
    avl_node *component_root_node = create_node(window_component);

    if (component_root_node == NULL) {
        printf("[Loopadrome][Main] Component root node is NULL\r\n");
        return;
    }

    // 3. Create the system
    ecs_system *window_system = dm_create_window_system(component_root_node);

    if (window_system == NULL) {
        printf("[Loopadrome][Main] Window system is NULL\r\n");
        return;
    }

    float delta_time = 0.0f;

    // 4. Execute the system
    do {

        struct timeval start, end;
        
        gettimeofday(&start, NULL);

        window_system->execute(delta_time);

        gettimeofday(&end, NULL);

        delta_time = (end.tv_sec - start.tv_sec) * 1000.0f;

    } while (glfwWindowShouldClose(window_component->data) == 0);

    glfwTerminate();

}
 
int main(int argc, char const *argv[]) {

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    // system_test();
    // entity_test();
    // component_test();

    // avl_tree_test();

    // window_test();

    test_md_window_system();

}
