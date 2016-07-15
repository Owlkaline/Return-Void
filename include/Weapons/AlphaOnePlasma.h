#ifndef AlphaOnePlasma_H
#define AlphaOnePlasma_H

#include "./Weapon.h"

class AlphaOnePlasma: public Weapon {
  public:
    AlphaOnePlasma();
    
    void draw(); 
    void reset();
    void clean();
    void tick();
    void setup(float x, float y, float dirX, float dirY, float angle);  
};

#endif
