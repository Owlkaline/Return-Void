#include "../include/BluePlasma.h"

BluePlasma::BluePlasma() {

}

void BluePlasma::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 4;
  height = 32;
  speed = 25;
  damage = 1;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
  Texture = txt::LoadTexture("Textures/Game/Weapons/BluePlasma.png");
} 

void BluePlasma::update() {
  if(visible) {
    y+=speed*directionY;
    x+=speed*directionX;
  }
  if(y > SPACE_Y_RESOLUTION || y < 0 || x < 0 || x > SPACE_X_RESOLUTION)
    visible = false;

}

void BluePlasma::draw() {
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
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

void BluePlasma::reset() {

}

void BluePlasma::clean() {

}
