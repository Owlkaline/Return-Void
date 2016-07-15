#ifndef HYPNOENEMY_H
#define HYPNOENEMY_H

#include "./Enemy.h"

class HypnoEnemy: public Enemy {
  public:
    HypnoEnemy();
    ~HypnoEnemy();
    void defaults();
    void update(float Px, float Py);
    void reset();
    void setTexture();
    void setX(float x);
    void setY(float y);
  protected:
};

#endif
