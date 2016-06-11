#ifndef CorruptedStarShip_H
#define CorruptedStarShip_H

#include "./Enemy.h"

class CorruptedStarShip: public Enemy {
  public:
    void setup();
    void update();
    void reset();
    void draw();
  protected:
};

#endif
