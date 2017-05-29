#ifndef SHIP_H
#define SHIP_H

#include <math.h>

#include "../defines.h"

#include "../Mounts/TriangleMount.h"
#include "../Mounts/MountType1.h"
#include "../Mounts/MountType2.h"
#include "../Mounts/MountType3.h"

#include "../GraphicsHandler.h"

class Ship {
  public:    
    virtual std::string getTexture()=0;
    virtual void defaults(){}
    virtual void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState)=0; 
    virtual void specialDraw(GraphicsHandler *graphics) {
      int sSize = 32;
      for(int i = 0; i < specialsLeft; ++i) {
      graphics->drawObject(glm::vec2(40 + i*50, 40), glm::vec2(sSize, sSize), "Boost");
    }
  }
    
    void clean() { WeaponMount.clear();  WeaponMount.erase(WeaponMount.begin(), WeaponMount.end()); }
    
    void setY(float y) { this->y = y; }
    void setX(float x) { this->x = x; for(unsigned int i = 0; i < WeaponMount.size(); ++i) { WeaponMount[i]->setX(x); }}    
    void setVisible(bool visible) { this->visible = visible; for(unsigned int i = 0; i < WeaponMount.size(); ++i) { WeaponMount[0]->setVisible(visible); } }
    
 
    int getCoins() { return coins; }
    int getNumOfMounts() { return WeaponMount.size(); }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }

    bool getVisible() { return visible; }

    float bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }

    float getX() { return x; }
    float getY() { return y; }   
    float getWidth() { return width; }
    float getHeight() { return height; }   
    float getDirectionX() { return directionX; }
    float getDirectionY() { return directionY; }    
    float getDistanceFromCursor() { return distanceFromCursor; }

    float getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
    float getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
    float getBulletDirectionX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletDirectionX(bIndex); }
    float getBulletDirectionY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletDirectionY(bIndex); }
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }
    
    void draw(GraphicsHandler *graphics) {
      if(visible) {
        specialDraw(graphics);
        //glPushMatrix();
        if(tookDamage) {
        //  tick-=1*deltaTime;
          if(tick <= 0)
            tookDamage = false;
        }      
        graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), angle, getTexture());
      }
      
      for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
        WeaponMount[i]->draw(graphics); 
       
      if(shield > 0)
        drawShield(graphics);
    }
    
    void VisualSetup(float x, float y) {
      defaults();
      crntTexture = 0;
      this->x = x;
      this->y = y;
      shield = 0;
      specialsLeft = 0;
      visible = true;
      tookDamage = false;
      
      for(unsigned int i = 0; i < WeaponMount.size(); ++i)
        WeaponMount[i]->update(x, y, 1, 0, 0, 0, false);  
        
      angle = 0;
    }
    
    void fire(float x, float y, float deltaTime, float directionX, float directionY, float angle, unsigned int* mouseBtnState) {
    for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
      WeaponMount[i]->update(x, y, deltaTime, directionX, directionY, angle, mouseBtnState[0]);
    }
    
    void animate() {
      crntTexture++;
      if(crntTexture > 2)
        crntTexture = 0;
    }
    
    void collect(int powerup) {
      switch(powerup) {
        case NOTHING:
        break;
      case COIN:
        coins+=10;
        break;
      case HEALTH:
        health += 5;
        crntHealth = health; 
        if(health >= maxHealth) {
          health = maxHealth;
          crntHealth = maxHealth;
        }
        break;
      case SHIELD:
        shield += 5;
        if(shield >= maxShield)
          shield = maxShield;
        break;
      }
    }
        
    void takeDamage(float damage) {
      if(shield <= 0) {
        health -= damage;   
        if(tookDamage == false && shieldDamaged == false) {
          tick = 5;
          tookDamage = true;
        }
      } else {
        shield -= damage;
        if(shield < 0) {
          health += shield;
          shield = 0;
        } 
        if(shieldDamaged == false && tookDamage == false) {
          tick = 25;
          shieldDamaged = true;
        }
      }
  
      if(health <= 0) {
        crntHealth = 0;
        visible = false;
        for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
          WeaponMount[i]->setVisible(false);
        }
      }
    }
    
    void drawHealthBar(GraphicsHandler *graphics) {

      float hy = SPACE_Y_RESOLUTION - 35;    
      float hw = 500;
      float hh = 50;
      float hx = SPACE_X_RESOLUTION/2;
      /*glEnable(GL_TEXTURE_2D);
  
      glBindTexture(GL_TEXTURE_2D, healthBarTexture[0]);
  
      glColor4f(1.0, 1.0, 1.0, 0.5f);
      drawQuad(hx, -hw, hy, hh, UP);*/
      graphics->drawObject(glm::vec2(hx, hy), glm::vec2(hw, hh), "HealthBarBase");
  
      hw = hw/maxShield * shield;
      hx = SPACE_X_RESOLUTION/2;
  
      //Shield Bar
//      glBindTexture(GL_TEXTURE_2D, healthBarTexture[2]);
  //    drawQuad(hx, -hw, hy, hh, UP);
      graphics->drawObject(glm::vec2(hx, hy), glm::vec2(hw, hh), "ShieldBar");
    
      hw = 500/(float)maxHealth * crntHealth;
      hx = SPACE_X_RESOLUTION/2;
      //Health bar
//      glBindTexture(GL_TEXTURE_2D, healthBarTexture[1]);
  //    drawQuad(hx, -hw, hy, hh, UP);
      graphics->drawObject(glm::vec2(hx, hy), glm::vec2(hw, hh), "HealthBar");
   
//      glDisable(GL_TEXTURE_2D);
//      glColor4f(1.0, 1.0, 1.0, 1.0);
    }
    
    void drawShield(GraphicsHandler *graphics) {  
      std::string name = "Shield";
      if(shieldDamaged) {
        if(tick > 20) {
          //glBindTexture(GL_TEXTURE_2D, shieldTexture[1]); 
          name = "ShieldRipple1";
        } else if(tick > 15) {
          //glBindTexture(GL_TEXTURE_2D, shieldTexture[2]);
          name = "ShieldRipple2";
        } else if(tick > 10) {
          //glBindTexture(GL_TEXTURE_2D, shieldTexture[3]);
          name = "ShieldRipple3";
        } else if(tick > 5) {
          //glBindTexture(GL_TEXTURE_2D, shieldTexture[4]);
          name = "ShieldRipple4";
        } else {
          //glBindTexture(GL_TEXTURE_2D, shieldTexture[5]);
          name = "ShieldRipple5";
        }    
       // tick-=1*deltaTime;
        if(tick <= 0)
          shieldDamaged = false;
      } 
      
      graphics->drawObject(glm::vec2(x, y), glm::vec2(width*1.3, height*1.3), angle, 0.5f, name);
    }
    
  protected:      
    
    virtual void special() {  }
    
    int coins;    
    int maxShield;
    int maxHealth;     
    int extraSpeed;
    int crntTexture;
    int specialsLeft;
    int maxNumWeapons;
    int health, crntHealth;
    
    float tick;  
    float x, y;
    float speed;
    float angle;
    float shield;
    float specialTimer;
    float width, height;
    float directionX, directionY, distanceFromCursor;
    
    bool onCooldown;
    bool specialActive;
    bool visible, tookDamage, shieldDamaged;
    
    GLuint textures[10];
    GLuint shieldTexture[6];
    GLuint healthBarTexture[3];
    GLuint specialIcon;
    std::vector<Mount*> WeaponMount;
};

#endif
