#ifndef BLUEPLASMA_H
#define BLUEPLASMA_H

#include "./Weapon.h"

class BluePlasma: public Weapon {
  public:
    BluePlasma();
    
    void draw(); 
    void tick();
    void reset();
    void clean();    
    void setup(float x, float y, float dirX, float dirY, float angle);  
};

#endif
