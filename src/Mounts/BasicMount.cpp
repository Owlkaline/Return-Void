#include "../../include/Mounts/BasicMount.h"

BasicMount::BasicMount() {
  ticks=0;
}

void BasicMount::draw() {
  for(unsigned int i = 0; i < bullets.size(); ++i)
    bullets[i]->draw();
      
  if(visible) {
    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);  
    if(currentTexture == 1) {
      glBindTexture(GL_TEXTURE_2D, getBasicMountBrightTexture());
    } else {
      glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
    }
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
} 

void BasicMount::reset() {

}

void BasicMount::setup() { 
  setup(BLUEPLASMA);
}

void BasicMount::setup(int variant) { 
  ticks = 0;
  angle = 0;
  width = 8;
  height = 64;
  health = 10;
  visible = true;
  currentTexture = 0;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  this->variant = variant;
  switch (variant) {
    case BLUEPLASMA:
      timer = 7;
      break;
    case REDPLASMA:
      timer = 20;
      break;
  }
} 

void BasicMount::update(float x, float y, float directionX, float directionY, float angle) {  
  if(currentTexture == 1)
    currentTexture = 0;
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  dirX = directionX;
  dirY = directionY;
  
  tick();
    
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void BasicMount::addBullet() {
  switch(variant) {
    case BLUEPLASMA:
      bullets.push_back(new BluePlasma);
      break;
    case REDPLASMA:
      bullets.push_back(new RedPlasma);
      break;
  }
}

