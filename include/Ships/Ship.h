#ifndef SHIP_H
#define SHIP_H

#define MAXWEAPONS 3

#include <math.h>

#include "../defines.h"
#include "../Mounts/BasicMount.h"
#include "../Mounts/TriangleMount.h"
#include "../Namespaces/LoadTexture.h"

class Ship {
  public:
    Ship();
    
    void draw();
    void setup();
    void clean();
    void takeDamage(int damage);
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);  
    
    bool getVisible();
    
    int getNumOfMounts();
    int getNumOfBullets(int index);
    int bulletHit(int mIndex, int bIndex);
    
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getDirectionX();
    float getDirectionY();
    float getDistanceFromCursor();
    float getBulletX(int mIndex, int bIndex);
    float getBulletY(int mIndex, int bIndex);
    float getBulletWidth(int mIndex, int bIndex);
    float getBulletHeight(int mIndex, int bIndex);
    
  protected:   
    int tick;        
    int health;
    float x, y;
    float speed;
    float angle;
    bool visible, tookDamage;
    float width, height;
    float directionX, directionY, distanceFromCursor;
  
    GLuint textures[3];
    Mount* WeaponMount[MAXWEAPONS];
};

#endif
