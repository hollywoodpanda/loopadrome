#ifndef CORE_ENTITY_H
#define CORE_ENTITY_H

typedef struct Entity {
    int id;
} Entity;

Entity *create_entity (int id);

void free_entity (Entity *entity);

#endif