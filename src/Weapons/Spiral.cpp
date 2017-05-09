#include "../../include/Weapons/Spiral.h"

Spiral::Spiral() {
  this->immortal = false;
  this->active = true;
}

void Spiral::draw() {
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, getSpiralTexture());
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

void Spiral::reset() {

}

void Spiral::clean() {

}

void Spiral::tick(float deltaTime) {
  y+=(speed*deltaTime)*directionY;
  x+=(speed*deltaTime)*directionX;
  angle+=10*deltaTime;
}

void Spiral::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 12;
  height = 32;
  speed = 7;
  damage = 3;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

