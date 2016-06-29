#include "../../include/Mounts/PurpleMount.h"

PurpleMount::PurpleMount() {
  ticks=0;
}

void PurpleMount::draw() {
  for(unsigned int i = 0; i < bullets.size(); ++i)
    bullets[i]->draw();
      
  if(visible) {
    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation

    glEnable(GL_TEXTURE_2D);  
    /*if(currentTexture == 1) {
      glBindTexture(GL_TEXTURE_2D, getPurpleMountBrightTexture());
    } else {
      glBindTexture(GL_TEXTURE_2D, getPurpleMountTexture());
    }*/
    glBindTexture(GL_TEXTURE_2D, getPurpleMountTexture());
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

void PurpleMount::reset() {

}

void PurpleMount::setup() { 
  setup(PURPLEPLASMA);
}

void PurpleMount::setup(int variant) { 
  ticks = 0;
  angle = 0;
  width = 32;
  height = 32;
  health = 10;
  visible = true;
  currentTexture = 0;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  this->variant = variant;
  switch (variant) {
    case BLUEPLASMA:
      timer = BLUEPLASMATIMER;
      break;
    case REDPLASMA:
      timer = REDPLASMATIMER;
      break;
    case PURPLEPLASMA:
      timer = PURPLEPLASMATIMER;
      break;
  }
} 

void PurpleMount::update(float x, float y, float directionX, float directionY, float angle) {  
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

void PurpleMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle);
}

void PurpleMount::addBullet() {
  switch(variant) {
    case BLUEPLASMA:
      bullets.push_back(new BluePlasma);
      break;
    case REDPLASMA:
      bullets.push_back(new RedPlasma);
      break;
    case PURPLEPLASMA:
      bullets.push_back(new PurplePlasma);
      break;
  }
}

