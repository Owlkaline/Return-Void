#ifndef FIGHTERSHIP_H
#define FIGHTERSHIP_H

#include "./Ship.h"

class FighterShip: public Ship {
  public:
    FighterShip();
    ~FighterShip();

    std::string getTexture();    
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
    
  protected:      
};

#endif
