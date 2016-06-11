#ifndef RedPlasma_H
#define RedPlasma_H

#include "./Weapon.h"
#include "./defines.h"

class RedPlasma: public Weapon {
  public:
    RedPlasma();
    void update();
    void draw();
    void setup(float x, float y, float dirX, float dirY, float angle);
    void reset();
    void clean();
  protected:
  
};

#endif
