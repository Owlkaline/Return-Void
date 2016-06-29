#ifndef MOUNT
#define MOUNT

#include <vector>
#include <math.h>

#include "../Weapons/Spiral.h"
#include "../Weapons/RedPlasma.h"
#include "../Weapons/BluePlasma.h"
#include "../Weapons/GreenPlasma.h"
#include "../Weapons/PurplePlasma.h"
#include "../Namespaces/LoadTexture.h"

class Mount {
  public:
    virtual void draw() = 0;
    virtual void setup() = 0;
    virtual void reset() = 0;
    virtual void setup(int variant) = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle) = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) = 0;
   
    void takeDamage(int damage) { health -= damage; }
    void setVisible(bool visible) { this->visible = visible; }
    void tick() { ticks++; if(ticks > timer) { fire(); ticks = 0; } }  
    void clean() {   bullets.erase(bullets.begin(), bullets.end()); ticks = 0;};      
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }

    void fire() { 
      if(visible) {
        currentTexture = 1;
        addBullet();
        int i = bullets.size()-1;
        bullets[i]->setup(x, y, dirX, dirY, angle);
        bullets[i]->setVisible(true);
      }
    }
    

    
    bool isVisible() { return visible; }
    
    int getNumBullets() { return bullets.size(); }
    int bulletHit(int index) { return bullets[index]->hit(); }

    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getBulletX(int index) { return bullets[index]->getX(); }
    float getBulletY(int index) { return bullets[index]->getY(); }
    float getBulletWidth(int index) { return bullets[index]->getWidth(); }
    float getBulletHeight(int index) { return bullets[index]->getHeight(); }
   
  protected:
    virtual void addBullet()=0;
  
    int health;
    float angle;   
    bool visible;
    float fireRate;
    int ticks, timer;
    float dirX, dirY;
    int currentTexture;
    float offsetX, offsetY;
    float x,y, width, height;

    std::vector<Weapon*> bullets; 
    
    static GLuint getBasicMountTexture() {
      static GLuint basicMountTexture = txt::LoadTexture("Textures/Game/Weapons/BasicMount.png");
      return basicMountTexture;
    }
    
    static GLuint getBasicMountBrightTexture() {
      static GLuint basicMountBrightTexture = txt::LoadTexture("Textures/Game/Weapons/BasicMountBright.png");
      return basicMountBrightTexture;
    }
    
    static GLuint getTriangleMountTexture() {
      static GLuint triangleMountTexture = txt::LoadTexture("Textures/Game/Weapons/TriangleMount.png");
      return triangleMountTexture;
    }
    
    static GLuint getPurpleMountTexture() {
      static GLuint purpleMountTexture = txt::LoadTexture("Textures/Game/Weapons/PurpleMount.png");
      return purpleMountTexture;
    }
    
    static GLuint getHypnoMountTexture(int i) {
      static GLuint hypnoMountLeftTexture = txt::LoadTexture("Textures/Game/Weapons/HypnoMountLeft.png");
      static GLuint hypnoMountRightTexture = txt::LoadTexture("Textures/Game/Weapons/HypnoMountRight.png");
      
      switch(i) {
        case 0:
          return hypnoMountLeftTexture;
        case 1:
          return hypnoMountRightTexture;
      }
      return hypnoMountLeftTexture;
    }
};

#endif
