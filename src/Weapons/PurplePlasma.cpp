#include "../../include/Weapons/PurplePlasma.h"

PurplePlasma::PurplePlasma() {

}

void PurplePlasma::draw() {
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, getPurplePlasmaTexture());
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

void PurplePlasma::reset() {

}

void PurplePlasma::clean() {

}

void PurplePlasma::tick(float deltaTime) {
  y+=(speed*deltaTime)*directionY;
  x+=(speed*deltaTime)*directionX;
}

void PurplePlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 20;
  height = 20;
  speed = 15;
  damage = 1;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
}

