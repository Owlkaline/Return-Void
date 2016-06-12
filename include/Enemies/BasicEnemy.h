#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "./Enemy.h"

class BasicEnemy: public Enemy {
  public:
    void setup();
    void update();
    void reset();
    void draw();
};

#endif
