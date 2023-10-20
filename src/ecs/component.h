#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

/**
 * Um componente na estrutura ECS. Ele é composto de um nome, que pode ser qualquer string
 * desde que exclusiva - cada componente precisa de um nome único. Também é composto de um
 * ponteiro para os dados do componente, que podem ser qualquer tipo de dado.
 * 
 * @param name O nome do componente
 * @param data Os dados do componente
*/
typedef struct ecs_component {
    char *name;
    void *data;
} ecs_component;

/**
 * Cria um novo componente ECS com o nome e dados informados.
 * 
 * @param name O nome do componente
 * @param data Os dados do componente
 * 
 * @return Um ponteiro para o componente criado
*/
ecs_component *ecs_create_component (char *name, void *data);

/**
 * Libera a memória alocada para o componente informado.
 * 
 * @param component O componente a ser liberado
*/
void ecs_free_component (ecs_component *component);

#endif