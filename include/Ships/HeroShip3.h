#ifndef HEROSHIP_H
#define HEROSHIP_H

#include "./Ship.h"

class HeroShip3: public Ship {
  public:
    HeroShip3();
    ~HeroShip3();

    std::string getTexture();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState); 
  protected:   
     
    void special(); 
};

#endif
