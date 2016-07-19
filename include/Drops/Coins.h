#ifndef COINS_H
#define COINS_H

#include "./Drops.h"

class Coins: public Drops {
  public:
    Coins();
    
    void draw();    
    void update();
    void setup(float x, float y);
    
    int getType();
  protected:
  
};

#endif
