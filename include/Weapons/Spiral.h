#ifndef SPIRAL_H
#define SPIRAL_H

#include "./Weapon.h"

class Spiral: public Weapon {
  public:
    Spiral();
       
    void draw();    
    void reset();
    void clean();
    void tick();
    void setup(float x, float y, float dirX, float dirY, float angle);
};

#endif
