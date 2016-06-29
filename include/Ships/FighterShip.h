#ifndef FIGHTERSHIP_H
#define FIGHTERSHIP_H

#include "./Ship.h"

class FighterShip: public Ship {
  public:
    FighterShip();

    void draw();
    void setup();
    void clean();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
    
  protected:      
};

#endif
