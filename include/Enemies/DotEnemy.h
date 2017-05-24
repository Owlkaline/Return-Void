#ifndef DOTENEMY_H
#define DOTENEMY_H

#include "./Enemy.h"

class DotEnemy: public Enemy {
  public:
    DotEnemy();
    ~DotEnemy();
        
    void reset();
    void defaults();
    std::string getTexture();
    void setX(float x);
    void setY(float y);
    void update(float Px, float Py, float deltaTime);
  protected:
};

#endif
