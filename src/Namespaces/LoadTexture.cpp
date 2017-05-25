#include "../include/Namespaces/LoadTexture.h"

#include <stb_image.h>

GLuint txt::LoadTexture( const char * filename ) {
  stbi_set_flip_vertically_on_load(false);
  int w;
  int h;
  int comp;
  unsigned char* image = stbi_load(filename, &w, &h, &comp, STBI_rgb_alpha);

  if(image == nullptr) {
    std::string err = "Failed to load texture: ";
    err += filename;
    throw std::runtime_error(err);
  }
  GLuint m_texture;
  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if(comp == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  else if(comp == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(image);

  return m_texture;

}
