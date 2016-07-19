#include "../../include/Mounts/PurpleMount.h"

PurpleMount::PurpleMount() {
  visible = false;
  width = 32;
  height = 32;
}

PurpleMount::~PurpleMount() {
  clean();
}

void PurpleMount::setTexture() {
  glBindTexture(GL_TEXTURE_2D, getPurpleMountTexture());
}

void PurpleMount::reset() {

}

void PurpleMount::defaults() {
  width = 32;
  height = 32;
  health = 10;
}
/*
void PurpleMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {
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

  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
    if(isShooting) {
      tick(isShooting);
    } else {
      bulletTicks = PURPLEPLASMATIMER;
    }
}

void PurpleMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}*/

