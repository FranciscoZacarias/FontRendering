#ifndef RENDERER_H
#define RENDERER_H

#define VERTEX_SHADER_PATH "D:/work/opengl_font_rendering/src/shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER_PATH "D:/work/opengl_font_rendering/src/shaders/fragment_shader.glsl"

#define FONT_SPACEMONO "D:/work/opengl_font_rendering/fonts/SpaceMono-Regular.ttf"
#define FONT_INCONSOLATA "D:/work/opengl_font_rendering/fonts/Inconsolata.otf"

typedef struct Vertex {
Vec3f32 position;
Vec2f32 uv;
} Vertex;

typedef struct Glyph {
  Vec2f32 uv_min;
  Vec2f32 uv_max;
  Vec2f32 size;
  Vec2f32 offset;
  f32     advance;
} Glyph;

typedef struct Font {
  Glyph glyphs[95];
  u32   texture_id;
  f32   height;
  f32 line_height;   // Line height in screen space
} Font;

typedef struct Instanced_Data {
  Transformf32 transform;
  Vec4f32 color;
  u32     texture_id;
  Vec2f32 uv_min;
  Vec2f32 uv_max;
} Instanced_Data;

global GLuint Vbo_InstancedData;
global GLuint Vao_Quad, Vbo_Quad, Ebo_Quad;
global OGL_Shader OglProgram;

typedef struct Renderer_State {
  Arena* arena;
  Instanced_Data* instanced_data;
  u32             instanced_max;
  u32             instanced_count;
  GLuint*         textures;
  u32             texture_count;
  u32             texture_max;
  Font            font;
} Renderer_State;

Renderer_State Renderer;

internal void renderer_init();
internal void renderer_begin_frame();
internal void renderer_end_frame(Mat4f32 view, Mat4f32 projection);
internal u32  renderer_load_font(String8 path, f32 font_height);
internal f32  renderer_push_text(Vec2f32 screen_position, Vec4f32 color, f32 scale, String8 text); /* Renders text, returns vertical size of rendered text */

#endif // RENDERER_H