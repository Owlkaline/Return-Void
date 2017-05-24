#ifndef MOUNTTYPE3
#define MOUNTTYPE3

#include "Mount.h"

class MountType3: public Mount {
  public:
    MountType3(float offsetX, float offsetY);
    
    void reset(float x, float y);
    std::string getTexture();
  protected:
};

#endif
