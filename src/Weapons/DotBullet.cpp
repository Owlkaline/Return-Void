#include "../../include/Weapons/DotBullet.h"

DotBullet::DotBullet() {

}

void DotBullet::draw() { 
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, getDotBulletTexture());
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

void DotBullet::reset() {

}

void DotBullet::clean() {

}

void DotBullet::tick() {
  y+=speed*directionY;
  x+=speed*directionX;
}

void DotBullet::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 12;
  height = 64;
  speed = 12;
  damage = 1;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

