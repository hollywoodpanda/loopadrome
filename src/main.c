#include "game/engine.h"
#include "game/window/win_system.h"
#include "game/window/win_entity.h"

int main () {

    eng_context* ctx = eng_create_context();

    win_create_entity("Loopadrome 100", 800, 600, false, true, ctx);
    win_create_system(true, ctx);

    eng_start(ctx);
    eng_run(ctx);
    eng_destroy_context(ctx);

}