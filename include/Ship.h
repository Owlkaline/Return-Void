#ifndef SHIP_H
#define SHIP_H

#define MAXWEAPONS 3

#include <math.h>

#include "./defines.h"
#include "./LoadTexture.h"
#include "./BasicMount.h"
#include "./TriangleMount.h"

class Ship {
  public:
    Ship();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void draw();
    void setup();
    void clean();
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    bool getVisible();
    float getDirectionX();
    float getDirectionY();
    float getDistanceFromCursor();
    //float getHealth();
    void takeDamage(int damage);
    
  protected:
    //void respawn();
    const float mountPosX[MAXWEAPONS] = {18, -22, -2};
    const float mountPosY[MAXWEAPONS] = {0, 0, 50};
    
    GLuint textures[3];
    Mount* WeaponMount[MAXWEAPONS];
    
    float x, y;
    int health;
    float speed;
    float angle;
    bool visible;
    float width, height;
    float directionX, directionY, distanceFromCursor;
    //float directionX, directionY;   
};

#endif
