#ifndef MOUNTTYPE1
#define MOUNTTYPE1

#include "Mount.h"

class MountType1: public Mount {
  public:
    MountType1(float offsetX, float offsetY);
    
    void reset(float x, float y);
    std::string getTexture();
  protected:
};

#endif
