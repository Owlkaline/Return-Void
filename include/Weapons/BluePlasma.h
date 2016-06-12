#ifndef BLUEPLASMA_H
#define BLUEPLASMA_H

#include "./Weapon.h"

class BluePlasma: public Weapon {
  public:
    BluePlasma();
    void update();
    void draw();
    void setup(float x, float y, float dirX, float dirY, float angle);
    void reset();
    void clean();
  protected:
  
};

#endif
