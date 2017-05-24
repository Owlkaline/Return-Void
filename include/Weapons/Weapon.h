#ifndef WEAPON
#define WEAPON

#include "../defines.h"

#include "../GraphicsHandler.h"

class Weapon {
  public:
    virtual void tick(float deltaTime) = 0;
    virtual void draw(GraphicsHandler *graphics) = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    
    virtual void setup(float x, float y, float dirX, float dirY, float angle) = 0;
       
    void setIsBoss(bool boss) { isBoss = boss; }
    void setDamage(float damage) { this->damage = damage; }
    void setVisible(bool visible) { this->visible = visible; }
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }  
      
    bool getImmortal() { return immortal; }
    bool getIsBoss() { return isBoss; }
    bool getVisible() { return visible; }  
    bool hasExploded() { return explode; }  
        
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getDamage() { return damage; }
    float getDirectionX() { return directionX; }
    float getDirectionY() { return directionY; }
    float hit() { 
      if(!immortal) 
        visible = false;
      if(active) {
        active = false;
        activeTimer = 20;
        return damage;
      }   
      return 0;
    }    
    
    virtual void update(float deltaTime) { 
      if(visible) {
        tick(deltaTime);
        if(!active) {
          activeTimer-=1*deltaTime;
          if(activeTimer <= 0)
            active = true;
        }
      }
      if(y > SPACE_Y_RESOLUTION+height || y < -height || x < -width || x > SPACE_X_RESOLUTION+width)
        visible = false;
    }
       
  protected:
    bool isBoss;
    bool explode;
    bool visible;
    bool immortal;
    bool active;
    
    float activeTimer;
    float angle; 
    float damage;  
    float offsetX, offsetY;
    float directionX, directionY;
    float x, y, width, height, speed;
};

#endif
