#ifndef GALACTICSHIP_H
#define GALACTICSHIP_H

#include "./Ship.h"

class GalacticShip: public Ship {
  public:
    GalacticShip();
    ~GalacticShip();

    void setTexture();
    void defaults();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
    
  protected:  
  
    void boost() { hasBoost = true; boostTimer = 100; extraSpeed = 3; }
    bool hasBoost;
    float boostTimer;    
};

#endif
