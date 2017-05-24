#ifndef LOADTEXTURE
#define LOADTEXTURE

#include <string>
#include <stdio.h>
#include <stdexcept>
// GLFW
#include <GLFW/glfw3.h>

#define TEXTURE_LOAD_ERROR 0

namespace txt {
  GLuint LoadTexture( const char * filename );
}

#endif
