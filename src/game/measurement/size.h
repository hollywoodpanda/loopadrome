#ifndef GAME_MEASUREMENT_SIZE_H
#define GAME_MEASUREMENT_SIZE_H

#include <stdbool.h>

typedef struct measure_size
{
    int width;
    int height;
    bool is_resizable;
} measure_size;

#endif