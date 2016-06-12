#ifndef WEAPON
#define WEAPON

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"

class Weapon {
  public:

    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    virtual void update() = 0;
    virtual void setup(float x, float y, float dirX, float dirY, float angle) = 0;

    void setVisible(bool visible) { this->visible = visible; }
    
    bool getVisible() { return visible; }
    
    int getDamage() { return damage; }
    int hit() { visible = false; return damage; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    
  protected:
    int damage;
    float angle;
    bool visible;
    float directionX, directionY;
    float x,y, width, height, speed;
    
    static GLuint getBluePlasmaTexture() {
      static GLuint bluePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/BluePlasma.png");
      return bluePlasmaTexture;
    }
    static GLuint getGreenPlasmaTexture() {
      static GLuint greenPlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/GreenPlasma.png");
      return greenPlasmaTexture;
    }
    static GLuint getRedPlasmaTexture() {
      static GLuint redPlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/RedPlasma.png");
      return redPlasmaTexture;
    }
};

#endif
