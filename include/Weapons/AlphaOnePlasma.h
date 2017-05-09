#ifndef AlphaOnePlasma_H
#define AlphaOnePlasma_H

#include <vector>

#include "./Weapon.h"

class AlphaOnePlasma: public Weapon {
  public:
    AlphaOnePlasma();
    
    void draw(); 
    void tick(float deltaTime);
    void reset();
    void clean();
    
    void setup(float x, float y, float dirX, float dirY, float angle);  
  protected:   
};

#endif
