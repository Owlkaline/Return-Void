#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <math.h>

#include "../defines.h"
#include "../Mounts/BasicMount.h"
#include "../Namespaces/LoadTexture.h"

class Enemy {
  public:
    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual void setup() = 0;
    virtual void update() = 0;
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void clean() { WeaponMount.erase(WeaponMount.begin(), WeaponMount.end()); }    
    
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
    
    bool isVisible() { return visible; }
    
    int getNumOfMounts() { return maxWeaponMounts; }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
    int bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }
    
    int getTotalNumOfBullets() { 
      int totalBullets = 0; 
      for(int i = 0; i < maxWeaponMounts; ++i) { 
        totalBullets += WeaponMount[i]->getNumBullets(); 
      }
      return totalBullets;
    }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }   
    float getMountX(int index) { return WeaponMount[index]->getX(); }
    float getMountY(int index) { return WeaponMount[index]->getY(); }
    float getMountWidth(int index) { return WeaponMount[index]->getWidth(); }
    float getMountHeight(int index) { return WeaponMount[index]->getHeight(); }  
    float getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
    float getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }

  protected:
    bool visible;
    
    int health;
    int maxWeaponMounts;  
   
    float x, y, width, height, speed;

    GLuint Texture;
    std::vector<Mount*> WeaponMount;
  
};

#endif
