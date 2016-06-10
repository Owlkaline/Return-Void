#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <math.h>

#include "./defines.h"
#include "./LoadTexture.h"
#include "./BasicMount.h"
//#include "./BluePlasma.h"
//#include "./GreenPlasma.h"

class Enemy {
  public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void reset() = 0;
    virtual void draw() = 0;
    void clean() { WeaponMount.erase(WeaponMount.begin(), WeaponMount.end()); }
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    
    bool isVisible() { return visible; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }

   
  protected:
    int health;
    float x,y, width, height;
    bool visible;
    GLuint Texture;
    std::vector<Mount*> WeaponMount;
    int maxWeaponMounts;    
};

#endif
