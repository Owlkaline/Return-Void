#ifndef HYPNOENEMY_H
#define HYPNOENEMY_H

#include "./Enemy.h"

class HypnoEnemy: public Enemy {
  public:
    void setup(float drop);
    void update(float Px, float Py);
    void reset();
    void draw();
    void setX(float x);
    void setY(float y);
  protected:
    float startX, startY, amp;
    float angle;
};

#endif
