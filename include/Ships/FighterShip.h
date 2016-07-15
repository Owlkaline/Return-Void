#ifndef FIGHTERSHIP_H
#define FIGHTERSHIP_H

#include "./Ship.h"

class FighterShip: public Ship {
  public:
    FighterShip();
    ~FighterShip();

    void setTexture();
    void defaults();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
    
  protected:      
};

#endif
