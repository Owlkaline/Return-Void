#include "../../include/Weapons/RedPlasma.h"

RedPlasma::RedPlasma() {

}

void RedPlasma::draw() {
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, getRedPlasmaTexture());
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

void RedPlasma::reset() {

}

void RedPlasma::clean() {

} 

void RedPlasma::tick() {
  y+=speed*directionY;
  x+=speed*directionX;
} 

void RedPlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 12;
  height = 12;
  speed = 15;
  damage = 2;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

