#ifndef PURPLEPLASMA_H
#define PURPLEPLASMA_H

#include "./Weapon.h"

class PurplePlasma: public Weapon {
  public:
    PurplePlasma();
    
    void draw(); 
    void reset();
    void clean();
    void tick();
    void setup(float x, float y, float dirX, float dirY, float angle);  
};

#endif
