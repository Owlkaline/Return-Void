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
    virtual void setTexture()=0;
    virtual void defaults()=0;
    virtual void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState)=0; 
    
    void boost() { hasBoost = true; boostTimer = 100; extraSpeed = 3; }
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
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }    
 
    void setup() {    
      maxNumWeapons = 0;
      defaults();
      x = SPACE_X_RESOLUTION/2;
      y = 100;
  
      coins = 0;
      angle = 0;
  
      extraSpeed = 0;
      maxShield = shield;
      maxHealth = health;
      crntHealth = health;
  
      hasBoost = false;
      visible = true;
      tookDamage = false;
      shieldDamaged = false;
      directionX = 1;
      directionY = 1; 
  
      crntTexture = 0;
  
      healthBarTexture[0] = txt::LoadTexture("Textures/Game/Misc/HealthBarBase.png");
      healthBarTexture[1] = txt::LoadTexture("Textures/Game/Misc/HealthBar.png");
      healthBarTexture[2] = txt::LoadTexture("Textures/Game/Misc/ShieldBar.png");
  
      shieldTexture[0] = txt::LoadTexture("Textures/Game/Ships/Shield.png");
      shieldTexture[1] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple1.png");
      shieldTexture[2] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple2.png");
      shieldTexture[3] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple3.png");
      shieldTexture[4] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple4.png");
      shieldTexture[5] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple5.png");
    }
 
    void draw() {
      if(visible) {
        glPushMatrix();
        if(tookDamage) {
          tick--;
          if(tick <= 0)
            tookDamage = false;
        }      
        glTranslatef(x, y, 0); // M1 - 2nd translation
        glRotatef(angle, 0.0f, 0.0f, 1.0f);  
        glTranslatef(-x, -y, 0); // M1 - 2nd translation        
        
        glEnable(GL_TEXTURE_2D);
        setTexture();

        glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(x-width/2, y+height/2, 0.0);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(x+width/2, y+height/2, 0.0);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(x+width/2, y-height/2, 0.0);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(x-width/2, y-height/2, 0.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();  
        glColor4f(1.0, 1.0, 1.0, 1.0);      
      }
      
      for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
        WeaponMount[i]->draw(); 
       
      if(shield > 0)
        drawShield();
    }
    
    void VisualSetup(float x, float y) {
      defaults();
      crntTexture = 0;
      this->x = x;
      this->y = y;
      shield = 0;
      visible = true;
      tookDamage = false;
      
      for(unsigned int i = 0; i < WeaponMount.size(); ++i)
        WeaponMount[i]->update(x, y, 0, 0, 0, false);  
        
      angle = 0;          
    }
    
    void fire(float x, float y, float directionX, float directionY, float angle, unsigned int* mouseBtnState) {
    for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
      WeaponMount[i]->update(x, y, directionX, directionY, angle, mouseBtnState[0]);
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
    
      hw = hw/(float)maxHealth * crntHealth;
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
    int maxShield;
    int maxHealth;    
    int boostTimer;  
    int extraSpeed;
    int crntTexture;
    int maxNumWeapons;
    int health, crntHealth;
    
        
    float x, y;
    float speed;
    float angle;
    float shield;
    float width, height;
    float directionX, directionY, distanceFromCursor;
    
    bool hasBoost;
    bool visible, tookDamage, shieldDamaged;
    
    GLuint textures[3];
    GLuint shieldTexture[6];
    GLuint healthBarTexture[3];
    std::vector<Mount*> WeaponMount;
};

#endif
