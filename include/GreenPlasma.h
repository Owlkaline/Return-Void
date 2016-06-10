#ifndef GREENPLASMA_H
#define GREENPLASMA_H

#include "./Weapon.h"
#include "./defines.h"

class GreenPlasma: public Weapon {
  public:
    GreenPlasma();
    void update();
    void draw();
    void setup(float x, float y, float dirX, float dirY, float angle);
    void reset();
    void clean();
  protected:
  
};

#endif
