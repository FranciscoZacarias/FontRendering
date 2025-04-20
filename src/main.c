#include "main.h"

String8 AsciiChars;
String8 SolwayFirth;
Vec4f32 Colors[15];
f32 Scale = 1.0f;
f32 FontYOffset = 0;

void application_init() {
  renderer_init();
  
  SolwayFirth = Str8("While I was learning to live\nYou taught me how to die\nI guess I got what I wanted\nAnother needle in the back through purified sacrification\nIt wasn't somebody else\nYou fucking did it to me\nYou want a real smile?\nI haven't smiled in years.\n");

  Colors[0] = Color_Red;
  Colors[1] = Color_Green;
  Colors[2] = Color_Blue;
  Colors[3] = Color_Yellow;
  Colors[4] = Color_Cyan;
  Colors[5] = Color_Magenta;
  Colors[6] = Color_White;
  Colors[7] = Color_Black;
  Colors[8] = Color_Gray;

  AsciiChars = Str8("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}");
}

void application_tick() {
  input_update();
  renderer_begin_frame();

  Mat4f32 view = mat4f32_identity();
  Mat4f32 projection = mat4f32_ortographic(
      0.0, (f64)FZ_WINDOW_WIDTH,     // left to right
      (f64)FZ_WINDOW_HEIGHT, 0.0,    // bottom to top (flipped Y)
      -1.0, 1.0                      // near to far
  );

  u32 ColorIt = 0;

  f32 y = Renderer.font.line_height;
  f32 scale = 0.8;

  for (s32 i = 0; i < 8; i += 1) {
    y += renderer_push_text(vec2f32(0.0f, y), Colors[ColorIt++%8], scale, AsciiChars);
  }

  y += renderer_push_text(vec2f32(0.0f, y), Colors[ColorIt++%8], scale, SolwayFirth);
  y += renderer_push_text(vec2f32(0.0f, y), Colors[ColorIt++%8], scale, Str8("End of the story."));

  renderer_end_frame(view, projection);
}

internal void input_update() {
  if (input_is_key_pressed(KeyboardKey_ESCAPE)) {
    application_stop();
  }
}