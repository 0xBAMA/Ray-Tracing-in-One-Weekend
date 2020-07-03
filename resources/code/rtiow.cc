#include "rtiow.h"
#include "debug.h"
// This contains the very high level expression of what's going on

rtiow::rtiow()
{
    pquit = false;

    create_window();
    gl_debug_enable();
    gl_setup();

    while(!pquit)
    {
        do_a_sample();
    }
}

rtiow::~rtiow()
{
    quit();
}
