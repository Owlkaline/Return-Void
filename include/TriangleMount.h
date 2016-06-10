#ifndef TRIANGLEMOUNT_H
#define TRIANGLEMOUNT_H

#include "./Mount.h"

class TriangleMount: public Mount {
  public:
    TriangleMount();
    void update(float x, float y, float directionX, float directionY, float angle);

    void setup(float offsetX, float offsetY);
    void reset();

  protected:
    void addBullet();
};


#endif
