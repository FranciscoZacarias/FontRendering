#ifndef FZ_INCLUDES_H
#define FZ_INCLUDES_H

//~ CLib
#include <stdlib.h>
#include <string.h>
#include <math.h> // TODO(fz): Replace/Implement these functions -> sinf(), cosf(), tan(), atan2f(), sqrtf(), fmaxf(), fabsf()

//~ Extern
#include "external/stb_sprintf.h"

//~ Single headers
#include "fz_core.h"
#include "fz_io.h"

//~ Headers
#include "fz_math.h"
#include "fz_memory.h"
#include "fz_string.h"
#include "fz_thread_context.h"
#if FZ_ENABLE_OPENGL
# include "glad/glad.h"
# include "glad/glad.c"
# include "extra/fz_opengl_helper.h"
#endif 
#if FZ_ENABLE_WINDOW
#include "fz_input.h"
#endif
#include "fz_win32.h"
#include "fz_win32_window.h"

//~ Extern
#define STB_SPRINTFZ_IMPLEMENTATION
#include "external/stb_sprintf.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

//~ Source
#include "fz_math.c"
#include "fz_memory.c"
#include "fz_string.c"
#include "fz_thread_context.c"

#if FZ_ENABLE_OPENGL
# include "extra/fz_opengl_helper.c"
#endif
#if FZ_ENABLE_WINDOW
#include "fz_input.c"
#endif
#include "fz_win32.c"
#include "fz_win32_window.c"

#endif // FZ_INCLUDES_H