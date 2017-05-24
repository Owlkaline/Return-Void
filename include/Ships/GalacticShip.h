#ifndef GALACTICSHIP_H
#define GALACTICSHIP_H

#include "./Ship.h"

class GalacticShip: public Ship {
  public:
    GalacticShip();
    ~GalacticShip();

    std::string getTexture();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
  protected:  
  
    void special();   
};

#endif
