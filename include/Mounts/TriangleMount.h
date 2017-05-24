#ifndef TRIANGLEMOUNT_H
#define TRIANGLEMOUNT_H

#include "./Mount.h"

class TriangleMount: public Mount {
  public:
    TriangleMount();
    ~TriangleMount();
    
    std::string getTexture();
    void defaults();
    void draw(GraphicsHandler *graphics);
  protected:
};

#endif
