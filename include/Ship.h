#ifndef SHIP_H
#define SHIP_H

#include "./defines.h"
#include "./LoadTexture.h"
#include <math.h>

class Ship {
  public:
    Ship();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void draw();
    void setup();
    //float getX();
    //float getY();
    //float getHealth();
  protected:
    //void respawn();
    GLuint textures[3];
    
    float x, y;
    //int health;
    float speed;
    float angle;
    float width, height;
    float directionX, directionY;
    //float directionX, directionY;   
};

#endif
