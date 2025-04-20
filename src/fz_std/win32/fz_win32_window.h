#ifndef FZ_WIN32_PLATFORM_H
#define FZ_WIN32_PLATFORM_H

///////////////////////
//~ Application space

global b32 IsApplicationRunning = true;

extern void application_init(); // Implement in application layer
extern void application_tick(); // Implement in application layer

///////////////////////
//~ Timer
typedef struct PerformanceTimer {
  LARGE_INTEGER start;
  LARGE_INTEGER end;
  f32 elapsed_seconds;
} PerformanceTimer;

global LARGE_INTEGER    _PerformanceFrequency;
global PerformanceTimer _Timer_DeltaTime   = {0}; 
global PerformanceTimer _Timer_FrameTime   = {0};
global PerformanceTimer _Timer_ElapsedTime = {0};

internal f32 _get_elapsed_time();

#define DeltaTime   _Timer_DeltaTime.elapsed_seconds
#define FrameTime   _Timer_FrameTime.elapsed_seconds
#define ElapsedTime _get_elapsed_time()

void win32_timer_init();
void win32_timer_start(PerformanceTimer* timer);
void win32_timer_end(PerformanceTimer* timer);

///////////////////////
//~ Window

#if FZ_ENABLE_WINDOW

# if !FZ_WINDOW_WIDTH || !FZ_WINDOW_HEIGHT
#  define FZ_WINDOW_WIDTH  1280
#  define FZ_WINDOW_HEIGHT 720
# endif

global HDC   _DeviceContextHandle    = NULL;
global HGLRC _RenderingContextHandle = NULL;
global HWND  _WindowHandle           = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

internal HWND win32_window_create(HINSTANCE hInstance, s32 width, s32 height);
internal void win32_window_resize_callback(s32 width, s32 height);

# if FZ_ENABLE_WINDOW && !FZ_ENABLE_OPENGL
internal void win32_put_pixel(s32 x, s32 y, COLORREF color);
# endif // FZ_ENABLE_WINDOW && !FZ_ENABLE_OPENGL

#endif // FZ_ENABLE_WINDOW

///////////////////////
//~ Cursor

#if FZ_ENABLE_WINDOW

typedef enum Cursor_Type {
  CURSOR_ARROW,
  CURSOR_HAND,
  CURSOR_CROSSHAIR,
  CURSOR_IBEAM,
  CURSOR_WAIT,
  CURSOR_SIZE_ALL,

  CURSOR_COUNT
} CursorType;

global b32 IgnoreNextMouseMove = false;
global b32 IsCursorLocked      = false;
internal void win32_set_cursor(CursorType cursor);
internal void win32_set_cursor_position(s32 x, s32 y);
internal void win32_lock_cursor(b32 lock);
internal void win32_hide_cursor(b32 hide);

#endif // FZ_ENABLE_WINDOW

///////////////////////
//~ Window Components

global b32 _IsOpenGLContextAttached = false;
global b32 _IsTerminalAttached      = false;

# if FZ_ENABLE_OPENGL
internal b32  attach_opengl_context();
# endif

# if FZ_ENABLE_CONSOLE
internal void attach_console_output();
# endif

#endif // FZ_WIN32_PLATFORM_H