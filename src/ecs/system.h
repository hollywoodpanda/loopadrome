#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "./entity.h"

/**
 * Função de execução de um sistema ECS. Ela é chamada a cada frame e recebe como parâmetro
 * obrigatório o delta_time, que é o tempo que passou desde o último frame. Além disso, ela
 * pode ou não receber outros parâmetros variáveis. Com isso cada sistema pode possuir
 * uma função executora que atenda suas necessidades.
 * 
 * @param delta_time O tempo que passou desde o último frame. Parâmetro obrigatório
 * @param ... Possíveis parâmetros variáveis, não obrigatórios
*/
typedef void (*ecs_system_function)(float delta_time, ...);

/**
 * Um sistema na estrutura ECS. Ele é composto de uma função executora, que é chamada a cada
 * frame.
*/
typedef struct ecs_system {
    ecs_system_function execute;
} ecs_system;

/**
 * Cria um novo sistema ECS com a função executora informada.
 * 
 * @param execute A função executora do sistema
 * @return Um ponteiro para o sistema criado
*/
ecs_system *ecs_create_system (ecs_system_function execute);

/**
 * Libera a memória alocada para o sistema informado.
 * 
 * @param system O sistema a ser liberado
*/
void ecs_free_system (ecs_system *system);

#endif