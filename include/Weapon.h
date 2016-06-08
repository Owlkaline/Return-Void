#ifndef WEAPON
#define WEAPON

#include "./LoadTexture.h"

class Weapon {
  public:
    virtual void setup(float x, float y, float dirX, float dirY, float angle) = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    
    void setVisible(bool visible) { this->visible = visible; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    bool getVisible() { return visible; }
    
  protected:
    float x,y, width, height, speed;
    float directionX, directionY;
    float angle;
    bool visible;
    GLuint Texture;
};

#endif
