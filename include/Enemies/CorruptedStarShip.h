#ifndef CORRUPTEDSTARSHIP_H
#define CORRUPTEDSTARSHIP_H

#include "./Enemy.h"

class CorruptedStarShip: public Enemy {
  public:
    void setup();
    void update();
    void reset();
    void draw();
};

#endif
