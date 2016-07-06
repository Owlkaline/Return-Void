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

void PurplePlasma::update() {
  if(visible) {
    y+=speed*directionY;
    x+=speed*directionX;
  }
  if(y > SPACE_Y_RESOLUTION || y < 0 || x < 0 || x > SPACE_X_RESOLUTION)
    visible = false;
}

void PurplePlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 28;
  height = 28;
  speed = 15;
  damage = 0.5;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

