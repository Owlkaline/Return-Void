#ifndef GREENPLASMA_H
#define GREENPLASMA_H

#include "./Weapon.h"

class GreenPlasma: public Weapon {
  public:
    GreenPlasma();
       
    void draw();    
    void reset();
    void clean();
    void tick();
    void setup(float x, float y, float dirX, float dirY, float angle);
};

#endif
