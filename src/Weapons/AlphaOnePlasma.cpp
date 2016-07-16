#include "../../include/Weapons/AlphaOnePlasma.h"

AlphaOnePlasma::AlphaOnePlasma() {

}

void AlphaOnePlasma::draw() { 
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, getAlphaOnePlasmaTexture());
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

void AlphaOnePlasma::reset() {

}

void AlphaOnePlasma::clean() {

}

void AlphaOnePlasma::tick() {
  if(isBoss) {
    if(y > SPACE_Y_RESOLUTION/2+height) {
      y-=speed;
    } else {
      visible = false;
    }
  } else {
    x += speed*directionX;
    y += speed*directionY;
  }
}

void AlphaOnePlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  if(isBoss) {
    width = 76;
    height = 76;
    offsetX = 0;
    offsetY = 76;
  } else {
    offsetX = 0;
    offsetY = 0;
    width = 32;
    height = 32;
  }
  speed = 12;
  damage = 1;
  y+=offsetY;
  x+=offsetX;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = true;
} 

