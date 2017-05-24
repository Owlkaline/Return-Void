#ifndef CORRUPTEDSTARSHIP_H
#define CORRUPTEDSTARSHIP_H

#include "./Enemy.h"

class CorruptedStarShip: public Enemy {
  public:
    CorruptedStarShip();
    ~CorruptedStarShip();
    
    void reset();
    void defaults();
    std::string getTexture();
    void setX(float x);
    void setY(float y);
    void update(float Px, float Py, float deltaTime);
  protected:
};

#endif
