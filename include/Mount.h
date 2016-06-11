#ifndef MOUNT
#define MOUNT

#include <vector>
#include <math.h>

#include "./LoadTexture.h"
#include "./BluePlasma.h"
#include "./GreenPlasma.h"
#include "./RedPlasma.h"

class Mount {
  public:
    virtual void setup() = 0;
    virtual void setup(int variant) = 0;
    virtual void update(float x, float y, float directionX, float directionY, float angle) = 0;
    virtual void reset() = 0;
        void tick() { ticks++; if(ticks > timer) { fire(); ticks = 0; } }
        
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }

    void fire() { 
      if(visible) {
        addBullet();
        int i = bullets.size()-1;
        bullets[i]->setup(x, y, dirX, dirY, angle);
        bullets[i]->setVisible(true);
      }
    }
    
    void draw() {
      for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();
    
        glPushMatrix();
        glTranslatef(x, y, 0); // M1 - 2nd translation
        glRotatef(angle, 0.0f, 0.0f, 1.0f);  
        glTranslatef(-x, -y, 0); // M1 - 2nd translation
        glEnable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);  
        glBindTexture(GL_TEXTURE_2D, Texture);
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
    }
    void clean() {   bullets.erase(bullets.begin(), bullets.end()); ticks = 0;};
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    bool isVisible() { return visible; }
    
    int bulletHit(int index) { return bullets[index]->hit(); }
    int getNumBullets() { return bullets.size(); }
    float getBulletX(int index) { return bullets[index]->getX(); }
    float getBulletY(int index) { return bullets[index]->getY(); }
    float getBulletWidth(int index) { return bullets[index]->getWidth(); }
    float getBulletHeight(int index) { return bullets[index]->getHeight(); }
    
    void setVisible(bool visible) { this->visible = visible; }
    
    void takeDamage(int damage) { health -= damage; }
   
  protected:
    int health;
    int ticks, timer;
    float x,y, width, height;
    float dirX, dirY;
    float fireRate;
    float angle;
    float offsetX, offsetY;
    bool visible;
    GLuint Texture;
    std::vector<Weapon*> bullets;
    
    virtual void addBullet()=0;
};

#endif
