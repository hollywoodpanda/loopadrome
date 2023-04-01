#include <stdio.h>
#include <stdlib.h>

#include "core/entity.h"
#include "core/component.h"

typedef struct HealthComponent {
    int health;
} HealthComponent;

void printo (char *str)
{

    printf("%s\r\n", str);    

}

int main(int argc, char const *argv[])
{

    Entity *entity = create_entity(2);

    printo("[DEBUG] Criou a entity");

    struct HealthComponent *health_component = malloc(sizeof(struct HealthComponent));

    health_component->health = 10;

    printo("[DEBUG] Criou o health_component");

    Component *component = create_component("Health", health_component);

    entity->id = 1;
    health_component->health = 1;

    printo("[DEBUG] Criou o component");

    HealthComponent *extracted_health = (HealthComponent *) component->data;

    printf("[DEBUG] Entity %d with health %d (%s)\r\n", entity->id, extracted_health->health, component->name);

    printo("[DEBUG] Printou o entity e o health_component");

    free_component(component);
    free_entity(entity);

    return 0;
}
