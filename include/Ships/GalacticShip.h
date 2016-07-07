#ifndef GALACTICSHIP_H
#define GALACTICSHIP_H

#include "./Ship.h"

class GalacticShip: public Ship {
  public:
    GalacticShip();
    ~GalacticShip();

    void draw();
    void setup();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
    
  protected:      
};

#endif
