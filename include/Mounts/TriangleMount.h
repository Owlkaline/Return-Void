#ifndef TRIANGLEMOUNT_H
#define TRIANGLEMOUNT_H

#include "./Mount.h"

class TriangleMount: public Mount {
  public:
    TriangleMount();
    ~TriangleMount();
    
    void setTexture();
    void defaults();
    void draw();
  protected:
};

#endif
