#ifndef MOUNT
#define MOUNT

#include <vector>
#include <math.h>

#include "../Weapons/Spiral.h"
#include "../Weapons/RedPlasma.h"
#include "../Weapons/BluePlasma.h"
#include "../Weapons/GreenPlasma.h"
#include "../Weapons/PurplePlasma.h"
#include "../Weapons/AlphaOnePlasma.h"
#include "../Namespaces/LoadTexture.h"

class Mount {
  public:
    virtual void setTexture() = 0;
    virtual void defaults() = 0;
    virtual void reset() = 0;
    //virtual void setup(int variant) = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle, bool isShooting) = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) = 0;

    void takeDamage(float damage) { health -= damage; if(!tookDamage) { tookDamage = true; } if(health <= 0) { visible = false; } }
    void setVisible(bool visible) { this->visible = visible; }
    void tick(bool isShooting) {
                  damageTicks++; if(damageTicks > damageTimer) { tookDamage = false; damageTicks = 0; }
                  if(isShooting)
                    bulletTicks++; if(bulletTicks > bulletTimer) { fire(); bulletTicks = 0; }
                  if(x < 0)
                    visible = false;
                }
    void clean() { bullets.clear();  bullets.erase(bullets.begin(), bullets.end()); bulletTicks = 0;};
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }

    void draw() {
      for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();

      if(visible) {
        glPushMatrix();
        glTranslatef(x, y, 0); // M1 - 2nd translation
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-x, -y, 0); // M1 - 2nd translation

        glEnable(GL_TEXTURE_2D);
        setTexture();
        if(!isLeft) {
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
        } else {
          glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x-width/2, y+height/2, 0.0);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x+width/2, y+height/2, 0.0);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x+width/2, y-height/2, 0.0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x-width/2, y-height/2, 0.0);
          glEnd();
        }
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      }
    }

    void setup(int variant) {
      bulletTicks = 0;
      damageTicks = 0;
      angle = 0;
      isLeft = false;
      visible = true;
      tookDamage = false;
      currentTexture = 0;
      x = -SPACE_X_RESOLUTION;
      y = -SPACE_Y_RESOLUTION;
      this->variant = variant;
      defaults();
      damageTimer = DAMAGETIMER;
      switch (variant) {
        case BLUEPLASMA:
          bulletTimer = BLUEPLASMATIMER;
          break;
        case REDPLASMA:
          bulletTimer = REDPLASMATIMER;
          break;
        case PURPLEPLASMA:
          bulletTimer = PURPLEPLASMATIMER;
          break;
        case GREENPLASMA:
          bulletTimer = GREENPLASMATIMER;
          break;
        case SPIRAL:
          bulletTimer = SPIRALTIMER;
          break;
        case ALPHAONEPLASMA:
          bulletTimer = ALPHAONETIMER;
          break;
        default:
          printf("Error: unknown varient in mount setup: %d\n",variant);
          exit(0);
      }
    }

    void fire() {
      if(visible) {
        currentTexture = 1;
        addBullet();
        unsigned int i = bullets.size()-1;
        bullets[i]->setup(x, y, dirX, dirY, angle);
        bullets[i]->setVisible(true);
      }
    }

    void setIsBoss() { isBoss = true; }

    void isLeftMount() { isLeft = true; }

    bool isVisible() { return visible; }

    int getNumBullets() { return bullets.size(); }
    float bulletHit(int index) { return bullets[index]->hit(); }

    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getBulletX(int index) { return bullets[index]->getX(); }
    float getBulletY(int index) { return bullets[index]->getY(); }
    float getBulletWidth(int index) { return bullets[index]->getWidth(); }
    float getBulletHeight(int index) { return bullets[index]->getHeight(); }

  protected:
    void addBullet() {
      switch(variant) {
        case GREENPLASMA:
          bullets.push_back(new GreenPlasma);
          break;
        case BLUEPLASMA:
          bullets.push_back(new BluePlasma);
          break;
        case REDPLASMA:
          bullets.push_back(new RedPlasma);
          break;
        case PURPLEPLASMA:
          bullets.push_back(new PurplePlasma);
          break;
        case SPIRAL:
          bullets.push_back(new Spiral);
          break;
        case ALPHAONEPLASMA:
          bullets.push_back(new AlphaOnePlasma);
          if(isBoss) {
            int size = bullets.size() - 1;
            bullets[size]->setIsBoss(true);
          }
          break;
        default:
          printf("Error: unknown varient in mounts add bullet: %d\n",variant);
          exit(0);
      }
    }

    bool isBoss;
    int isLeft;
    float health;
    float angle;
    int variant;
    bool visible;
    bool tookDamage;
    int maxMounts;
    float fireRate;
    int bulletTicks, bulletTimer, damageTicks, damageTimer;
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

    static GLuint getAlphaOneMountTexture() {
      static GLuint alphaOneMountTexture = txt::LoadTexture("Textures/Game/Weapons/AlphaOneMount.png");
      return alphaOneMountTexture;
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
