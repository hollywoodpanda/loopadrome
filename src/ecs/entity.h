#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

/**
 * Uma entidade na estrutura ECS. Ela é composta de um id, que deve ser um inteiro único.
 * Cada entidade deve possuir um id diferente.
 * 
 * @param id O id da entidade
*/
typedef struct ecs_entity {
    int id;
} ecs_entity;

/**
 * Cria uma nova entidade ECS com o id informado.
 * 
 * @param id O id da entidade
 * @return Um ponteiro para a entidade criada
*/
ecs_entity *ecs_create_entity (int id);

/**
 * Libera a memória alocada para a entidade informada.
 * 
 * @param entity A entidade a ser liberada
*/
void ecs_free_entity (ecs_entity *entity);

#endif