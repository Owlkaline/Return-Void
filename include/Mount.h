#ifndef MOUNT
#define MOUNT

#include <vector>
#include <time.h>
#include <math.h>

#include "./LoadTexture.h"

class Mount {
  public:
    virtual void setup(float offsetX, float offsetY) = 0;
    virtual void draw() = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle) = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    virtual void fire(float directionX, float directionY) = 0;
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
   
  protected:
    int health;
    float x,y, width, height;
    float fireRate;
    float angle;
    float offsetX, offsetY;
    clock_t t;
    GLuint Texture;
};

#endif
