#ifndef TRIANGLEMOUNT_H
#define TRIANGLEMOUNT_H

#include "./Mount.h"

class TriangleMount: public Mount {
  public:
    TriangleMount();
    ~TriangleMount();
    
    void draw();
    void reset();
    void setup();
    void setup(int variant);
    void update(float x, float y, float directionX, float directionY, float angle, bool isShooting);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);
    
  protected:
    void addBullet();
};

#endif
