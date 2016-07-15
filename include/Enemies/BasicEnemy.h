#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "./Enemy.h"

class BasicEnemy: public Enemy {
  public:
    BasicEnemy();
    ~BasicEnemy();
    void defaults();
    void update(float Px, float Py);
    void reset();
    void setTexture();
};

#endif
