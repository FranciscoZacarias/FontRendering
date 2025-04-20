#version 460 core

in vec4 frag_color;
in vec2 frag_texcoord;

flat in uint texture_id;

uniform sampler2D textures[32];
uniform uint texture_count;

out vec4 FragColor;

void main() {
  if (texture_id == 0 || texture_id > texture_count) {
    FragColor = frag_color;
  } else {
    float alpha = texture(textures[texture_id - 1], frag_texcoord).r;
    FragColor = vec4(frag_color.rgb, frag_color.a * alpha);
  }
}

