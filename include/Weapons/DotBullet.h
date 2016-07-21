#ifndef DOTBULLET_H
#define DOTBULLET_H

#include "./Weapon.h"

class DotBullet: public Weapon {
  public:
    DotBullet();
    
    void draw(); 
    void tick();
    void reset();
    void clean();    
    void setup(float x, float y, float dirX, float dirY, float angle);  
};

#endif
