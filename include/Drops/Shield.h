#ifndef SHIELD_H
#define SHIELD_H

#include "./Drops.h"

class Shield: public Drops {
  public:
    Shield();
    void draw();
    void setup(float x, float y);
    void update();
    int getType();
  protected:
};

#endif
