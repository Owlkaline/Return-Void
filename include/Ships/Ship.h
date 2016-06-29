#ifndef SHIP_H
#define SHIP_H

#include <math.h>

#include "../defines.h"
#include "../Mounts/BasicMount.h"
#include "../Mounts/TriangleMount.h"
#include "../Mounts/PurpleMount.h"
#include "../Namespaces/LoadTexture.h"

class Ship {
  public:    
    virtual void draw()=0;
    virtual void setup()=0;
    virtual void clean()=0;
    virtual void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState)=0; 
 
    int getCoins() { return coins; }

    bool getVisible() { return visible; }

    int getNumOfMounts() { return WeaponMount.size(); }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
    int bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }
 
    float getX() { return x; }
    float getY() { return y; }   
    float getWidth() { return width; }
    float getHeight() { return height; }   
    float getDirectionX() { return directionX; }
    float getDirectionY() { return directionY; }    
    float getDistanceFromCursor() { return distanceFromCursor; }

    float getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
    float getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }
    void boost() { hasBoost = true; boostTimer = 100; extraSpeed = 3; }
    
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
    
        
    void takeDamage(int damage) {
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
        visible = false;
        for(int i = 0; i < maxNumWeapons; ++i) {
          WeaponMount[i]->setVisible(false);
        }
      }
    }
    
    void drawHealthBar() {

      float hy = SPACE_Y_RESOLUTION - 10;    
      float hw = 500;
      float hh = 50;
      float hx = SPACE_X_RESOLUTION/2 - hw/2;
      glEnable(GL_TEXTURE_2D);
  
      glBindTexture(GL_TEXTURE_2D, healthBarTexture[0]);
  
      glColor4f(1.0, 1.0, 1.0, 0.5f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(hx, hy, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(hx+hw, hy, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(hx+hw, hy-hh, 0.0);
        glTexCoord2f(0.0f, 0.0f);
      glVertex3f(hx, hy-hh, 0.0);
      glEnd();
  
      hw = hw/maxShield * shield;
      hx = SPACE_X_RESOLUTION/2 - hw/2;
  
      //Shield Bar
      glBindTexture(GL_TEXTURE_2D, healthBarTexture[2]);
  
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(hx, hy, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(hx+hw, hy, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(hx+hw, hy-hh, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(hx, hy-hh, 0.0);
      glEnd(); 
  
      hw = 500;
      hx = SPACE_X_RESOLUTION/2 - hw/2;
    
      hw = hw/maxHealth * crntHealth;
      hx = SPACE_X_RESOLUTION/2 - hw/2;
      //Health bar
      glBindTexture(GL_TEXTURE_2D, healthBarTexture[1]);
  
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(hx, hy, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(hx+hw, hy, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(hx+hw, hy-hh, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(hx, hy-hh, 0.0);
      glEnd();
   
      glDisable(GL_TEXTURE_2D);
      glColor4f(1.0, 1.0, 1.0, 1.0);
    }
    
    void drawShield() {
      glPushMatrix();

      glTranslatef(x, y, 0); // M1 - 2nd translation
      glRotatef(angle, 0.0f, 0.0f, 1.0f);  
      glTranslatef(-x, -y, 0); // M1 - 2nd translation
  
      glEnable(GL_TEXTURE_2D);
      glColor4f(1.0, 1.0, 1.0, 0.5);
  
  
      if(shieldDamaged) {
        if(tick > 20) {
          glBindTexture(GL_TEXTURE_2D, shieldTexture[1]); 
        } else if(tick > 15) {
          glBindTexture(GL_TEXTURE_2D, shieldTexture[2]);
        } else if(tick > 10) {
          glBindTexture(GL_TEXTURE_2D, shieldTexture[3]);
        } else if(tick > 5) {
          glBindTexture(GL_TEXTURE_2D, shieldTexture[4]);
        } else {
          glBindTexture(GL_TEXTURE_2D, shieldTexture[5]);
        }
    
        tick--;
        if(tick <= 0)
          shieldDamaged = false;
        // glColor3f(0.0, 0.0, 0.3);
      } else {
        glBindTexture(GL_TEXTURE_2D, shieldTexture[0]);
      }
  
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x-width*0.7, y+height*0.7, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width*0.7, y+height*0.7, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width*0.7, y-height*0.7, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x-width*0.7, y-height*0.7, 0.0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();  
      glColor4f(1.0, 1.0, 1.0, 1.0);     
    }
    
  protected:      
    int tick;  
    int coins;    
    int boostTimer;  
    int extraSpeed;
    int crntTexture;
    int maxNumWeapons;
    int shield, maxShield;
    int health, maxHealth, crntHealth;
    float x, y;
    float speed;
    float angle;
    bool hasBoost;
    bool visible, tookDamage, shieldDamaged;
    float width, height;
    float directionX, directionY, distanceFromCursor;
  
    GLuint textures[3];
    GLuint shieldTexture[6];
    GLuint healthBarTexture[3];
    std::vector<Mount*> WeaponMount;
};

#endif
