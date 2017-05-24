#ifndef PURPLEPLASMA_H
#define PURPLEPLASMA_H

#include "./Weapon.h"

class PurplePlasma: public Weapon {
  public:
    PurplePlasma();
    
    void draw(GraphicsHandler *graphics); 
    void reset();
    void clean();
    void tick(float deltaTime);
    void setup(float x, float y, float dirX, float dirY, float angle);  
};

#endif
