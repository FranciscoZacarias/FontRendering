internal void renderer_init() {
  AssertNoReentry();

  MemoryZeroStruct(&Renderer);
  Renderer.arena = arena_init_sized(Gigabytes(1), ARENA_COMMIT_SIZE, "");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  OGL_Shader vertex_shader   = opengl_make_shader(Str8(VERTEX_SHADER_PATH), GL_VERTEX_SHADER);
  OGL_Shader fragment_shader = opengl_make_shader(Str8(FRAGMENT_SHADER_PATH), GL_FRAGMENT_SHADER);
  OGL_Shader shaders[]       = { vertex_shader, fragment_shader };
  OglProgram = opengl_make_program(shaders, 2);
  ogl_delete_shader(vertex_shader);
  ogl_delete_shader(fragment_shader);

  Renderer.instanced_max   = Megabytes(8) / sizeof(Instanced_Data);
  Renderer.instanced_data  = ArenaPush(Renderer.arena, Instanced_Data, Renderer.instanced_max);
  Renderer.instanced_count = 0;

  glGenBuffers(1, &Vbo_InstancedData);
  glBindBuffer(GL_ARRAY_BUFFER, Vbo_InstancedData);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Instanced_Data) * Renderer.instanced_max, NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  Vertex unit_quad[] = {
    { vec3f32(-0.5f, -0.5f, 0.0f), vec2f32(0.0f, 0.0f) },
    { vec3f32( 0.5f, -0.5f, 0.0f), vec2f32(1.0f, 0.0f) },
    { vec3f32( 0.5f,  0.5f, 0.0f), vec2f32(1.0f, 1.0f) },
    { vec3f32(-0.5f,  0.5f, 0.0f), vec2f32(0.0f, 1.0f) },
  };
  u32 indices[] = { 0, 1, 2, 0, 2, 3 };

  glGenVertexArrays(1, &Vao_Quad);
  glGenBuffers(1, &Vbo_Quad);
  glGenBuffers(1, &Ebo_Quad);
  glBindVertexArray(Vao_Quad);

  glBindBuffer(GL_ARRAY_BUFFER, Vbo_Quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(unit_quad), unit_quad, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OffsetOfMember(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OffsetOfMember(Vertex, uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo_Quad);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, Vbo_InstancedData);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, transform.translation));
  glVertexAttribDivisor(2, 1);
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, transform.rotation));
  glVertexAttribDivisor(3, 1);
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, transform.scale));
  glVertexAttribDivisor(4, 1);
  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, color));
  glVertexAttribDivisor(5, 1);
  glEnableVertexAttribArray(6);
  glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, texture_id));
  glVertexAttribDivisor(6, 1);
  glEnableVertexAttribArray(7);
  glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, uv_min));
  glVertexAttribDivisor(7, 1);
  glEnableVertexAttribArray(8);
  glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(Instanced_Data), (void*)OffsetOfMember(Instanced_Data, uv_max));
  glVertexAttribDivisor(8, 1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGetIntegerv(GL_MAX_TEXTURE_SIZE, (s32*)&Renderer.texture_max);
  Renderer.textures = ArenaPush(Renderer.arena, GLuint, Renderer.texture_max);
  Renderer.texture_count = 0;

  renderer_load_font(Str8(FONT_INCONSOLATA), 32.0f);
}

internal void renderer_begin_frame() {
    glClearColor(0.1, 0.6, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

internal void renderer_end_frame(Mat4f32 view, Mat4f32 projection) {
  glUseProgram(OglProgram);

  local_persist GLint texture_units[32] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
  opengl_set_uniform_mat4fv(OglProgram, "view", view);
  opengl_set_uniform_mat4fv(OglProgram, "projection", projection);

  for (u32 i = 0; i < Renderer.texture_count; ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, Renderer.textures[i]);
  }

  glUniform1iv(glGetUniformLocation(OglProgram, "textures"), Renderer.texture_count, texture_units);
  opengl_set_uniform_u32(OglProgram, "texture_count", Renderer.texture_count);

  glBindBuffer(GL_ARRAY_BUFFER, Vbo_InstancedData);
  glBufferData(GL_ARRAY_BUFFER, Renderer.instanced_count * sizeof(Instanced_Data), Renderer.instanced_data, GL_STREAM_DRAW);

  if (Renderer.instanced_count > 0) {
    glBindVertexArray(Vao_Quad);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, Renderer.instanced_count);
    glBindVertexArray(0);
  }

  Renderer.instanced_count = 0;

  SwapBuffers(_DeviceContextHandle);
}

