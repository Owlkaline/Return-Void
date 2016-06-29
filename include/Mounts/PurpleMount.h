#ifndef PURPLEMOUNT_H
#define PURPLEMOUNT_H

#include "./Mount.h"

class PurpleMount: public Mount {
  public:
    PurpleMount();
    
    void draw();
    void reset();
    void setup();
    void setup(int variant);
    void update(float x, float y, float directionX, float directionY, float angle);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);

  protected:   
    int variant;
    int maxMounts;
    void addBullet();
};

#endif
