#ifndef MOUNTTYPE2
#define MOUNTTYPE2

#include "Mount.h"

class MountType2: public Mount {
  public:
    MountType2(float offsetX, float offsetY);
    
    void reset(float x, float y);
    void setTexture();  
  protected:
};

#endif