internal u32 renderer_load_font(String8 path, f32 font_height) {
    Arena_Temp scratch = scratch_begin(0, 0);
    u32 result = 0;

    if (Renderer.texture_count >= Renderer.texture_max) return 0;

    File_Data file_data = file_load(scratch.arena, path);
    if (!file_data.data.str || file_data.data.size == 0) return 0;

    stbtt_fontinfo font_info;
    if (!stbtt_InitFont(&font_info, (u8*)file_data.data.str, 0)) return 0;

    s32 atlas_width = 512, atlas_height = 512;
    u8* atlas_bitmap = ArenaPush(scratch.arena, u8, atlas_width * atlas_height);

    stbtt_packedchar char_data[95];
    stbtt_pack_context pack;
    stbtt_PackBegin(&pack, atlas_bitmap, atlas_width, atlas_height, atlas_width, 1, NULL);
    stbtt_PackSetOversampling(&pack, 1, 1);
    stbtt_PackFontRange(&pack, (u8*)file_data.data.str, 0, font_height, 32, 95, char_data);
    stbtt_PackEnd(&pack);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlas_width, atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, atlas_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    u32 texture_index = Renderer.texture_count++;
    Renderer.textures[texture_index] = texture;
    result = texture_index + 1;

    f32 max_height = 0.0f;
    f32 min_y = 0.0f;

    for (s32 i = 0; i < 95; i++) {
      Glyph* glyph = &Renderer.font.glyphs[i];
      stbtt_packedchar* ch = &char_data[i];

      glyph->uv_min  = vec2f32((f32)ch->x0 / atlas_width, (f32)ch->y0 / atlas_height);
      glyph->uv_max  = vec2f32((f32)ch->x1 / atlas_width, (f32)ch->y1 / atlas_height);
      glyph->size    = vec2f32(ch->x1 - ch->x0, ch->y1 - ch->y0);
      glyph->offset  = vec2f32(ch->xoff, ch->yoff);
      glyph->advance = ch->xadvance;

      f32 y_top = ch->yoff;
      f32 y_bottom = ch->yoff + (ch->y1 - ch->y0);

      if (y_top < min_y) min_y = y_top;
      if (y_bottom > max_height) max_height = y_bottom;
    }

    scratch_end(&scratch);

    Renderer.font.line_height = max_height - min_y;
    Renderer.font.height      = font_height;
    Renderer.font.texture_id  = result;

    return result;
}

internal f32 renderer_push_text(Vec2f32 screen_position, Vec4f32 color, f32 scale, String8 text) {
  f32 x_start  = screen_position.x;
  f32 y_cursor = screen_position.y;

  Font* font      = &Renderer.font;
  f32 line_height = font->line_height * scale;
  f32 max_y       = y_cursor;

  for (u64 i = 0; i < text.size; ++i) {
    char c = text.str[i];

    if (c == '\n') {
      y_cursor         += line_height;
      screen_position.x = x_start;
      continue;
    }

    if (c < 32 || c > 126) continue;

    Glyph* glyph = &font->glyphs[c - 32];
    Vec2f32 pos  = vec2f32(screen_position.x + glyph->offset.x * scale, y_cursor + glyph->offset.y * scale);
    Vec2f32 size = vec2f32(glyph->size.x * scale, glyph->size.y * scale);

    Instanced_Data* data        = &Renderer.instanced_data[Renderer.instanced_count++];
    data->transform.translation = vec3f32(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
    data->transform.rotation    = quatf32_identity();
    data->transform.scale       = vec3f32(size.x, size.y, 1.0f);
    data->color                 = color;
    data->texture_id            = font->texture_id;
    data->uv_min                = glyph->uv_min;
    data->uv_max                = glyph->uv_max;

    screen_position.x += glyph->advance * scale;
    max_y = Max(max_y, y_cursor + line_height);
  }

  return max_y - screen_position.y;
}
