#ifndef HEALTH_H
#define HEALTH_H

#include "./Drops.h"

class Health: public Drops {
  public:
    Health();
    void draw();
    void setup(float x, float y);
    void update();
    int getType();
  protected:

};

#endif
