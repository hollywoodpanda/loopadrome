#ifndef GAME_WINDOW_SYSTEM_H
#define GAME_WINDOW_SYSTEM_H

#include <stdbool.h>
#include "../../game/engine.h"

void _win_start_system (eng_context* ctx);

void _win_update_system (eng_context* ctx, float delta_time);

void win_create_system (
    bool active,
    eng_context* ctx
);

#endif