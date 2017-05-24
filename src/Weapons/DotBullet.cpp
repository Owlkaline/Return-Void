#include "../../include/Weapons/DotBullet.h"

DotBullet::DotBullet() {
  this->immortal = false;
  this->active = true;
}

void DotBullet::draw(GraphicsHandler *graphics) { 
 /* glPushMatrix();
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
  glPopMatrix();*/
  
  graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), angle, "DotBullet");
}

void DotBullet::reset() {

}

void DotBullet::clean() {

}

void DotBullet::tick(float deltaTime) {
  y+=(speed*deltaTime)*directionY;
  x+=(speed*deltaTime)*directionX;
}

void DotBullet::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 12;
  height = 64;
  speed = 12;
  damage = 0.5;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

