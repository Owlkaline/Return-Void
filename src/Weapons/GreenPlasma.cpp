#include "../../include/Weapons/GreenPlasma.h"

GreenPlasma::GreenPlasma() {

}

void GreenPlasma::draw() {
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, getGreenPlasmaTexture());
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

void GreenPlasma::reset() {

}

void GreenPlasma::clean() {

}

void GreenPlasma::tick(float deltaTime) {
  y+=(speed*deltaTime)*directionY;
  x+=(speed*deltaTime)*directionX;
}

void GreenPlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 24;
  height = 64;
  speed = 12;
  damage = 2;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

