#include <stdlib.h>

#include "entity.h"

Entity *create_entity (int id) {
    Entity *entity = malloc(sizeof(Entity));
    entity->id = id;
    return entity;
}

void free_entity (Entity *entity) {
    free(entity);
}