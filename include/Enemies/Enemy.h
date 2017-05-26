#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include <math.h>

#include "../defines.h"

#include "../Menus/Label.h"
#include "../Mounts/DotMount.h"
#include "../Mounts/BasicMount.h"
#include "../Mounts/HypnoMount.h"
#include "../Mounts/AlphaOneMount.h"
#include "../Mounts/MountType1.h"

#include "../Namespaces/Movement.h"
#include "../Namespaces/LoadTexture.h"

class Enemy {
  public:
    virtual void reset() = 0;
    virtual void defaults() {};
    virtual void update(float Px, float Py, float deltaTime) = 0;

    virtual void setX(float x) { this->x = x; }
    virtual void setY(float y) { this->y = y; }
    
    void setHealth(float health) { this->health = health; maxHealth = health; }
    void setMountHealth(int i, float health) { WeaponMount[i]->setHealth(health); }
    
    void mountTakeDamage(int mount, float damage) { WeaponMount[mount]->takeDamage(damage); }
    void clean() { WeaponMount.clear(); WeaponMount.erase(WeaponMount.begin(), WeaponMount.end()); }
    
    int dropPowerup() { return drop; }
    
    bool isVisible() { return visible; }
    
    float bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }
        
    int getNumOfMounts() { return WeaponMount.size(); }
    int getScore() { wasKilled = false; return score; }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
    
    bool getIsBoss() { return isBoss; }    
    bool getWaskilled() { return wasKilled; }     
    bool getMountVisible(int index) { return WeaponMount[index]->getVisible(); }
        
    float getX() { return this->x; }
    float getY() { return this->y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getHealth() { return health; }
    float getMountX(int index) { return WeaponMount[index]->getX(); }
    float getMountY(int index) { return WeaponMount[index]->getY(); }
    float getMountHealth(int i) { return WeaponMount[i]->getHealth(); }
    float getMountWidth(int index) { return WeaponMount[index]->getWidth(); }
    float getMountHeight(int index) { return WeaponMount[index]->getHeight(); }
    float getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
    float getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
    float getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
    float getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }

    void setup(float x, float y, int moveType, int drop) {
      
      this->x = x;
      this->y = y;
      this->drop = drop;
      this->moveType = moveType;
      defaults();
      tick = 0;
      cycle = 0;

      visible = true;
      wasKilled = false;
      tookDamage = false;
      hasFinished = false;

      startX = x;
      startY = y;
      maxHealth = health;

      switch(moveType) {
        case FALL:
          break;
        case SINWAVE:
          startX = x;
          if(x < width*5) {
            amp = (x-width)/2;//startX-width/2;
          } else if(SPACE_X_RESOLUTION - x < width*5) {
            amp = (SPACE_X_RESOLUTION - x - width)/2;
          } else {
            amp = width/2*5;
          }
          break;
        case SEMICIRCLE:
          if(x < width*5) {
            amp = (x-width)/2;//startX-width/2;
          } else if(SPACE_X_RESOLUTION - x < width*5) {
            amp = (SPACE_X_RESOLUTION - x - width)/2;
          } else {
            amp = width/2*5;
          }
          if(x > SPACE_X_RESOLUTION/2) {
            startX = x - amp;
            isOnRightSide = true;
          } else {
            startX = x + amp;
            isOnRightSide = false;
            angle = 0;
          }
          break;
        case RIGHTSIDEFALL:
          movementAngle = 0;
          x = SPACE_X_RESOLUTION - width/2;
          startX = x;
          break;
        case ALPHAONE:
          movementAngle = 0;
          break;
        default:
          printf("Unkown enemy movement type: %d\n", moveType);
          exit(0);
          break;
      }
      movementAngle = 0;
    }

    void draw(GraphicsHandler *graphics) {
      for(unsigned int i = 0; i < WeaponMount.size(); ++i)
        WeaponMount[i]->draw(graphics);

      if(visible) {
        if(tookDamage) {
          if(tick <= 0)
            tookDamage = false;
        }
       graphics->drawObject(glm::vec2(x,y), glm::vec2(width, height), angle, getTexture());
        /*glEnable(GL_TEXTURE_2D);
        setTexture();
        glPushMatrix();
        glTranslatef(x, y, 0); // M1 - 2nd translation
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-x, -y, 0); // M1 - 2nd translation

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

        glColor3f(1.0, 1.0, 1.0);*/
      }
    }

    void takeDamage(float damage) {
      health -= damage;
      if(tookDamage == false) {
        tick = 5;
        tookDamage = true;
      }
      if(health <= 0) {
        if(visible) {
          wasKilled = true;
        }
        setVisible(false);
      }
    }
    
    bool checkMountsVisible() { 
      for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
        if(WeaponMount[i]->getVisible())
          return false;
      }
      return true;
    }
    
    void setVisible(bool visible) {
      this->visible = visible;
      for(unsigned int i = 0; i < WeaponMount.size(); ++i)
        WeaponMount[i]->setVisible(visible);
    }

    int getTotalNumOfBullets() {
      int totalBullets = 0;
      for(unsigned int i = 0; i < WeaponMount.size(); ++i)
        totalBullets += WeaponMount[i]->getNumBullets();
      return totalBullets;
    }
  protected:
    virtual std::string getTexture() = 0;

    void move(float deltaTime) {
      if(visible) {
        switch(moveType) {
          case FALL:
            move::fall(&y, speed*deltaTime, &movementAngle, &visible);//y-=speed;
            break;
          case SEMICIRCLE: {
            int numOfBullets = 0;
            for(unsigned int i = 0; i < WeaponMount.size(); ++i)
              numOfBullets += getNumOfBullets(i);
            move::semicircle(&x, &y, width, height, speed*deltaTime, startX, &startY, &movementAngle, &isOnRightSide, &cycle, &visible, numOfBullets);
            break;
            }
          case SINWAVE:
            move::sinwave(&x, &y, &movementAngle, height, speed*deltaTime, amp, startX, &visible);
            break;
          case RIGHTSIDEFALL:
            move::sidefall(&x, &y, width, height, &startX, &startY, speed*deltaTime, &movementAngle, &cycle, &visible);
            angle = -movementAngle;
            break;
          case ALPHAONE:
            move::AlphaOne(&x, &y, width, height, speed*deltaTime, &cycle);
            break;
          default:
            printf("Unkown Enemy Movement variant: %d\n", moveType);
            exit(0);
            break;
        }
      }
    }

    bool isBoss;
    bool visible;
    bool wasKilled;
    bool tookDamage;
    bool hasFinished, isOnRightSide;

    int tick;
    int drop;
    int score;
    int cycle;    
    int moveType;
    int maxHealth;
    int maxWeaponMounts;
    
    float angle;
    float health;
    float transparent;
    float movementAngle;    
    float startX, startY, amp;
    float x, y, width, height, speed;

    std::vector<Mount*> WeaponMount;
};

#endif
