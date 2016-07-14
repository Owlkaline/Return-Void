#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <math.h>

#include "../defines.h"
#include "../Menus/Label.h"
#include "../Mounts/BasicMount.h"
#include "../Mounts/HypnoMount.h"
#include "../Namespaces/Movement.h"
#include "../Namespaces/LoadTexture.h"

class Enemy {
  public:

    virtual void reset() = 0;
    virtual void defaults() = 0;
    virtual void update(float Px, float Py) = 0;

    virtual void setX(float x) { this->x = x; }
    virtual void setY(float y) { this->y = y; }

    void setup(float x, float y, int moveType, int drop) {
      defaults();
      this->x = x;
      this->y = y;
      this->drop = drop;
      this->moveType = moveType;

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
            isOnRightSide = false;
          } else {
            startX = x + amp;
            isOnRightSide = true;
            angle = 0;
          }
          break;
        case RIGHTSIDEFALL:
          movementAngle = 0;
          x = SPACE_X_RESOLUTION - width/2;
          startX = x;
          break;
      }
      movementAngle = 0;
    }

    void draw() {
      for(int i = 0; i < maxWeaponMounts; ++i)
        WeaponMount[i]->draw();

      if(visible) {
        if(tookDamage) {
          if(tick <= 0)
            tookDamage = false;
        }

        glEnable(GL_TEXTURE_2D);
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

        glColor3f(1.0, 1.0, 1.0);
      } else {
        lbScore.setX(x);
        lbScore.setY(y);
        lbScore.draw();
      }
    }

    void clean() { WeaponMount.clear(); WeaponMount.erase(WeaponMount.begin(), WeaponMount.end()); }

    void takeDamage(float damage) {
      health -= damage;
      if(tookDamage == false) {
        tick = 5;
        tookDamage = true;
      }
      if(health <= 0) {
        if(visible) {
          lbScore.setTimer(1);
          wasKilled = true;
        }
        setVisible(false);
      }
    }

    void setVisible(bool visible) {
      this->visible = visible;
      for(int i = 0; i < maxWeaponMounts; ++i)
        WeaponMount[i]->setVisible(visible);
    }

    bool getWaskilled() { return wasKilled; }
    bool isVisible() { return visible; }
    bool timerExpired() { return lbScore.timeExpired(); }

    int dropPowerup() { return drop; }
    int getScore() { wasKilled = false; return score; }
    int getNumOfMounts() { return maxWeaponMounts; }
    int getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
    float bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }

    int getTotalNumOfBullets() {
      int totalBullets = 0;
      for(int i = 0; i < maxWeaponMounts; ++i)
        totalBullets += WeaponMount[i]->getNumBullets();
      return totalBullets;
    }

    float getX() { return this->x; }
    float getY() { return this->y; }
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

    virtual void setTexture() = 0;

    void move() {
      if(visible) {
        switch(moveType) {
          case FALL:
            move::fall(&y, speed, &movementAngle, &visible);//y-=speed;
            break;
          case SEMICIRCLE: {
            int numOfBullets = 0;
            for(int i = 0; i < maxWeaponMounts; ++i)
              numOfBullets += getNumOfBullets(i);
            move::semicircle(&x, &y, width, height, speed, startX, &startY, &movementAngle, &isOnRightSide, &cycle, &visible, numOfBullets);
            break;
            }
          case SINWAVE:
            move::sinwave(&x, &y, &movementAngle, height, speed, amp, startX, &visible);
            break;
          case RIGHTSIDEFALL:
            move::sidefall(&x, &y, width, &startX, &startY, speed, &movementAngle, &cycle);
            angle = -movementAngle;
            break;
        }
      }
    }

    bool visible;
    bool wasKilled;
    bool tookDamage;

    int tick;
    int drop;
    int score;
    int cycle;
    float angle;
    float health;
    int maxHealth;
    int moveType;
    int maxWeaponMounts;

    float transparent;
    float movementAngle;
    bool hasFinished, isOnRightSide;
    float startX, startY, amp;
    float x, y, width, height, speed;

    Label lbScore;

    std::vector<Mount*> WeaponMount;

    static GLuint getBasicEnemyTexture() {
      static GLuint basicEnemyTexture = txt::LoadTexture("Textures/Game/Enemies/BasicEnemy.png");
      return basicEnemyTexture;
    }

    static GLuint getHypnoEnemyTexture() {
      static GLuint hypnoEnemyTexture = txt::LoadTexture("Textures/Game/Enemies/HypnoEnemy.png");
      return hypnoEnemyTexture;
    }

    static GLuint getCorruptedStarShipTexture(int i) {
      static GLuint corruptedStarShipTexture0 = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShip.png");
      static GLuint corruptedStarShipTexture1 = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShipDmg1.png");
      static GLuint corruptedStarShipTexture2 = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShipDmg2.png");
      static GLuint corruptedStarShipTexture3 = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShipDmg3.png");
      static GLuint corruptedStarShipTexture4 = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShipDmg4.png");

      switch(i) {
        case 0:
          return corruptedStarShipTexture0;
          break;
        case 1:
          return corruptedStarShipTexture1;
          break;
        case 2:
          return corruptedStarShipTexture2;
          break;
        case 3:
          return corruptedStarShipTexture3;
          break;
        case 4:
          return corruptedStarShipTexture4;
          break;
      }
      return 0;
    }
};

#endif
