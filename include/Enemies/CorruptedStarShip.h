#ifndef CORRUPTEDSTARSHIP_H
#define CORRUPTEDSTARSHIP_H

#include "./Enemy.h"

class CorruptedStarShip: public Enemy {
  public:
    CorruptedStarShip();
    ~CorruptedStarShip();
    void defaults();
    void update(float Px, float Py);
    void reset();
    void setTexture();
    void setX(float x);
    void setY(float y);
  protected:
};

#endif
