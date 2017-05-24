#ifndef HYPNOENEMY_H
#define HYPNOENEMY_H

#include "./Enemy.h"

class HypnoEnemy: public Enemy {
  public:
    HypnoEnemy();
    ~HypnoEnemy();
        
    void reset();
    void defaults();
    std::string getTexture();
    void setX(float x);
    void setY(float y);
    void update(float Px, float Py, float deltaTime);
  protected:
};

#endif
