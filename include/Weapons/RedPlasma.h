#ifndef RedPlasma_H
#define RedPlasma_H

#include "./Weapon.h"

class RedPlasma: public Weapon {
  public:
    RedPlasma();

    void draw();
    void reset();
    void clean();
    void tick(float deltaTime);
    void setup(float x, float y, float dirX, float dirY, float angle);
};

#endif
