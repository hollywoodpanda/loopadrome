#include <stdio.h>
#include <stdlib.h>

#include "core/entity.h"
#include "core/component.h"

#include "opengl/window.h"
#include "opengl/error.h"

void window_test ()
{
    start_default_error_callback();
    open_window(
        "Loopadrome",
        1024,
        768
    );    
}

int main(int argc, char const *argv[])
{

    printf("[Loopadrome][Main] argc %d\r\n", argc);
    printf("[Loopadrome][Main] argv %s\r\n", argv[0]);

    window_test();
}
