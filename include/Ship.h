#ifndef SHIP_H
#define SHIP_H

#define MAXWEAPONS 3

#include <math.h>

#include "./defines.h"
#include "./LoadTexture.h"
#include "./BasicMount.h"

class Ship {
  public:
    Ship();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void draw();
    void setup();
    float getX();
    float getY();
    float getDirectionX();
    float getDirectionY();
    float getDistanceFromCursor();
    //float getHealth();
  protected:
    //void respawn();
    const float mountPosX[MAXWEAPONS] = {18, -22, -2};
    const float mountPosY[MAXWEAPONS] = {0, 0, 30};
    
    GLuint textures[MAXWEAPONS];
    Mount* mountSlot[MAXWEAPONS];
    
    float x, y;
    //int health;
    float speed;
    float angle;
    float width, height;
    float directionX, directionY, distanceFromCursor;
    //float directionX, directionY;   
};

#endif
