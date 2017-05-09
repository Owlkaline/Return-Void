#ifndef LOADTEXTURE
#define LOADTEXTURE

#include "../defines.h"
#include <string>
#include <stdio.h>

#define TEXTURE_LOAD_ERROR 0

namespace txt {
  GLuint LoadTexture( const char * filename );
}

#endif
