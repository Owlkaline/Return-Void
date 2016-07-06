#ifndef HYPNOMOUNT_H
#define HYPNOMOUNT_H

#include "./Mount.h"

class HypnoMount: public Mount {
  public:
    HypnoMount();
    ~HypnoMount();
    
    void draw();
    void setup();
    void reset();
    void setup(int variant);
    void update(float x, float y, float directionX, float directionY, float angle, bool isShooting);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);
  protected:
    void addBullet();
    int isLeft;
};

#endif
