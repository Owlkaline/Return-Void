#ifndef WEAPON
#define WEAPON

#include "../defines.h"

#include "../Namespaces/LoadTexture.h"

class Weapon {
  public:
    virtual void tick(float deltaTime) = 0;
    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    
    virtual void setup(float x, float y, float dirX, float dirY, float angle) = 0;
       
    void setIsBoss(bool boss) { isBoss = boss; }
    void setDamage(float damage) { this->damage = damage; }
    void setVisible(bool visible) { this->visible = visible; }
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }  
      
    bool getIsBoss() { return isBoss; }
    bool getVisible() { return visible; }    
        
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getDamage() { return damage; }
    float hit() { visible = false; return damage; }    
    
    virtual void update(float deltaTime) { 
      if(visible)
        tick(deltaTime);
      if(y > SPACE_Y_RESOLUTION+height || y < -height || x < -width || x > SPACE_X_RESOLUTION+width)
        visible = false;
    }
       
  protected:
    bool isBoss;
    bool visible;
     
    float angle; 
    float damage;  
    float offsetX, offsetY;
    float directionX, directionY;
    float x, y, width, height, speed;
    
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
    static GLuint getPurplePlasmaTexture() {
      static GLuint purplePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/PurplePlasma.png");
      return purplePlasmaTexture;
    }
    
    static GLuint getSpiralTexture() {
      static GLuint spiralTexture = txt::LoadTexture("Textures/Game/Weapons/Spiral.png");
      return spiralTexture;
    }
    
    static GLuint getDotBulletTexture() {
      static GLuint dotBulletTexture = txt::LoadTexture("Textures/Game/Weapons/DotBullet.png");
      return dotBulletTexture;
    }
    
    static GLuint getAlphaOnePlasmaTexture() {
      static GLuint alphaOnePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/AlphaOnePlasma.png");
      return alphaOnePlasmaTexture;
    }
};

#endif
