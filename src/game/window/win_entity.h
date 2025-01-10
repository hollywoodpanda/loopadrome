#ifndef GAME_WIN_ENTITY_H
#define GAME_WIN_ENTITY_H

#include <stdbool.h>

#include "../../constants.h"
#include "../../ecs/entity.h"
#include "../../ecs/component.h"
#include "../engine.h"

void win_create_entity (
    char *title,
    int width,
    int height,
    bool is_fullscreen,
    bool is_resizable,
    eng_context* ctx
);

#endif