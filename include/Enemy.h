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
    
    int getNumOfMounts() { return maxWeaponMounts; }
    float getMountX(int index) { return WeaponMount[index]->getX(); }
    float getMountY(int index) { return WeaponMount[index]->getY(); }
    float getMountWidth(int index) { return WeaponMount[index]->getWidth(); }
    float getMountHeight(int index) { return WeaponMount[index]->getHeight(); }
    
    int bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
    float getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
    float getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }
    
    int getTotalNumOfBullets() { 
      int totalBullets = 0; 
      for(int i = 0; i < maxWeaponMounts; ++i) { 
        totalBullets += 5;//WeaponMount[i]->getNumBullets(); 
      }
      return totalBullets;
    }

    void takeDamage(int damage) {
      health -= damage;
      if(health <= 0)
        visible = false;
    }
    
        
    void setVisible(bool visible) { 
      this->visible = visible; 
      for(int i = 0; i < maxWeaponMounts; ++i) {
        WeaponMount[0]->setVisible(visible);
      } 
    }

    std::vector<Mount*> getMount() { return WeaponMount; }
  protected:
    int health;
    float x,y, width, height, speed;
    bool visible;
    GLuint Texture;
    std::vector<Mount*> WeaponMount;
    int maxWeaponMounts;    
};

#endif
