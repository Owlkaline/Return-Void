#ifndef HYPNOENEMY_H
#define HYPNOENEMY_H

#include "./Enemy.h"

class HypnoEnemy: public Enemy {
  public:
    ~HypnoEnemy();
    void setup(float drop);
    void update(float Px, float Py);
    void reset();
    void setTexture();
    void setX(float x);
    void setY(float y);
  protected:
    float startX, startY, amp;
    float movementAngle;
    bool hasFinished, rightSide;
};

#endif
