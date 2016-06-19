#ifndef CORRUPTEDSTARSHIP_H
#define CORRUPTEDSTARSHIP_H

#include "./Enemy.h"

class CorruptedStarShip: public Enemy {
  public:
    void setup(float drop);
    void update();
    void reset();
    void draw();
    void setX(float x);
    void setY(float y);
  protected:
    float startX, startY, amp;
};

#endif
