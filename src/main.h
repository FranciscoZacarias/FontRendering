#ifndef MAIN_H
#define MAIN_H

//~ fz_std
#define FZ_WINDOW_NAME   "Text Rendering"

#define FZ_ENABLE_ASSERT  1
#define FZ_ENABLE_WINDOW  1
#define FZ_ENABLE_OPENGL  1

#include "fz_include.h"

//~ *.h
#include "renderer.h"

//~ *.c
#include "renderer.c"

void application_init(); // Run once at start of program
void application_tick(); // Run every tick

internal void input_update();

#endif // MAIN_H