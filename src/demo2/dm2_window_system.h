#ifndef DEMO2_WINDOW_SYSTEM_H
#define DEMO2_WINDOW_SYSTEM_H

#include "../ecs/system.h"

void dm2_window_system_start (void);
void dm2_window_system_execute (float delta_time);

ecs_system *dm2_create_window_system (void);

#endif