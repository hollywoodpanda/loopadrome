#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

typedef struct Component {
    char *name;
    void *data;
} Component;

Component *create_component (char *name, void *data);

void free_component (Component *component);

#endif