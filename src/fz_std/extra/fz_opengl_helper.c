internal OGL_Shader opengl_make_shader(String8 source_path, GLenum kind) {
  Arena_Temp scratch = scratch_begin(0, 0);
  OGL_Shader result  = glCreateShader(kind);
  GLenum error       = glGetError();
  if (error != GL_NO_ERROR) {
    ERROR_MESSAGE_AND_EXIT("Error %u in glCreateShader.\n", error);
  }
    
  File_Data shader_source = file_load(scratch.arena, source_path);
  glShaderSource(result, 1, &shader_source.data.str, &(GLint)shader_source.data.size);
  glCompileShader(result);
  
  GLint success;
  glGetShaderiv(result, GL_COMPILE_STATUS, &success);
  if (!success) {
    char8 infoLog[1024];
    glGetShaderInfoLog(result, 1024, NULL, infoLog);
    printf("Error %d while compiling shader. Log: %s", success, infoLog);
    glDeleteShader(result);
    ERROR_MESSAGE_AND_EXIT("Error creating shader");
  }

  scratch_end(&scratch);
  return result;
}

internal OGL_Shader opengl_make_program(OGL_Shader *shaders, u32 count) {
  OGL_Shader result = glCreateProgram();
  
  for (u32 i = 0; i < count; i += 1){
    glAttachShader(result, shaders[i]);
  }
  glLinkProgram(result);
    
  GLint success;
  glGetProgramiv(result, GL_LINK_STATUS, &success);
  if(!success) {
    char8 infoLog[1024];
    glGetProgramInfoLog(result, 1024, NULL, infoLog);
    printf("Error %d linking compiled shader program. Log: %s", success, infoLog);
    for (u32 i = 0; i < count; i += 1){
      glDeleteShader(shaders[i]);
    }
    ERROR_MESSAGE_AND_EXIT("Error creating shader program");
  }
  
  return result;
}

internal void opengl_set_uniform_mat4fv(u32 program, const char8* uniform, Mat4f32 mat) {
  s32 uniform_location = glGetUniformLocation(program, uniform);
  if (uniform_location == -1) {
    printf("Mat4f32 :: Uniform %s not found for program %d\n", uniform, program);
  }
  glUniformMatrix4fv(uniform_location, 1, 1, &mat.data[0][0]);
}

internal void opengl_set_uniform_u32(u32 program, const char8* uniform, u32 value) {
  GLint uniform_location = glGetUniformLocation(program, uniform);
  if (uniform_location == -1) {
    printf("u32 :: Uniform %s not found for program %d\n", uniform, program);
  }
  glUniform1ui(uniform_location, value);
}

internal void ogl_delete_shader(OGL_Shader shader) {
  glDeleteShader(shader);
}