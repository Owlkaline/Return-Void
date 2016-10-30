#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "./Enemy.h"

class BasicEnemy: public Enemy {
  public:
    BasicEnemy();
    ~BasicEnemy();
       
    void reset();
    void setTexture();
    void update(float Px, float Py, float deltaTime);
};

#endif
