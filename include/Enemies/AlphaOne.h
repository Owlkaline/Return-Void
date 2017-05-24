#ifndef ALPHAONE_H
#define ALPHAONE_H

#include "./Enemy.h"

class AlphaOne: public Enemy {
  public:
    AlphaOne();
    ~AlphaOne();
    
    void reset();
    void defaults();
    std::string getTexture();
    void update(float Px, float Py, float deltaTime);
};

#endif
