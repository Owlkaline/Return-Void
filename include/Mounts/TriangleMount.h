#ifndef TRIANGLEMOUNT_H
#define TRIANGLEMOUNT_H

#include "./Mount.h"

class TriangleMount: public Mount {
  public:
    TriangleMount();
    ~TriangleMount();
    
    void setTexture();
    void reset();
    void defaults();
  protected:
};

#endif
